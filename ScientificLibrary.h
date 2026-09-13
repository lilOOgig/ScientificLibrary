#pragma once
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include "Publication.h"

class ScientificLibrary : public std::enable_shared_from_this<ScientificLibrary> {
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
};
