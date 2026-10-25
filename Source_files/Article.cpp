#include "Article.h"
#include <iostream>

Article::Article() : Publication("", "", 2023), issueNumber(1) {}

Article::Article(std::string_view t, std::string_view a, int y, std::string_view jName, int issue, std::weak_ptr<ScientificLibrary> lib)
    : Publication(t, a, y, lib), journalName(jName), issueNumber(issue) {}

std::string_view Article::getType() const {
    return "Статья";
}

void Article::printSpecific(std::ostream& os) const {
    os << " | Журнал: " << journalName << " (№" << issueNumber << ")";
}

void Article::readSpecific(std::istream& is) {
    std::cout << "Введите название научного журнала: ";
    std::getline(is >> std::ws, journalName);

    std::cout << "Введите номер выпуска: ";
    safeReadNumber(is, issueNumber, 1);
}
