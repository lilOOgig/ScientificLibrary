#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include "Collection.h"
#include "Publication.h"
#include "exceptions.h"

enum class SortKey { Title, Year, LoanPeriod };

class ScientificLibrary : public std::enable_shared_from_this<ScientificLibrary> {
public:
    static constexpr int MAX_EXTENSION_DAYS = 30;   // максимальный срок, на который можно продлевать за раз

private:
    std::string name;
    size_t maxCapacity;
    Collection<Publication> items;

    // Ищет издание по названию; бросает InvalidDataException / ObjectNotFoundException / RelationException.
    std::shared_ptr<Publication> requireByTitle(std::string_view pubTitle) const;

public:
    ScientificLibrary(std::string_view libName, size_t capacity);

    void addPublication(const std::shared_ptr<Publication>& pub);
    void removePublication(std::string_view pubTitle);
    void removeByNumber(int number);                                  // номер в каталоге, с 1
    std::shared_ptr<Publication> findPublication(std::string_view pubTitle) const;
    std::shared_ptr<Publication> getByNumber(int number) const;       // номер в каталоге, с 1
    void issuePublication(std::string_view pubTitle, std::string_view userName) const;
    void returnPublication(std::string_view pubTitle) const;
    void showCatalog() const;
    void searchByAuthor(std::string_view authorName) const;
    void showSorted(SortKey key) const;
    void showStatistics() const;

    void extendAllLoans(int days) const;
    void showLoanPeriods() const;
    void findLongestLoan() const;

    const Collection<Publication>& getItems() const { return items; }

    ScientificLibrary& operator+=(const std::shared_ptr<Publication>& pub);
    ScientificLibrary& operator-=(const std::shared_ptr<Publication>& pub);
};
