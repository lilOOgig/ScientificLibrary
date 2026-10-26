#pragma once
#include "Publication.h"

class Monograph : public Publication {
private:
    std::string isbn;
    int circulation;
public:
    Monograph();
    Monograph(std::string_view t, std::string_view a, int y, std::string_view isbnVal, int circ, std::weak_ptr<ScientificLibrary> lib = {});

    std::string_view getType() const override;
    void printSpecific(std::ostream& os) const override;
    void readSpecific(std::istream& is) override;
};
