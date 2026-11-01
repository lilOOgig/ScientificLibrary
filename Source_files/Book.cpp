#include "Book.h"

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

void Book::addPages(int count) {
    if (count <= 0) throw std::invalid_argument("Ошибка: количество страниц должно быть положительным!");
    pageCount += count;
}

std::string_view Book::getType() const { return "Книга"; }

void Book::printInformation(std::ostream& os) const {
    Publication::printInformation(os);
    os << " | ";
    printPageCount(os);
}

double Book::getKeyIndicator() const { return static_cast<double>(pageCount); }
std::string Book::getKeyIndicatorName() const { return "Количество страниц"; }

void Book::updateKeyIndicator(int value) {
    if (value <= 0) {
        std::cout << "Ошибка: значение должно быть положительным!\n";
        return;
    }
    addPages(value);
    std::cout << "Книге \"" << title << "\" добавлено страниц: " << value << ". Всего: " << pageCount << "\n";
}

bool Book::equals(const Publication& other) const {
    const auto* b = dynamic_cast<const Book*>(&other);
    return b && hasSameCommonData(*b) && pageCount == b->pageCount;
}

void Book::readFrom(std::istream& is) {
    Publication::readFrom(is);
    readPageCount(is);
}
