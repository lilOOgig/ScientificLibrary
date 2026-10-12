#include "Publication.h"

std::string_view typeToString(PublicationType type) {
    switch (type) {
        case PublicationType::Article:    return "Статья";
        case PublicationType::Book:       return "Книга";
        case PublicationType::Journal:    return "Журнал";
        case PublicationType::Monograph:  return "Монография";
        case PublicationType::Conference: return "Конференция";
        default:                          return "Неизвестно";
    }
}

Publication::Publication() 
    : title(""), author(""), type(PublicationType::Book), year(1), isBorrowed(false) {}

Publication::Publication(std::string_view t, std::string_view a, PublicationType tp, int y, std::weak_ptr<ScientificLibrary> lib)
    : title(t), author(a), type(tp), isBorrowed(false), libraryRef(lib) {
    setYear(y); 
}

std::string_view Publication::getTitle() const { return title; }
std::string_view Publication::getAuthor() const { return author; }
PublicationType Publication::getType() const { return type; }
int Publication::getYear() const { return year; }
bool Publication::getIsBorrowed() const { return isBorrowed; }

void Publication::setTitle(std::string_view t) { title = t; }
void Publication::setAuthor(std::string_view a) { author = a; }
void Publication::setType(PublicationType tp) { type = tp; }
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
    return title == other.title && author == other.author && year == other.year && type == other.type;
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
    os << "[" << typeToString(pub.type) << "] \"" << pub.title << "\" — " << pub.author
       << " (" << pub.year << " г.) | "
       << (pub.isBorrowed ? "Выдана" : "В наличии");
    return os;
}

std::istream& operator>>(std::istream& is, Publication& pub) {
    std::cout << "Введите название: ";
    std::getline(is >> std::ws, pub.title);

    std::cout << "Введите автора: ";
    std::getline(is, pub.author);

    std::cout << "Выберите тип (0 - Статья, 1 - Книга, 2 - Журнал, 3 - Монография, 4 - Конференция): ";
    int typeChoice;
    if (!(is >> typeChoice) || typeChoice < 0 || typeChoice > 4) {
        is.clear();
        throw std::invalid_argument("Ошибка: Некорректный выбор типа публикации!");
    }
    pub.type = static_cast<PublicationType>(typeChoice);

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

// [ИЗ ВЕРСИИ 2] Дружественная функция
int getYearDifference(const Publication& p1, const Publication& p2) {
    return std::abs(p1.year - p2.year);
}
