#pragma once

#include "vector.h"

#include <algorithm>
#include <optional>

namespace shket::common {

template<typename K, typename V, size_t t = 3>
class BTree {
public:
    template<typename T>
    using vector = Vector<T>;

    using Item = std::pair<K, V>;

    using ItemVisitor = std::function<void(const Item &)>;

    struct Node {
        bool is_leaf = false;
        int64_t num_items = 0;
        Item items[2 * t - 1];
        Node *children[2 * t];
    };

public:
    BTree() : size_(0) {
        root_ = new Node;
        root_->is_leaf = true;
        root_->num_items = 0;
    }

    ~BTree() {
        destroy();
    }

public:
    void insert(Item item) {
        auto r = root_;
        if (r->num_items == 2 * t - 1) {
            auto s = new Node();
            root_ = s;
            s->children[0] = r;
            split_child(s, 0);
            insert_nonfull(s, item);
        } else {
            insert_nonfull(r, item);
        }
        ++size_;
    }

    auto find(const K &key) const {
        return root_ ? find_(key, root_) : std::nullopt;
    }

    void traverse(const ItemVisitor &visitor) const {
        traverse_(root_, visitor);
    }

    [[nodiscard]]
    auto size() const -> size_t {
        return size_;
    }

private:
    auto find_(const K &key, Node *node) const -> std::optional<std::reference_wrapper<Item>> {
        int64_t i = 0;
        while (i < node->num_items && key > node->items[i].first) {
            ++i;
        }

        if (i < node->num_items && node->items[i].first == key) {
            return node->items[i];
        }

        return node->is_leaf ? std::nullopt : find_(key, node->children[i]);
    }

    void insert_nonfull(Node *x, Item item) {
        int64_t i = x->num_items - 1;
        if (x->is_leaf) {
            while (i >= 0 && item.first < x->items[i].first) {
                x->items[i + 1] = x->items[i];
                --i;
            }
            ++i;

            x->items[i] = item;
            ++x->num_items;
        } else {
            while (i >= 0 && item.first < x->items[i].first) {
                --i;
            }
            ++i;
            if (x->children[i]->num_items == 2 * t - 1) {
                split_child(x, i);
                if (item.first > x->items[i].first) {
                    ++i;
                }
            }
            insert_nonfull(x->children[i], item);
        }

    }

    void split_child(Node *x, int64_t i) {
        auto y = x->children[i];

        auto z = new Node;
        z->is_leaf = y->is_leaf;
        z->num_items = t - 1;
        for (int64_t j = 0; j < t - 1; ++j) {
            z->items[j] = y->items[j + t];
        }

        if (!y->is_leaf) {
            for (int64_t j = 0; j < t; ++j) {
                z->children[j] = y->children[j + t];
            }
        }
        y->num_items = t - 1;

        for (int64_t j = x->num_items; j >= i + 1; --j) {
            x->children[j + 1] = x->children[j];
        }
        x->children[i + 1] = z;

        for (int64_t j = x->num_items - 1; j >= i; --j) {
            x->items[j + 1] = x->items[j];
        }
        x->items[i] = y->items[t - 1];

        ++x->num_items;
    }

    void traverse_(Node *x, const ItemVisitor &visitor) const {
        if (x == nullptr) {
            return;
        }

        for (size_t i = 0; i < x->num_items; ++i) {
            visitor(x->items[i]);
        }

        if (!x->is_leaf) {
            for (size_t i = 0; i < x->num_items + 1; ++i) {
                traverse_(x->children[i], visitor);
            }
        }
    }

    void destroy() {

    }

private:
    Node *root_;
    size_t size_;
};

}