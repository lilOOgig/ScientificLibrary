#include "Book.h"
#include <iostream>

Book::Book() : Publication("", "", 2000), pageCount(100) {}

Book::Book(std::string_view t, std::string_view a, int y, int pages, std::weak_ptr<ScientificLibrary> lib)
    : Publication(t, a, y, lib), pageCount(pages) {}

int Book::getPageCount() const { return pageCount; }

std::string_view Book::getType() const { return "Книга"; }

void Book::printSpecific(std::ostream& os) const {
    os << " | Страниц: " << pageCount;
}

void Book::readSpecific(std::istream& is) {
    std::cout << "Введите количество страниц: ";
    safeReadNumber(is, pageCount, 100);
}
