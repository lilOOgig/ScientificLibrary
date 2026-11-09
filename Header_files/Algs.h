#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <numeric>
#include <iostream>
#include "Сollection.h"

// Шаблонная функция: поиск элемента с максимальным сроком выдачи (метрикой)
template <typename T>
std::shared_ptr<T> maxByMetric(const Collection<T>& collection) {
    std::shared_ptr<T> best = nullptr;
    for (const auto& item : collection) {
        if (!item) continue;
        if (!best || item->getLoanPeriod() > best->getLoanPeriod()) {
            best = item;
        }
    }
    return best;
}

// Шаблонная функция: расчет среднего значения срока выдачи по коллекции
template <typename T>
double averageMetric(const Collection<T>& collection) {
    if (collection.size() == 0) return 0.0;

    double sum = 0.0;
    size_t count = 0;
    for (const auto& item : collection) {
        if (item) {
            sum += item->getLoanPeriod();
            ++count;
        }
    }
    return (count > 0) ? sum / count : 0.0;
}

// Шаблонная функция: сортировка элементов коллекции через современный std::ranges::sort (C++20)
template <typename T, typename Comparator>
std::vector<std::shared_ptr<T>> sortBy(const Collection<T>& collection, Comparator comp) {
    std::vector<std::shared_ptr<T>> result;
    for (const auto& item : collection) {
        if(item) result.push_back(item);
    }

    // Использование std::ranges::sort вместо передачи begin/end итераторов
    std::ranges::sort(
        result,
        [&comp](const std::shared_ptr<T>& a, const std::shared_ptr<T>& b) {
            return comp(*a, *b);
        }
    );
    
    return result;
}
