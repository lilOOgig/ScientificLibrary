#pragma once
#include <iostream>
#include <string>
#include <string_view>
#include <memory>
#include <stdexcept> 

class ScientificLibrary;

enum class PublicationType {
    Article,     
    Book, 
    Journal,
    Monograph,    
    Conference    
};

std::string_view typeToString(PublicationType type);

class Publication {
private:
    std::string title;
    std::string author;
    PublicationType type;
    int year;
    bool isBorrowed;
    std::weak_ptr<ScientificLibrary> libraryRef;

public:
    Publication();
    Publication(std::string_view t, std::string_view a, PublicationType tp, int y, std::weak_ptr<ScientificLibrary> lib = {});

    std::string_view getTitle() const;
    std::string_view getAuthor() const;
    PublicationType getType() const;
    int getYear() const;
    bool getIsBorrowed() const;

    void setTitle(std::string_view t);
    void setAuthor(std::string_view a);
    void setType(PublicationType tp);
    void setYear(int y);
    void setBorrowed(bool status);

    void printInfo() const;

    bool operator==(const Publication& other) const;
    bool operator!=(const Publication& other) const;

    bool operator>(const Publication& other) const;
    bool operator<(const Publication& other) const;
    bool operator>=(const Publication& other) const;
    bool operator<=(const Publication& other) const;

    friend int getYearDifference(const Publication& p1, const Publication& p2);

    // [ИЗ ВЕРСИИ 2] Дружественные операторы ввода/вывода в поток
    friend std::ostream& operator<<(std::ostream& os, const Publication& pub);
    friend std::istream& operator>>(std::istream& is, Publication& pub);
};
