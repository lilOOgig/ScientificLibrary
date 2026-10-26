#pragma once
#include "Publication.h"

class Conference : public Publication {
private:
    std::string conferenceName;
    std::string location;
public:
    Conference();
    Conference(std::string_view t, std::string_view a, int y, std::string_view confName, std::string_view loc, std::weak_ptr<ScientificLibrary> lib = {});

    std::string_view getType() const override;
    void printSpecific(std::ostream& os) const override;
    void readSpecific(std::istream& is) override;
};
