#include "Article.h"
#include <format>

Article::Article(std::string_view t, std::string_view a, int y, std::string_view jName, int issue, std::weak_ptr<ScientificLibrary> lib)
    : Publication(t, a, y, lib), journalName(jName), issueNumber(issue) {
}

std::string_view Article::getJournalName() const { return journalName; }
void Article::setJournalName(std::string_view name) { journalName = name; }
void Article::printJournalName(std::ostream& os) const { os << "Журнал: " << journalName; }
void Article::readJournalName(std::istream& is) { setJournalName(readLine(is, "Введите название журнала: ")); }

int Article::getIssueNumber() const { return issueNumber; }
void Article::setIssueNumber(int issue) {
    if (issue <= 0) throw std::invalid_argument("Ошибка: номер выпуска должен быть положительным!");
    issueNumber = issue;
}
void Article::printIssueNumber(std::ostream& os) const { os << "Выпуск №" << issueNumber; }
void Article::readIssueNumber(std::istream& is) { setIssueNumber(readInt(is, "Введите номер выпуска: ")); }

std::string_view Article::getType() const { return "Статья"; }

void Article::printInformation(std::ostream& os) const {
    Publication::printInformation(os);
    os << " | ";
    printJournalName(os);
    os << " | ";
    printIssueNumber(os);
}

bool Article::equals(const Publication& other) const {
    const auto* a = dynamic_cast<const Article*>(&other);
    return a && hasSameCommonData(*a) && journalName == a->journalName && issueNumber == a->issueNumber;
}

void Article::readFrom(std::istream& is) {
    Publication::readFrom(is);
    readJournalName(is);
    readIssueNumber(is);
}

int Article::getLoanPeriod() const { return getYear() >= CURRENT_YEAR - 1 ? 3 : 7; }
int Article::getAllowedExtension(int requestedDays) const { return getYear() >= CURRENT_YEAR - 1 ? 0 : limitDays(requestedDays, 3); }

std::string Article::getCitation() const {
    return std::format("{} {} // {}. — {}. — №{}.", getAuthor(), getTitle(), journalName, getYear(), issueNumber);
}
