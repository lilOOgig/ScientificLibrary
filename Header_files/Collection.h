#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

template <typename T>
class Collection {
public:
    Collection() = default;
    ~Collection() = default;

    const std::vector<std::shared_ptr<T>>& getItems() const;

    void add(const std::shared_ptr<T>& item);
    void removeAt(size_t index);
    
    template <typename Predicate>
    size_t removeIf(Predicate pred);

    std::shared_ptr<T> get(size_t index) const;

    template <typename Predicate>
    std::shared_ptr<T> find(Predicate pred) const;

    template <typename Predicate>
    Collection<T> findAll(Predicate pred) const;

    size_t size() const;
    void clear();
    void print(std::ostream& os = std::cout) const;

    auto begin() const { return _items.begin(); }
    auto end() const { return _items.end(); }
    auto begin() { return _items.begin(); }
    auto end() { return _items.end(); }

private:
    std::vector<std::shared_ptr<T>> _items;
};

#include "Collection.tpp"
