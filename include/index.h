#pragma once

#include "common/vector.h"
#include "common/btree.h"

#include <iostream>
#include <cassert>

namespace shket {

class Index {
public:
    template<typename T>
    using vector = common::Vector<T>;

public:
    Index() = default;

    ~Index() = default;

public:
    void index(const std::string &doc_id, const std::string &token);

    void print() const;

private:
    common::BTree<std::string, vector<std::string>> word_to_docs_;
};

}