#pragma once
#include "Publication.h"

class Book : public Publication {
private:
    int pageCount;
public:
    Book();
    Book(std::string_view t, std::string_view a, int y, int pages, std::weak_ptr<ScientificLibrary> lib = {});
    int getPageCount() const;

    std::string_view getType() const override;
    void printSpecific(std::ostream& os) const override;
    void readSpecific(std::istream& is) override;
};
