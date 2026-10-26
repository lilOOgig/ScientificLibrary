#include "Conference.h"
#include <iostream>

Conference::Conference(std::string_view t, std::string_view a, int y, std::string_view confName, std::string_view loc, std::weak_ptr<ScientificLibrary> lib)
    : Publication(t, a, y, lib), conferenceName(confName), location(loc) {
}

std::string_view Conference::getType() const { return "Конференция"; }

void Conference::printInformation(std::ostream& os) const {
    os << "[Конференция] \"" << title << "\" — " << author << " (" << year << " г.) | Мероприятие: " << conferenceName << " (" << location << ")";
}

double Conference::calculateSpecificValue() const { return static_cast<double>(2026 - year); }

void Conference::applyEffect(int value) {
    std::cout << "Для материалов конференции \"" << title << "\" учтено дополнительных ссылок: " << value << "\n";
}

void Conference::readFrom(std::istream& is) {
    std::cout << "Введите название доклада: ";
    std::getline(is >> std::ws, title);
    std::cout << "Введите автора: ";
    std::getline(is, author);
    std::cout << "Введите год: ";
    int y; is >> y; setYear(y);
    std::cout << "Введите название конференции: ";
    std::getline(is >> std::ws, conferenceName);
    std::cout << "Введите место проведения: ";
    std::getline(is, location);
}

bool Conference::equals(const Publication& other) const {
    const auto* c = dynamic_cast<const Conference*>(&other);
    return c && title == c->title && author == c->author && year == c->year && conferenceName == c->conferenceName;
}

std::string Conference::getValueName() const { return "Давность доклада (лет)"; }