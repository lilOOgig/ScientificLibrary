#pragma once
#include "Publication.h"

class Monograph : public Publication {
private:
    std::string isbn;
    int circulation;
public:
    Monograph(std::string_view t = "", std::string_view a = "", int y = 2023, std::string_view isbnVal = "000-0", int circ = 500, std::weak_ptr<ScientificLibrary> lib = {});

    std::string_view getType() const override;
    void printInformation(std::ostream& os) const override;
    double calculateSpecificValue() const override; // Специфический параметр: тираж
    void applyEffect(int value) override;            // Увеличение тиража
    void readFrom(std::istream& is) override;
    bool equals(const Publication& other) const override;
    std::string getValueName() const override;
};