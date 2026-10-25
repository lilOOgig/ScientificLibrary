#include "Journal.h"
#include <iostream>

Journal::Journal() : Publication("", "", 2024), volumeNumber(1) {}

Journal::Journal(std::string_view t, std::string_view a, int y, int volume, std::string_view pub, std::weak_ptr<ScientificLibrary> lib)
    : Publication(t, a, y, lib), volumeNumber(volume), publisher(pub) {}

std::string_view Journal::getType() const { return "Журнал"; }

void Journal::printSpecific(std::ostream& os) const {
    os << " | Том: " << volumeNumber << " | Издательство: " << publisher;
}

void Journal::readSpecific(std::istream& is) {
    std::cout << "Введите номер тома: ";
    safeReadNumber(is, volumeNumber, 1);
    std::cout << "Введите название издательства: ";
    std::getline(is, publisher);
}
