#pragma once
#include "Publication.h"

class Article : public Publication {
private:
    std::string journalName;
    int issueNumber;
public:
    Article(std::string_view t = "", std::string_view a = "", int y = 2020, std::string_view jName = "Вестник ИТ", int issue = 1, std::weak_ptr<ScientificLibrary> lib = {});

    std::string_view getJournalName() const;
    void setJournalName(std::string_view name);
    void printJournalName(std::ostream& os) const;
    void readJournalName(std::istream& is);

    int getIssueNumber() const;
    void setIssueNumber(int issue);
    void printIssueNumber(std::ostream& os) const;
    void readIssueNumber(std::istream& is);

    // Уникальный метод статьи
    void moveToIssue(int newIssue);

    std::string_view getType() const override;
    void printInformation(std::ostream& os) const override;
    void readFrom(std::istream& is) override;
    double getKeyIndicator() const override;
    std::string getKeyIndicatorName() const override;
    void updateKeyIndicator(int value) override;
    bool equals(const Publication& other) const override;
};
