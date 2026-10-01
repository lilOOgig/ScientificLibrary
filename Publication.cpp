#include "Publication.h"

Publication::Publication(std::string_view t, std::string_view a, std::string_view tp, int y, std::weak_ptr<ScientificLibrary> lib)
    : title(t), author(a), type(tp), year(y), isBorrowed(false), libraryRef(lib) {
}

std::string_view Publication::getTitle() const { return title; }
std::string_view Publication::getAuthor() const { return author; }
std::string_view Publication::getType() const { return type; }
int Publication::getYear() const { return year; }
bool Publication::getIsBorrowed() const { return isBorrowed; }

void Publication::setTitle(std::string_view t) { title = t; }
void Publication::setAuthor(std::string_view a) { author = a; }
void Publication::setType(std::string_view tp) { type = tp; }
void Publication::setYear(int y) { year = y; }
void Publication::setBorrowed(bool status) { isBorrowed = status; }

void Publication::printInfo() const {
    std::cout << "[" << type << "] \"" << title << "\" — " << author
        << " (" << year << " г.) | "
        << (isBorrowed ? "Выдана" : "В наличии") << std::endl;
}
