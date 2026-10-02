#pragma once
#include <iostream>
#include <string>
#include <string_view>
#include <memory>

class ScientificLibrary;

class Publication {
private:
    std::string title;
    std::string author;
    std::string type;
    int year;
    bool isBorrowed;
    std::weak_ptr<ScientificLibrary> libraryRef;

public:
    Publication() : title(""), author(""), type(""), year(0), isBorrowed(false) {}
    Publication(std::string_view t, std::string_view a, std::string_view tp, int y, std::weak_ptr<ScientificLibrary> lib);

    std::string_view getTitle() const;
    std::string_view getAuthor() const;
    std::string_view getType() const;
    int getYear() const;
    bool getIsBorrowed() const;

    void setTitle(std::string_view t);
    void setAuthor(std::string_view a);
    void setType(std::string_view tp);
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
    friend std::ostream& operator<<(std::ostream& os, const Publication& pub);
    friend std::istream& operator>>(std::istream& is, Publication& pub);
};
