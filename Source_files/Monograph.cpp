#include "Monograph.h"
#include <limits>
#include <iostream>

Monograph::Monograph() : Publication("", "", 2020), isbn("000-0-00-000000-0"), circulation(500) {}

Monograph::Monograph(std::string_view t, std::string_view a, int y, std::string_view isbnVal, int circ, std::weak_ptr<ScientificLibrary> lib)
    : Publication(t, a, y, lib), isbn(isbnVal), circulation(circ) {}

std::string_view Monograph::getType() const {
    return "Монография";
}

void Monograph::printSpecific(std::ostream& os) const {
    os << " | ISBN: " << isbn << " | Тираж: " << circulation << " экз.";
}

void Monograph::readSpecific(std::istream& is) {
    std::cout << "Введите ISBN: ";
    std::getline(is >> std::ws, isbn);

    std::cout << "Введите тираж: ";
    if (!(is >> circulation)) {
        is.clear();
        circulation = 500;
    }
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

