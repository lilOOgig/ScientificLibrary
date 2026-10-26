#include "Monograph.h"
#include <iostream>

Monograph::Monograph(std::string_view t, std::string_view a, int y, std::string_view isbnVal, int circ, std::weak_ptr<ScientificLibrary> lib)
    : Publication(t, a, y, lib), isbn(isbnVal), circulation(circ) {
}

std::string_view Monograph::getType() const { return "Монография"; }

void Monograph::printInformation(std::ostream& os) const {
    os << "[Монография] \"" << title << "\" — " << author << " (" << year << " г.) | ISBN: " << isbn << " | Тираж: " << circulation << " экз.";
}

double Monograph::calculateSpecificValue() const { return static_cast<double>(circulation); }

void Monograph::applyEffect(int value) {
    circulation += value;
    std::cout << "Тираж монографии \"" << title << "\" увеличен на " << value << ". Новый тираж: " << circulation << " экз.\n";
}

void Monograph::readFrom(std::istream& is) {
    std::cout << "Введите название монографии: ";
    std::getline(is >> std::ws, title);
    std::cout << "Введите автора: ";
    std::getline(is, author);
    std::cout << "Введите год издания: ";
    int y; is >> y; setYear(y);
    std::cout << "Введите ISBN: ";
    std::getline(is >> std::ws, isbn);
    std::cout << "Введите тираж: ";
    is >> circulation;
}

bool Monograph::equals(const Publication& other) const {
    const auto* m = dynamic_cast<const Monograph*>(&other);
    return m && title == m->title && author == m->author && year == m->year && isbn == m->isbn;
}

std::string Monograph::getValueName() const { return "Тираж (экземпляров)"; }