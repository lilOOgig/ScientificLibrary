#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "Publication.h"

// Собственные типы исключений библиотеки
class LibraryError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};
class PublicationNotFoundError : public LibraryError {
public:
    using LibraryError::LibraryError;
};
class PublicationAlreadyIssuedError : public LibraryError {
public:
    using LibraryError::LibraryError;
};
class PublicationAlreadyOnShelfError : public LibraryError {
public:
    using LibraryError::LibraryError;
};
class LibraryFullError : public LibraryError {
public:
    using LibraryError::LibraryError;
};
class DuplicatePublicationError : public LibraryError {
public:
    using LibraryError::LibraryError;
};

class ScientificLibrary : public std::enable_shared_from_this<ScientificLibrary> {
private:
    std::string name;
    size_t maxCapacity;
    std::vector<std::shared_ptr<Publication>> items;

public:
    ScientificLibrary(std::string_view libName, size_t capacity);

    void addPublication(const std::shared_ptr<Publication>& pub);
    bool issuePublication(std::string_view pubTitle, std::string_view userName) const;
    void returnPublication(std::string_view pubTitle) const;
    void showCatalog() const;
    void searchByAuthor(std::string_view authorName) const;

    // Полиморфные операции над коллекцией
    void extendAllLoans(int days) const;      // запросить продление срока выдачи для всех изданий
    void showLoanPeriods() const;             // показать срок выдачи каждого издания
    void findLongestLoan() const;             // издание с наибольшим сроком выдачи

    const std::vector<std::shared_ptr<Publication>>& getItems() const { return items; }

    ScientificLibrary& operator+=(const std::shared_ptr<Publication>& pub);
    ScientificLibrary& operator-=(const std::shared_ptr<Publication>& pub);
};
