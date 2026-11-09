#pragma once
#include "Publication.h"

class Conference : public Publication {
private:
    std::string conferenceName; // Исправлено с Name на conferenceName
    std::string location;
public:
    explicit Conference(std::string_view t = "", std::string_view a = "", int y = 2024, std::string_view confName = "ИТ-Форум", std::string_view loc = "Москва", std::weak_ptr<ScientificLibrary> lib = {});

    std::string_view getConferenceName() const;
    void setConferenceName(std::string_view name);
    void printConferenceName(std::ostream& os) const;
    void readConferenceName(std::istream& is);

    std::string_view getLocation() const;
    void setLocation(std::string_view loc);
    void printLocation(std::ostream& os) const;
    void readLocation(std::istream& is);

    int getAge(int currentYear = getCurrentYear()) const;

    std::string_view getType() const override;
    void printInformation(std::ostream& os) const override;
    void readFrom(std::istream& is) override;
    int getLoanPeriod() const override;
    int getAllowedExtension(int requestedDays) const override;
    bool equals(const Publication& other) const override;
};
