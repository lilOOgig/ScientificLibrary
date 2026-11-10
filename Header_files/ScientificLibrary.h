#pragma once
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include "Collection.h"
#include "Publication.h"

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
    Collection<Publication> items;

public:
    ScientificLibrary(std::string_view libName, size_t capacity);

    void addPublication(const std::shared_ptr<Publication>& pub);
    void issuePublication(std::string_view pubTitle, std::string_view userName) const;
    void returnPublication(std::string_view pubTitle) const;
    void showCatalog() const;
    void searchByAuthor(std::string_view authorName) const;

    void extendAllLoans(int days) const;
    void showLoanPeriods() const;
    void findLongestLoan() const;

    const Collection<Publication>& getItems() const { return items; }

    ScientificLibrary& operator+=(const std::shared_ptr<Publication>& pub);
    ScientificLibrary& operator-=(const std::shared_ptr<Publication>& pub);
};
