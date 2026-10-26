#include "Article.h"
#include <iostream>

Article::Article(std::string_view t, std::string_view a, int y, std::string_view jName, int issue, std::weak_ptr<ScientificLibrary> lib)
    : Publication(t, a, y, lib), journalName(jName), issueNumber(issue) {
}

std::string_view Article::getType() const { return "Статья"; }

void Article::printInformation(std::ostream& os) const {
    os << "[Статья] \"" << title << "\" — " << author << " (" << year << " г.) | Журнал: " << journalName << " №" << issueNumber;
}

double Article::calculateSpecificValue() const { return static_cast<double>(issueNumber); }

void Article::applyEffect(int value) {
    issueNumber += value;
    std::cout << "У статьи \"" << title << "\" обновлен номер выпуска. Новый номер: " << issueNumber << "\n";
}

void Article::readFrom(std::istream& is) {
    std::cout << "Введите название статьи: ";
    std::getline(is >> std::ws, title);
    std::cout << "Введите автора: ";
    std::getline(is, author);
    std::cout << "Введите год издания: ";
    int y; is >> y; setYear(y);
    std::cout << "Введите название журнала: ";
    std::getline(is >> std::ws, journalName);
    std::cout << "Введите номер выпуска: ";
    is >> issueNumber;
}

bool Article::equals(const Publication& other) const {
    const auto* a = dynamic_cast<const Article*>(&other);
    return a && title == a->title && author == a->author && year == a->year && journalName == a->journalName && issueNumber == a->issueNumber;
}

std::string Article::getValueName() const { return "Номер выпуска"; }