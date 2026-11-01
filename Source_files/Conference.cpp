#include "Conference.h"

Conference::Conference(std::string_view t, std::string_view a, int y, std::string_view confName, std::string_view loc, std::weak_ptr<ScientificLibrary> lib)
    : Publication(t, a, y, lib), conferenceName(confName), location(loc) {
}

std::string_view Conference::getConferenceName() const { return conferenceName; }
void Conference::setConferenceName(std::string_view name) { conferenceName = name; }
void Conference::printConferenceName(std::ostream& os) const { os << "Мероприятие: " << conferenceName; }
void Conference::readConferenceName(std::istream& is) { setConferenceName(readLine(is, "Введите название конференции: ")); }

std::string_view Conference::getLocation() const { return location; }
void Conference::setLocation(std::string_view loc) { location = loc; }
void Conference::printLocation(std::ostream& os) const { os << "Место: " << location; }
void Conference::readLocation(std::istream& is) { setLocation(readLine(is, "Введите место проведения: ")); }

int Conference::getAge(int currentYear) const { return currentYear - year; }

std::string_view Conference::getType() const { return "Конференция"; }

void Conference::printInformation(std::ostream& os) const {
    Publication::printInformation(os);
    os << " | ";
    printConferenceName(os);
    os << " | ";
    printLocation(os);
}

double Conference::getKeyIndicator() const { return static_cast<double>(getAge()); }
std::string Conference::getKeyIndicatorName() const { return "Давность доклада (лет)"; }

void Conference::updateKeyIndicator(int value) {
    std::cout << "Для материалов конференции \"" << title << "\" учтено дополнительных ссылок: " << value << "\n";
}

bool Conference::equals(const Publication& other) const {
    const auto* c = dynamic_cast<const Conference*>(&other);
    return c && hasSameCommonData(*c) && conferenceName == c->conferenceName;
}

void Conference::readFrom(std::istream& is) {
    Publication::readFrom(is);
    readConferenceName(is);
    readLocation(is);
}
