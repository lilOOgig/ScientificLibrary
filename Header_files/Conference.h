#pragma once
#include "Publication.h"

class Conference : public Publication {
private:
    std::string Name;
    std::string location;
public:
    explicit Conference(std::string_view t = "", std::string_view a = "", int y = 2024, std::string_view confName = "ИТ-Форум", std::string_view loc = "Москва", std::weak_ptr<ScientificLibrary> lib = {});

    // Уникальное поле: название конференции
    std::string_view getConferenceName() const;
    void setConferenceName(std::string_view name);
    void printConferenceName(std::ostream& os) const;
    void readConferenceName(std::istream& is);

    // Уникальное поле: место проведения
    std::string_view getLocation() const;
    void setLocation(std::string_view loc);
    void printLocation(std::ostream& os) const;
    void readLocation(std::istream& is);

    // Уникальный метод класса
    int getAge(int currentYear = CURRENT_YEAR) const;

    std::string_view getType() const override;
    void printInformation(std::ostream& os) const override;
    void readFrom(std::istream& is) override;
    int getLoanPeriod() const override;
    int getAllowedExtension(int requestedDays) const override;
    bool equals(const Publication& other) const override;
};
