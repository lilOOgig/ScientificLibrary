#pragma once
#include <algorithm>
#include <stdexcept>

template <typename T>
void Collection<T>::add(const std::shared_ptr<T>& item) {
    if (!item) throw std::invalid_argument("Нельзя добавить пустой указатель в коллекцию!");
    items.push_back(item);
}

template <typename T>
void Collection<T>::removeAt(size_t index) {
    if (index >= items.size()) throw std::out_of_range("Индекс " + std::to_string(index) + " за пределами коллекции (размер " + std::to_string(items.size()) + ")!");
    items.erase(items.begin() + index);
}

template <typename T>
template <typename Predicate>
size_t Collection<T>::removeIf(Predicate pred) {
    return std::erase_if(items, [&pred](const std::shared_ptr<T>& item) { return pred(*item); });
}

template <typename T>
std::shared_ptr<T> Collection<T>::get(size_t index) const {
    if (index >= items.size()) throw std::out_of_range("Индекс " + std::to_string(index) + " за пределами коллекции (размер " + std::to_string(items.size()) + ")!");
    return items[index];
}

template <typename T>
template <typename Predicate>
std::shared_ptr<T> Collection<T>::find(Predicate pred) const {
    auto it = std::ranges::find_if(items, [&pred](const std::shared_ptr<T>& item) { return pred(*item); });
    return it != items.end() ? *it : nullptr;
}

template <typename T>
template <typename Predicate>
Collection<T> Collection<T>::findAll(Predicate pred) const {
    Collection<T> result;
    for (const auto& item : items) {
        if (pred(*item)) result.add(item);
    }
    return result;
}

template <typename T>
size_t Collection<T>::size() const { return items.size(); }

template <typename T>
bool Collection<T>::empty() const { return items.empty(); }

template <typename T>
void Collection<T>::clear() { items.clear(); }

template <typename T>
void Collection<T>::print(std::ostream& os) const {
    if (items.empty()) {
        os << "   (коллекция пуста)\n";
        return;
    }
    for (size_t i = 0; i < items.size(); ++i) {
        os << "   [" << i << "] " << *items[i] << "\n";
    }
}
