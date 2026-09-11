#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Publication.h"

class ScientificLibrary {
private:
    std::string libraryName;
    std::vector<Publication> catalog;

public:
    ScientificLibrary(std::string name);

    void addPublication(const Publication& pub);
    void printCatalog() const;
    bool issuePublication(const std::string& title, const std::string& researcherName);
    void returnPublication(const std::string& title);
    void searchByAuthor(const std::string& author) const;
};