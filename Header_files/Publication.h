#pragma once
#include <iostream>
#include <string>
#include <string_view>
#include <memory>
#include <limits>
#include <stdexcept>

class ScientificLibrary;

class Publication {
protected:
    std::string title;
    std::string author;
    int year;
    bool isBorrowed;
    std::weak_ptr<ScientificLibrary> libraryRef;

    // Общий метод для предотвращения дублирования кода ввода (для SonarQube)
    static void safeReadNumber(std::istream& is, int& value, int defaultValue) {
        if (!(is >> value)) {
            is.clear();
            value = defaultValue;
        }
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

public:
    Publication();
    Publication(std::string_view t, std::string_view a, int y, std::weak_ptr<ScientificLibrary> lib = {});

    virtual ~Publication() = default;

    std::string_view getTitle() const;
    std::string_view getAuthor() const;
    int getYear() const;
    bool getIsBorrowed() const;

    void setTitle(std::string_view t);
    void setAuthor(std::string_view a);
    void setYear(int y);
    void setBorrowed(bool status);

    virtual std::string_view getType() const = 0;

    virtual void printSpecific(std::ostream& os) const;
    virtual void readSpecific(std::istream& is);

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

