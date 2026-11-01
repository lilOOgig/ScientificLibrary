#pragma once
#include "Publication.h"

class Book : public Publication {
private:
    int pageCount;
public:
    Book(std::string_view t = "", std::string_view a = "", int y = 2000, int pages = 100, std::weak_ptr<ScientificLibrary> lib = {});

    int getPageCount() const;
    void setPageCount(int pages);
    void printPageCount(std::ostream& os) const;
    void readPageCount(std::istream& is);

    // Уникальный метод книги
    void addPages(int count);

    std::string_view getType() const override;
    void printInformation(std::ostream& os) const override;
    void readFrom(std::istream& is) override;
    double getKeyIndicator() const override;
    std::string getKeyIndicatorName() const override;
    void updateKeyIndicator(int value) override;
    bool equals(const Publication& other) const override;
};
