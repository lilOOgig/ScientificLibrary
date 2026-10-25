#include "Publication.h"
#include <limits>

Publication::Publication()
    : title(""), author(""), year(1), isBorrowed(false) {
}

Publication::Publication(std::string_view t, std::string_view a, int y, std::weak_ptr<ScientificLibrary> lib)
    : title(t), author(a), isBorrowed(false), libraryRef(lib) {
    setYear(y);
}

std::string_view Publication::getTitle() const { return title; }
std::string_view Publication::getAuthor() const { return author; }
int Publication::getYear() const { return year; }
bool Publication::getIsBorrowed() const { return isBorrowed; }

void Publication::setTitle(std::string_view t) { title = t; }
void Publication::setAuthor(std::string_view a) { author = a; }
void Publication::setBorrowed(bool status) { isBorrowed = status; }

void Publication::setYear(int y) {
    if (y <= 0) {
        throw std::invalid_argument("Ошибка: Год издания должен быть положительным числом!");
    }
    year = y;
}

void Publication::printSpecific(std::ostream& os) const {}
void Publication::readSpecific(std::istream& is) {}

void Publication::printInfo() const {
    std::cout << *this << std::endl;
}

bool Publication::operator==(const Publication& other) const {
    return title == other.title && author == other.author && year == other.year && getType() == other.getType();
}

bool Publication::operator!=(const Publication& other) const {
    return !(*this == other);
}

bool Publication::operator<(const Publication& other) const { return year < other.year; }
bool Publication::operator>(const Publication& other) const { return year > other.year; }
bool Publication::operator<=(const Publication& other) const { return year <= other.year; }
bool Publication::operator>=(const Publication& other) const { return year >= other.year; }

std::ostream& operator<<(std::ostream& os, const Publication& pub) {
    os << "[" << pub.getType() << "] \"" << pub.title << "\" — " << pub.author
        << " (" << pub.year << " г.)";
    pub.printSpecific(os);
    os << " | " << (pub.isBorrowed ? "Выдана" : "В наличии");
    return os;
}

std::istream& operator>>(std::istream& is, Publication& pub) {
    std::cout << "Введите название: ";
    std::getline(is >> std::ws, pub.title);

    std::cout << "Введите автора: ";
    std::getline(is, pub.author);

    std::cout << "Введите год издания: ";
    int tempYear;
    if (!(is >> tempYear)) {
        is.clear();
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Ошибка: Некорректный ввод года!");
    }
    pub.setYear(tempYear);
    pub.isBorrowed = false;

    pub.readSpecific(is);
    return is;
}

int getYearDifference(const Publication& p1, const Publication& p2) {
    return std::abs(p1.year - p2.year);
}
