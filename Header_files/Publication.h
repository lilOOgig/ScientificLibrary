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

    // Чисто виртуальные методы: у каждого типа издания своя реализация
    virtual std::string_view getType() const = 0;               // тип издания
    virtual double getKeyIndicator() const = 0;                 // ключевой показатель (страницы, тираж, том...)
    virtual std::string getKeyIndicatorName() const = 0;        // название ключевого показателя
    virtual void updateKeyIndicator(int value) = 0;             // изменить ключевой показатель
    virtual bool equals(const Publication& other) const = 0;

    // Виртуальный метод с реализацией: общая часть, наследники дополняют своими полями
    virtual void printInformation(std::ostream& os) const;

    // Виртуальный метод ввода: база читает общие поля, наследники добавляют свои
    virtual void readFrom(std::istream& is);

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

    void printTitle(std::ostream& os) const;
    void printAuthor(std::ostream& os) const;
    void printYear(std::ostream& os) const;
    void readTitle(std::istream& is);
    void readAuthor(std::istream& is);
    void readYear(std::istream& is);

    friend std::ostream& operator<<(std::ostream& os, const Publication& pub);
    friend std::istream& operator>>(std::istream& is, Publication& pub); 

    bool operator<(const Publication& other) const;
    bool operator>(const Publication& other) const;
    bool operator<=(const Publication& other) const;
    bool operator>=(const Publication& other) const;
    bool operator==(const Publication& other) const;
    bool operator!=(const Publication& other) const;

protected:
    bool hasSameCommonData(const Publication& other) const;

    static int readInt(std::istream& is, std::string_view prompt);
    static std::string readLine(std::istream& is, std::string_view prompt);

    std::string title;
    std::string author;
    int year;
    bool isBorrowed;
    std::weak_ptr<ScientificLibrary> libraryRef;
};
