#pragma once
#include "Publication.h"

class Monograph : public Publication {
private:
    std::string isbn;
    int circulation;
public:
    Monograph(std::string_view t = "", std::string_view a = "", int y = 2023, std::string_view isbnVal = "000-0", int circ = 500, std::weak_ptr<ScientificLibrary> lib = {});

    std::string_view getIsbn() const;
    void setIsbn(std::string_view value);
    void printIsbn(std::ostream& os) const;
    void readIsbn(std::istream& is);

    int getCirculation() const;
    void setCirculation(int circ);
    void printCirculation(std::ostream& os) const;
    void readCirculation(std::istream& is);

    // Уникальный метод монографии
    void increaseCirculation(int copies);

    std::string_view getType() const override;
    void printInformation(std::ostream& os) const override;
    void readFrom(std::istream& is) override;
    double getKeyIndicator() const override;
    std::string getKeyIndicatorName() const override;
    void updateKeyIndicator(int value) override;
    bool equals(const Publication& other) const override;
};
