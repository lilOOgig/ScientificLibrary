#include "Book.h"
#include <algorithm>

Book::Book(std::string_view t, std::string_view a, int y, int pages, std::weak_ptr<ScientificLibrary> lib)
    : Publication(t, a, y, lib), pageCount(pages) {
}

int Book::getPageCount() const { return pageCount; }
void Book::setPageCount(int pages) {
    if (pages <= 0) throw std::invalid_argument("Ошибка: количество страниц должно быть положительным!");
    pageCount = pages;
}
void Book::printPageCount(std::ostream& os) const { os << "Страниц: " << pageCount; }
void Book::readPageCount(std::istream& is) { setPageCount(readInt(is, "Введите количество страниц: ")); }

std::string_view Book::getType() const { return "Книга"; }

void Book::printInformation(std::ostream& os) const {
    Publication::printInformation(os);
    os << " | ";
    printPageCount(os);
}

bool Book::equals(const Publication& other) const {
    const auto* b = dynamic_cast<const Book*>(&other);
    return b && hasSameCommonData(*b);
}

void Book::readFrom(std::istream& is) {
    Publication::readFrom(is);
    readPageCount(is);
}

int Book::getLoanPeriod() const { return std::min(30, 14 + pageCount / 100); }
int Book::getAllowedExtension(int requestedDays) const { return limitDays(requestedDays, getLoanPeriod() / 2); }

int Book::getReadingDays(int pagesPerDay) const {
    if (pagesPerDay <= 0) throw std::invalid_argument("Ошибка: норма чтения должна быть положительной!");
    return (pageCount + pagesPerDay - 1) / pagesPerDay;
}
