#pragma once
#include "Publication.h"

class Journal : public Publication {
private:
    int volumeNumber;
    std::string publisher;
public:
    Journal(std::string_view t = "", std::string_view a = "", int y = 2022, int volume = 1, std::string_view pub = "Издательство", std::weak_ptr<ScientificLibrary> lib = {});

    std::string_view getType() const override;
    void printInformation(std::ostream& os) const override;
    double calculateSpecificValue() const override; // Специфический параметр: номер тома
    void applyEffect(int value) override;            // Изменение тома
    void readFrom(std::istream& is) override;
    bool equals(const Publication& other) const override;
    std::string getValueName() const override;
};
