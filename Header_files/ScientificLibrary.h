#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include "Publication.h"

class ScientificLibrary {
private:
    std::string name;
    size_t maxCapacity;
    std::vector<std::shared_ptr<Publication>> items;

public:
    ScientificLibrary(std::string_view libName, size_t capacity);

    void addPublication(const std::shared_ptr<Publication>& pub);
    bool issuePublication(std::string_view pubTitle, std::string_view userName);
    void returnPublication(std::string_view pubTitle);
    void showCatalog() const;
    void searchByAuthor(std::string_view authorName) const;

    // Полиморфные вызовы
    void applyMassEffect(int value);
    void showSpecificValues() const;
    void findMostValuable() const;

    const std::vector<std::shared_ptr<Publication>>& getItems() const { return items; }

    ScientificLibrary& operator+=(const std::shared_ptr<Publication>& pub);
    ScientificLibrary& operator-=(const std::shared_ptr<Publication>& pub);
};
