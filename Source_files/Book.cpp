#include "Book.h"
#include <format>
#include <algorithm>

Book::Book(std::string_view t, std::string_view a, int y, int pages, std::weak_ptr<ScientificLibrary> lib)
    : Publication(t, a, y, lib) {
    setPageCount(pages);
}

int Book::getPageCount() const { return pageCount; }
void Book::setPageCount(int pages) {
    if (pages <= 0) throw InvalidDataException(std::format("количество страниц должно быть положительным (введено {})!", pages));
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
    if (pagesPerDay <= 0) throw InvalidDataException(std::format("норма чтения должна быть положительной (введено {})!", pagesPerDay));
    return (pageCount + pagesPerDay - 1) / pagesPerDay;
}
