#include "Journal.h"
#include <iostream>

Journal::Journal(std::string_view t, std::string_view a, int y, int volume, std::string_view pub, std::weak_ptr<ScientificLibrary> lib)
    : Publication(t, a, y, lib), volumeNumber(volume), publisher(pub) {
}

std::string_view Journal::getType() const { return "Журнал"; }

void Journal::printInformation(std::ostream& os) const {
    os << "[Журнал] \"" << title << "\" — " << author << " (" << year << " г.) | Том: " << volumeNumber << " | Издательство: " << publisher;
}

double Journal::calculateSpecificValue() const { return static_cast<double>(volumeNumber); }

void Journal::applyEffect(int value) {
    volumeNumber += value;
    std::cout << "Номер тома журнала \"" << title << "\" изменен на: " << volumeNumber << "\n";
}

void Journal::readFrom(std::istream& is) {
    std::cout << "Введите название журнала: ";
    std::getline(is >> std::ws, title);
    std::cout << "Введите автора/редактора: ";
    std::getline(is, author);
    std::cout << "Введите год издания: ";
    int y; is >> y; setYear(y);
    std::cout << "Введите номер тома: ";
    is >> volumeNumber;
    std::cout << "Введите издательство: ";
    std::getline(is >> std::ws, publisher);
}

bool Journal::equals(const Publication& other) const {
    const auto* j = dynamic_cast<const Journal*>(&other);
    return j && title == j->title && author == j->author && year == j->year && volumeNumber == j->volumeNumber;
}

std::string Journal::getValueName() const { return "Номер тома"; }