#include "Book.h"
#include <iostream>

Book::Book(std::string_view t, std::string_view a, int y, int pages, std::weak_ptr<ScientificLibrary> lib)
    : Publication(t, a, y, lib), pageCount(pages) {
}

int Book::getPageCount() const { return pageCount; }

std::string_view Book::getType() const { return "Книга"; }

void Book::printInformation(std::ostream& os) const {
    os << "[Книга] \"" << title << "\" — " << author << " (" << year << " г.) | Страниц: " << pageCount;
}

double Book::calculateSpecificValue() const { return static_cast<double>(pageCount); }

void Book::applyEffect(int value) {
    if (value <= 0) {
        std::cout << "Ошибка: значение должно быть положительным!\n";
        return;
    }
    pageCount += value;
    std::cout << "Книге \"" << title << "\" добавлено страниц: " << value << ". Всего: " << pageCount << "\n";
}

void Book::readFrom(std::istream& is) {
    std::cout << "Введите название книги: ";
    std::getline(is >> std::ws, title);
    std::cout << "Введите автора: ";
    std::getline(is, author);
    std::cout << "Введите год издания: ";
    int y; is >> y; setYear(y);
    std::cout << "Введите количество страниц: ";
    is >> pageCount;
}

bool Book::equals(const Publication& other) const {
    const auto* b = dynamic_cast<const Book*>(&other);
    return b && title == b->title && author == b->author && year == b->year && pageCount == b->pageCount;
}

std::string Book::getValueName() const { return "Количество страниц"; }
