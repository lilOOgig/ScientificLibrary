#include "Publication.h"
#include <limits>

Publication::Publication(std::string_view t, std::string_view a, int y, std::weak_ptr<ScientificLibrary> lib)
    : title(t), author(a), isBorrowed(false), libraryRef(lib) {
    if (y <= 0) {
        throw std::invalid_argument("Ошибка: Год издания должен быть положительным числом!");
    }
    year = y;
}

void Publication::printInformation(std::ostream& os) const {
    os << "[" << getType() << "] \"" << title << "\" — " << author << " (" << year << " г.)";
}

void Publication::readFrom(std::istream& is) {
    readTitle(is);
    readAuthor(is);
    readYear(is);
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

void Publication::printTitle(std::ostream& os) const { os << "Название: " << title; }
void Publication::printAuthor(std::ostream& os) const { os << "Автор: " << author; }
void Publication::printYear(std::ostream& os) const { os << "Год: " << year; }

void Publication::readTitle(std::istream& is) { setTitle(readLine(is, "Введите название: ")); }
void Publication::readAuthor(std::istream& is) { setAuthor(readLine(is, "Введите автора: ")); }
void Publication::readYear(std::istream& is) { setYear(readInt(is, "Введите год издания: ")); }

bool Publication::hasSameCommonData(const Publication& other) const {
    return title == other.title && author == other.author && year == other.year;
}

int Publication::readInt(std::istream& is, std::string_view prompt) {
    std::cout << prompt;
    int value;
    if (!(is >> value)) {
        is.clear();
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Ошибка: нужно ввести целое число!");
    }
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

std::string Publication::readLine(std::istream& is, std::string_view prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(is, s);
    return s;
}

std::ostream& operator<<(std::ostream& os, const Publication& pub) {
    pub.printInformation(os);
    os << " | Статус: " << (pub.isBorrowed ? "Выдана" : "В наличии");
    return os;
}

std::istream& operator>>(std::istream& is, Publication& pub) {
    pub.readFrom(is);
    return is;
}

bool Publication::operator<(const Publication& other) const { return getKeyIndicator() < other.getKeyIndicator(); }
bool Publication::operator>(const Publication& other) const { return getKeyIndicator() > other.getKeyIndicator(); }
bool Publication::operator<=(const Publication& other) const { return getKeyIndicator() <= other.getKeyIndicator(); }
bool Publication::operator>=(const Publication& other) const { return getKeyIndicator() >= other.getKeyIndicator(); }
bool Publication::operator==(const Publication& other) const { return equals(other); }
bool Publication::operator!=(const Publication& other) const { return !(*this == other); }
