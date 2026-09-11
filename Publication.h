#pragma once
#include <iostream>
#include <string>

class Publication {
private:
    std::string title;
    std::string author;
    std::string type;
    int year;
    bool isBorrowed;

public:
    Publication(std::string t, std::string a, std::string tp, int y);

    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getType() const;
    int getYear() const;
    bool getIsBorrowed() const;

    void setTitle(const std::string& t);
    void setAuthor(const std::string& a);
    void setType(const std::string& tp);
    void setYear(int y);
    void setBorrowed(bool status);

    void printInfo() const;
};
