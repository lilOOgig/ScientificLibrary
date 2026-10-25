#pragma once
#include "Publication.h"

class Journal : public Publication {
private:
    int volumeNumber;     // Том
    std::string publisher; // Издательство
public:
    Journal();
    Journal(std::string_view t, std::string_view a, int y, int volume, std::string_view pub, std::weak_ptr<ScientificLibrary> lib = {});

    std::string_view getType() const override;
    void printSpecific(std::ostream& os) const override;
    void readSpecific(std::istream& is) override;
};
