#pragma once
#include "Publication.h"

class Conference : public Publication {
private:
    std::string conferenceName;
    std::string location;
public:
    Conference(std::string_view t = "", std::string_view a = "", int y = 2024, std::string_view confName = "ИТ-Форум", std::string_view loc = "Москва", std::weak_ptr<ScientificLibrary> lib = {});

    std::string_view getType() const override;
    void printInformation(std::ostream& os) const override;
    double calculateSpecificValue() const override; // Специфический параметр: давность доклада в годах
    void applyEffect(int value) override;
    void readFrom(std::istream& is) override;
    bool equals(const Publication& other) const override;
    std::string getValueName() const override;
};
