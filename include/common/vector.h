#pragma once

#include <cstddef>
#include <utility>
#include <cstdint>

namespace shket::common {

template<typename T>
class Vector {
public:
    Vector() = default;

    explicit Vector(size_t count) : capacity_(count), size_(count) {
        begin_ = new T[count];
    }

    Vector(size_t count, T value) : capacity_(count), size_(count) {
        begin_ = new T[count];
        for (size_t i = 0; i < size_; ++i) {
            begin_[i] = value;
        }
    }

    Vector(std::initializer_list<T> init) : capacity_(init.size()) {
        begin_ = new T[capacity_];
        for (const auto val : init) {
            push_back(val);
        }
    }

    Vector(const Vector<T> &other) {
        reserve(other.capacity());
        for (size_t i = 0; i < other.size(); ++i) {
            begin_[i] = other[i];
        }

        size_ = other.size();
    }

    Vector(Vector<T> &&other) noexcept {
        begin_ = other.begin_;
        capacity_ = other.capacity_;
        size_ = other.size_;

        other.begin_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
    }

    Vector<T> &operator=(std::initializer_list<T> init) {
        reserve(init.size());

        for (size_t i = 0; i < init.size(); ++i) {
            begin_[i] = init.begin()[i];
        }

        size_ = init.size();
    }

    Vector<T> &operator=(const Vector<T> &other) {
        if (&other == this) {
            return *this;
        }

        reserve(other.capacity());
        for (size_t i = 0; i < other.size(); ++i) {
            begin_[i] = other[i];
        }

        size_ = other.size();

        return *this;
    }

    Vector<T> &operator=(Vector<T> &&other) noexcept {
        if (&other == this) {
            return *this;
        }

        begin_ = other.begin_;
        capacity_ = other.capacity_;
        size_ = other.size_;

        other.begin_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;

        return *this;
    }

    ~Vector() {
        clear();
    }

public:
    void reserve(size_t cap) {
        if (capacity_ < cap) {
            capacity_ = cap;
            auto new_begin = new T[capacity_];

            for (size_t i = 0; i < size_; ++i) {
                new_begin[i] = begin_[i];
            }

            delete[] begin_;
            begin_ = new_begin;
        }
    }

    void resize(size_t sz) {
        reserve(sz);
        size_ = sz;
    }

    void push_back(T &&value) {
        if (size_ == capacity_) {
            capacity_ = capacity_ * 2 + (capacity_ == 0);
            auto new_begin = new T[capacity_];

            for (size_t i = 0; i < size_; ++i) {
                new_begin[i] = begin_[i];
            }

            delete[] begin_;
            begin_ = new_begin;
        }

        begin_[size_] = std::forward<T>(value);
        ++size_;
    }

    void push_back(const T &value) {
        if (size_ == capacity_) {
            capacity_ = capacity_ * 2 + (capacity_ == 0);
            auto new_begin = new T[capacity_];

            for (size_t i = 0; i < size_; ++i) {
                new_begin[i] = begin_[i];
            }

            delete[] begin_;
            begin_ = new_begin;
        }

        begin_[size_] = value;
        ++size_;
    }

    void pop_back() {
        --size_;
    }

    void clear() {
        delete[] begin_;

        begin_ = nullptr;
        capacity_ = 0;
        size_ = 0;
    }

    inline
    auto begin() const -> T * {
        return begin_;
    }

    inline
    auto end() const -> T * {
        return begin_ + size_;
    }

    inline
    auto back() const -> T & {
        return begin_[size_ - 1];
    }

    inline
    auto operator[](size_t i) const -> T & {
        return begin_[i];
    }

    [[nodiscard]]
    inline
    auto capacity() const -> size_t {
        return capacity_;
    }

    [[nodiscard]]
    inline
    auto size() const -> size_t {
        return size_;
    }

    [[nodiscard]]
    inline
    auto empty() const -> bool {
        return size_ == 0;
    }

    auto binary_search(const T &val) -> std::pair<bool, size_t> {
        int64_t l = -1;
        int64_t r = size();

        while (l < r - 1) {
            size_t m = (l + r) / 2;

            if (begin_[m] == val) {
                return {true, m};
            } else if (begin_[m] < val) {
                l = m;
            } else {
                r = m;
            }
        }

        return {false, l};
    }

private:
    T *begin_ = nullptr;

    size_t capacity_ = 0;
    size_t size_ = 0;
};

}