#pragma once
#include "Publication.h"

class Article : public Publication {
private:
    std::string journalName;
    int issueNumber;
public:
    explicit Article(std::string_view t = "", std::string_view a = "", int y = 2020, std::string_view jName = "Вестник ИТ", int issue = 1, std::weak_ptr<ScientificLibrary> lib = {});

    // Уникальное поле: название журнала
    std::string_view getJournalName() const;
    void setJournalName(std::string_view name);
    void printJournalName(std::ostream& os) const;
    void readJournalName(std::istream& is);

    // Уникальное поле: номер выпуска
    int getIssueNumber() const;
    void setIssueNumber(int issue);
    void printIssueNumber(std::ostream& os) const;
    void readIssueNumber(std::istream& is);

    // Уникальный метод класса
    std::string getCitation() const;   // библиографическая ссылка

    std::string_view getType() const override;
    void printInformation(std::ostream& os) const override;
    void readFrom(std::istream& is) override;
    int getLoanPeriod() const override;
    int getAllowedExtension(int requestedDays) const override;
    bool equals(const Publication& other) const override;
};
