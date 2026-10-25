#include "Monograph.h"
#include <iostream>

Monograph::Monograph() : Publication("", "", 2020), circulation(500) {}

Monograph::Monograph(std::string_view t, std::string_view a, int y, std::string_view isbnVal, int circ, std::weak_ptr<ScientificLibrary> lib)
    : Publication(t, a, y, lib), isbn(isbnVal), circulation(circ) {}

std::string_view Monograph::getType() const { return "Монография"; }

void Monograph::printSpecific(std::ostream& os) const {
    os << " | ISBN: " << isbn << " | Тираж: " << circulation << " экз.";
}

void Monograph::readSpecific(std::istream& is) {
    std::cout << "Введите ISBN: ";
    std::getline(is >> std::ws, isbn);
    std::cout << "Введите тираж: ";
    safeReadNumber(is, circulation, 500);
}
