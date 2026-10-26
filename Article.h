#pragma once
#include "Publication.h"

class Article : public Publication {
private:
    std::string journalName;
    int issueNumber;
public:
    Article(std::string_view t = "", std::string_view a = "", int y = 2020, std::string_view jName = "Вестник ИТ", int issue = 1, std::weak_ptr<ScientificLibrary> lib = {});

    std::string_view getType() const override;
    void printInformation(std::ostream& os) const override;
    double calculateSpecificValue() const override; // Специфический параметр: номер выпуска
    void applyEffect(int value) override;            // Обновление номера выпуска
    void readFrom(std::istream& is) override;
    bool equals(const Publication& other) const override;
    std::string getValueName() const override;
};