#pragma once
#include "Publication.h"

class Book : public Publication {
private:
    int pageCount;
public:
    explicit Book(std::string_view t = "", std::string_view a = "", int y = 2000, int pages = 100, std::weak_ptr<ScientificLibrary> lib = {});

    // Уникальное поле: количество страниц - доступ, вывод и ввод отдельно
    int getPageCount() const;
    void setPageCount(int pages);
    void printPageCount(std::ostream& os) const;
    void readPageCount(std::istream& is);

    // Уникальный метод класса
    int getReadingDays(int pagesPerDay) const;   // за сколько дней можно прочитать

    std::string_view getType() const override;
    void printInformation(std::ostream& os) const override;
    void readFrom(std::istream& is) override;
    int getLoanPeriod() const override;
    int getAllowedExtension(int requestedDays) const override;
    bool equals(const Publication& other) const override;
};
