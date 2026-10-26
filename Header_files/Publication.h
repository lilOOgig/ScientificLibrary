#pragma once
#include <iostream>
#include <string>
#include <string_view>
#include <memory>
#include <stdexcept>

class ScientificLibrary;

class Publication {
public:
    Publication(std::string_view title, std::string_view author, int year, std::weak_ptr<ScientificLibrary> lib = {});
    virtual ~Publication() = default;

    // Чисто виртуальные методы (интерфейс базового класса)
    virtual std::string_view getType() const = 0;
    virtual void printInformation(std::ostream& os) const = 0;
    virtual double calculateSpecificValue() const = 0;   // Специфическое вычисление/параметр для типа
    virtual void applyEffect(int value) = 0;             // Специфическое действие над изданием
    virtual void readFrom(std::istream& is) = 0;
    virtual bool equals(const Publication& other) const = 0;
    virtual std::string getValueName() const = 0;        // Название специфического параметра

    // Геттеры и сеттеры
    std::string_view getTitle() const;
    std::string_view getAuthor() const;
    int getYear() const;
    bool getIsBorrowed() const;
    std::weak_ptr<ScientificLibrary> getLibraryRef() const;

    void setTitle(std::string_view t);
    void setAuthor(std::string_view a);
    void setYear(int y);
    void setBorrowed(bool status);
    void setLibraryRef(std::weak_ptr<ScientificLibrary> lib);

    // Перегрузка операторов
    friend std::ostream& operator<<(std::ostream& os, const Publication& pub);
    friend std::istream& operator>>(std::istream& is, Publication& pub);

    bool operator<(const Publication& other) const;
    bool operator>(const Publication& other) const;
    bool operator<=(const Publication& other) const;
    bool operator>=(const Publication& other) const;
    bool operator==(const Publication& other) const;
    bool operator!=(const Publication& other) const;

protected:
    std::string title;
    std::string author;
    int year;
    bool isBorrowed;
    std::weak_ptr<ScientificLibrary> libraryRef;
};
