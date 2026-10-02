#include "Publication.h"

Publication::Publication(std::string_view t, std::string_view a, std::string_view tp, int y, std::weak_ptr<ScientificLibrary> lib)
    : title(t), author(a), type(tp), isBorrowed(false), libraryRef(lib) {
    setYear(y); 
}

std::string_view Publication::getTitle() const { return title; }
std::string_view Publication::getAuthor() const { return author; }
std::string_view Publication::getType() const { return type; }
int Publication::getYear() const { return year; }
bool Publication::getIsBorrowed() const { return isBorrowed; }

void Publication::setTitle(std::string_view t) { title = t; }
void Publication::setAuthor(std::string_view a) { author = a; }
void Publication::setType(std::string_view tp) { type = tp; }
void Publication::setBorrowed(bool status) { isBorrowed = status; }
void Publication::setYear(int y) {
    if (y <= 0) {
        throw std::invalid_argument("Ошибка: Год издания должен быть положительным числом!");
    }
    year = y;
}

void Publication::printInfo() const {
    std::cout << *this << std::endl;
}

bool Publication::operator==(const Publication& other) const {
    return title == other.title;
}

bool Publication::operator!=(const Publication& other) const {
    return !(*this == other);
}

bool Publication::operator<(const Publication& other) const {
    return year < other.year;
}

bool Publication::operator>(const Publication& other) const {
    return year > other.year;
}

bool Publication::operator<=(const Publication& other) const {
    return year <= other.year;
}

bool Publication::operator>=(const Publication& other) const {
    return year >= other.year;
}

std::ostream& operator<<(std::ostream& os, const Publication& pub) {
    os << "[" << pub.type << "] \"" << pub.title << "\" — " << pub.author
        << " (" << pub.year << " г.) | "
        << (pub.isBorrowed ? "Выдана" : "В наличии");
    return os;
}

std::istream& operator>>(std::istream& is, Publication& pub) {
    std::cout << "Введите название: ";
    std::getline(is >> std::ws, pub.title);

    std::cout << "Введите автора: ";
    std::getline(is, pub.author);

    std::cout << "Введите тип (Книга/Статья): ";
    std::getline(is, pub.type);

    std::cout << "Введите год издания: ";
    int tempYear;
    if (!(is >> tempYear)) {
        is.clear();
        throw std::invalid_argument("Ошибка: Некорректный ввод года!");
    }
    pub.setYear(tempYear);
    pub.isBorrowed = false;

    return is;
}
