#pragma once
#include "Publication.h"

class Book : public Publication {
private:
    int pageCount = 1;
public:
    explicit Book(std::string_view t = "", std::string_view a = "", int y = 2000, int pages = 100, std::weak_ptr<ScientificLibrary> lib = {});

    int getPageCount() const;
    void setPageCount(int pages);
    void printPageCount(std::ostream& os) const;
    void readPageCount(std::istream& is);

    int getReadingDays(int pagesPerDay) const;   // за сколько дней можно прочитать

    std::string_view getType() const override;
    void printInformation(std::ostream& os) const override;
    void readFrom(std::istream& is) override;
    int getLoanPeriod() const override;
    int getAllowedExtension(int requestedDays) const override;
    bool equals(const Publication& other) const override;
};
