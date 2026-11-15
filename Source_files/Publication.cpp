#include "Publication.h"
#include <format>
#include <charconv>

// Пустые название и автор допускаются только у объекта по умолчанию,
// который потом заполняется через operator>>; сеттеры пустые значения не пропускают.
Publication::Publication(std::string_view t, std::string_view a, int y, std::weak_ptr<ScientificLibrary> lib)
    : title(t), author(a), libraryRef(lib) {
    setYear(y);
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

bool Publication::isBlank(std::string_view s) {
    return s.find_first_not_of(" \t\r\n") == std::string_view::npos;
}
void Publication::requireNotBlank(std::string_view value, std::string_view fieldName) {
    if (isBlank(value)) throw InvalidDataException(std::string(fieldName) + " не может быть пустым!");
}

void Publication::setTitle(std::string_view t) {
    requireNotBlank(t, "Название");
    title = t;
}
void Publication::setAuthor(std::string_view a) {
    requireNotBlank(a, "Автор");
    author = a;
}
void Publication::setYear(int y) {
    if (y <= 0 || y > CURRENT_YEAR) {
        throw InvalidDataException(std::format("год издания должен быть от 1 до {} (введено {})!", CURRENT_YEAR, y));
    }
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

std::string Publication::readLine(std::istream& is, std::string_view prompt) {
    std::cout << prompt;
    std::string s;
    if (!std::getline(is, s)) throw InputAbortedException("поток ввода закрыт!");
    return s;
}

// Читает строку целиком и требует, чтобы вся она была целым числом ("12abc" - ошибка).
int Publication::readInt(std::istream& is, std::string_view prompt) {
    const std::string line = readLine(is, prompt);
    const auto first = line.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) throw InvalidDataException("нужно ввести целое число, а введена пустая строка!");
    const auto last = line.find_last_not_of(" \t\r\n");
    const std::string_view text = std::string_view(line).substr(first, last - first + 1);

    int value = 0;
    const auto [ptr, ec] = std::from_chars(text.data(), text.data() + text.size(), value);
    if (ec != std::errc{} || ptr != text.data() + text.size()) {
        throw InvalidDataException("нужно ввести целое число, получено \"" + std::string(text) + "\"!");
    }
    return value;
}

std::strong_ordering Publication::operator<=>(const Publication& other) const { return getLoanPeriod() <=> other.getLoanPeriod(); }
bool Publication::operator==(const Publication& other) const { return equals(other); }
