#include "Publication.h"
#include <limits>

Publication::Publication(std::string_view t, std::string_view a, int y, std::weak_ptr<ScientificLibrary> lib)
    : title(t), author(a), isBorrowed(false), libraryRef(lib) {
    if (y <= 0) {
        throw std::invalid_argument("Ошибка: Год издания должен быть положительным числом!");
    }
    year = y;
}

std::string_view Publication::getTitle() const { return title; }
std::string_view Publication::getAuthor() const { return author; }
int Publication::getYear() const { return year; }
bool Publication::getIsBorrowed() const { return isBorrowed; }
std::weak_ptr<ScientificLibrary> Publication::getLibraryRef() const { return libraryRef; }

void Publication::setTitle(std::string_view t) { title = t; }
void Publication::setAuthor(std::string_view a) { author = a; }
void Publication::setYear(int y) {
    if (y <= 0) throw std::invalid_argument("Ошибка: Некорректный год!");
    year = y;
}
void Publication::setBorrowed(bool status) { isBorrowed = status; }
void Publication::setLibraryRef(std::weak_ptr<ScientificLibrary> lib) { libraryRef = lib; }

std::ostream& operator<<(std::ostream& os, const Publication& pub) {
    pub.printInformation(os);
    os << " | Статус: " << (pub.isBorrowed ? "Выдана" : "В наличии");
    return os;
}

std::istream& operator>>(std::istream& is, Publication& pub) {
    pub.readFrom(is);
    return is;
}

bool Publication::operator<(const Publication& other) const { return this->calculateSpecificValue() < other.calculateSpecificValue(); }
bool Publication::operator>(const Publication& other) const { return this->calculateSpecificValue() > other.calculateSpecificValue(); }
bool Publication::operator<=(const Publication& other) const { return this->calculateSpecificValue() <= other.calculateSpecificValue(); }
bool Publication::operator>=(const Publication& other) const { return this->calculateSpecificValue() >= other.calculateSpecificValue(); }
bool Publication::operator==(const Publication& other) const { return equals(other); }
bool Publication::operator!=(const Publication& other) const { return !(*this == other); }