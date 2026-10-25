#include "Conference.h"
#include <iostream>

Conference::Conference() : Publication("", "", 2023) {}

Conference::Conference(std::string_view t, std::string_view a, int y, std::string_view confName, std::string_view loc, std::weak_ptr<ScientificLibrary> lib)
    : Publication(t, a, y, lib), conferenceName(confName), location(loc) {}

std::string_view Conference::getType() const { return "Конференция"; }

void Conference::printSpecific(std::ostream& os) const {
    os << " | Конференция: " << conferenceName << " (" << location << ")";
}

void Conference::readSpecific(std::istream& is) {
    std::cout << "Введите название конференции: ";
    std::getline(is >> std::ws, conferenceName);
    std::cout << "Введите место проведения (город): ";
    std::getline(is, location);
}
