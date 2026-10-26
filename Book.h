#pragma once
#include "Publication.h"

class Book : public Publication {
private:
    int pageCount;
public:
    Book(std::string_view t = "", std::string_view a = "", int y = 2000, int pages = 100, std::weak_ptr<ScientificLibrary> lib = {});
    int getPageCount() const;

    std::string_view getType() const override;
    void printInformation(std::ostream& os) const override;
    double calculateSpecificValue() const override; // Специфический параметр: количество страниц
    void applyEffect(int value) override;            // Добавление страниц
    void readFrom(std::istream& is) override;
    bool equals(const Publication& other) const override;
    std::string getValueName() const override;
};