#include "Monograph.h"

Monograph::Monograph(std::string_view t, std::string_view a, int y, std::string_view isbnVal, int circ, std::weak_ptr<ScientificLibrary> lib)
    : Publication(t, a, y, lib), isbn(isbnVal) {
    setCirculation(circ);
}

std::string_view Monograph::getIsbn() const { return isbn; }
void Monograph::setIsbn(std::string_view value) { isbn = value; }
void Monograph::printIsbn(std::ostream& os) const { os << "ISBN: " << isbn; }
void Monograph::readIsbn(std::istream& is) { setIsbn(readLine(is, "Введите ISBN: ")); }

int Monograph::getCirculation() const { return circulation; }
void Monograph::setCirculation(int circ) {
    if (circ <= 0) throw std::invalid_argument("Ошибка: тираж должен быть положительным!");
    circulation = circ;
}
void Monograph::printCirculation(std::ostream& os) const { os << "Тираж: " << circulation << " экз."; }
void Monograph::readCirculation(std::istream& is) { setCirculation(readInt(is, "Введите тираж: ")); }

std::string_view Monograph::getType() const { return "Монография"; }

void Monograph::printInformation(std::ostream& os) const {
    Publication::printInformation(os);
    os << " | ";
    printIsbn(os);
    os << " | ";
    printCirculation(os);
}

bool Monograph::equals(const Publication& other) const {
    const auto* m = dynamic_cast<const Monograph*>(&other);
    return m && hasSameCommonData(*m) && isbn == m->isbn;
}

void Monograph::readFrom(std::istream& is) {
    Publication::readFrom(is);
    readIsbn(is);
    readCirculation(is);
}

int Monograph::getLoanPeriod() const { return isLimitedEdition() ? 7 : 21; }
int Monograph::getAllowedExtension(int requestedDays) const { return isLimitedEdition() ? 0 : limitDays(requestedDays, 7); }

bool Monograph::isLimitedEdition() const { return circulation < 500; }
