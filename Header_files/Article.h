#pragma once
#include "Publication.h"

class Article : public Publication {
private:
    std::string journalName;
    int issueNumber;
public:
    Article();
    Article(std::string_view t, std::string_view a, int y, std::string_view jName, int issue, std::weak_ptr<ScientificLibrary> lib = {});

    std::string_view getType() const override;
    void printSpecific(std::ostream& os) const override;
    void readSpecific(std::istream& is) override;
};
