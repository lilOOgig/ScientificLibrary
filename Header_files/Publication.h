#pragma once
#include <iostream>
#include <string>
#include <string_view>
#include <memory>

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
    Publication(std::string_view t, std::string_view a, PublicationType tp, int y, std::weak_ptr<ScientificLibrary> lib);

    std::string_view getTitle() const;
    std::string_view getAuthor() const;
    PublicationType getType() const; 
    int getYear() const;
    bool getIsBorrowed() const;

    void setTitle(std::string_view t);
    void setAuthor(std::string_view a);
    void setType(std::string_view tp);
    void setYear(int y);
    void setBorrowed(bool status);

    void printInfo() const;
    std::string_view getTypeAsString() const;
};
