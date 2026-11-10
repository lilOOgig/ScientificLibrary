#pragma once
#include <algorithm>
#include <memory>
#include <vector>
#include "Collection.h"

// Элемент с наибольшим значением метрики. metric(const T&) возвращает любое сравнимое значение.
template <typename T, typename Metric>
std::shared_ptr<T> maxByMetric(const Collection<T>& collection, Metric metric) {
    std::shared_ptr<T> best;
    for (const auto& item : collection) {
        if (!best || metric(*item) > metric(*best)) best = item;
    }
    return best;
}

// Среднее значение числовой метрики по коллекции (0 для пустой).
template <typename T, typename Metric>
double averageMetric(const Collection<T>& collection, Metric metric) {
    if (collection.empty()) return 0.0;
    double sum = 0.0;
    for (const auto& item : collection) sum += metric(*item);
    return sum / static_cast<double>(collection.size());
}

// Копия содержимого, отсортированная по компаратору comp(const T&, const T&).
// Сама коллекция при этом не меняется.
template <typename T, typename Comparator>
std::vector<std::shared_ptr<T>> sortBy(const Collection<T>& collection, Comparator comp) {
    std::vector<std::shared_ptr<T>> result(collection.begin(), collection.end());
    std::ranges::sort(result, [&comp](const std::shared_ptr<T>& a, const std::shared_ptr<T>& b) {
        return comp(*a, *b);
    });
    return result;
}

// Выборка из коллекции базовых объектов только тех, что имеют конкретный тип Derived
// (например, все книги из общего фонда).
template <typename Derived, typename Base>
Collection<Derived> selectByType(const Collection<Base>& source) {
    Collection<Derived> result;
    for (const auto& item : source) {
        if (auto typed = std::dynamic_pointer_cast<Derived>(item)) result.add(typed);
    }
    return result;
}
