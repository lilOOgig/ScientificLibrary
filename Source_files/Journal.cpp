#include "Journal.h"

Journal::Journal(std::string_view t, std::string_view a, int y, int volume, std::string_view pub, std::weak_ptr<ScientificLibrary> lib)
    : Publication(t, a, y, lib), volumeNumber(volume), publisher(pub) {
}

int Journal::getVolumeNumber() const { return volumeNumber; }
void Journal::setVolumeNumber(int volume) {
    if (volume <= 0) throw std::invalid_argument("Ошибка: номер тома должен быть положительным!");
    volumeNumber = volume;
}
void Journal::printVolumeNumber(std::ostream& os) const { os << "Том: " << volumeNumber; }
void Journal::readVolumeNumber(std::istream& is) { setVolumeNumber(readInt(is, "Введите номер тома: ")); }

std::string_view Journal::getPublisher() const { return publisher; }
void Journal::setPublisher(std::string_view pub) { publisher = pub; }
void Journal::printPublisher(std::ostream& os) const { os << "Издательство: " << publisher; }
void Journal::readPublisher(std::istream& is) { setPublisher(readLine(is, "Введите издательство: ")); }

void Journal::nextVolume() { ++volumeNumber; }

std::string_view Journal::getType() const { return "Журнал"; }

void Journal::printInformation(std::ostream& os) const {
    Publication::printInformation(os);
    os << " | ";
    printVolumeNumber(os);
    os << " | ";
    printPublisher(os);
}

double Journal::getKeyIndicator() const { return static_cast<double>(volumeNumber); }
std::string Journal::getKeyIndicatorName() const { return "Номер тома"; }

void Journal::updateKeyIndicator(int value) {
    volumeNumber += value;
    std::cout << "Номер тома журнала \"" << title << "\" изменен на: " << volumeNumber << "\n";
}

bool Journal::equals(const Publication& other) const {
    const auto* j = dynamic_cast<const Journal*>(&other);
    return j && hasSameCommonData(*j) && volumeNumber == j->volumeNumber;
}

void Journal::readFrom(std::istream& is) {
    Publication::readFrom(is);
    readVolumeNumber(is);
    readPublisher(is);
}
