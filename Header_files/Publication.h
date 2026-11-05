#pragma once
#include <iostream>
#include <string>
#include <string_view>
#include <memory>
#include <stdexcept>

class ScientificLibrary;

// Абстрактный базовый класс иерархии изданий
class Publication {
public:
    Publication(std::string_view title, std::string_view author, int year, std::weak_ptr<ScientificLibrary> lib = {});
    virtual ~Publication() = default;

    static constexpr int CURRENT_YEAR = 2026;

    // Чисто виртуальные методы: у каждого типа издания своя реализация
    virtual std::string_view getType() const = 0;               // тип издания
    virtual int getLoanPeriod() const = 0;                      // срок выдачи в днях (зависит от типа)
    virtual int getAllowedExtension(int requestedDays) const = 0; // на сколько дней можно продлить (зависит от типа)
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

    // Вывод и ввод каждого общего поля отдельно
    void printTitle(std::ostream& os) const;
    void printAuthor(std::ostream& os) const;
    void printYear(std::ostream& os) const;
    void readTitle(std::istream& is);
    void readAuthor(std::istream& is);
    void readYear(std::istream& is);

    friend std::ostream& operator<<(std::ostream& os, const Publication& pub);
    friend std::istream& operator>>(std::istream& is, Publication& pub);   // вызывает readFrom

    // Сравнение изданий по сроку выдачи
    bool operator<(const Publication& other) const;
    bool operator>(const Publication& other) const;
    bool operator<=(const Publication& other) const;
    bool operator>=(const Publication& other) const;
    bool operator==(const Publication& other) const;
    bool operator!=(const Publication& other) const;

protected:
    static int limitDays(int days, int limit) { return days < 0 ? 0 : (days > limit ? limit : days); }
    bool hasSameCommonData(const Publication& other) const;

    static int readInt(std::istream& is, std::string_view prompt);
    static std::string readLine(std::istream& is, std::string_view prompt);

    std::string title;
    std::string author;
    int year;
    bool isBorrowed;
    std::weak_ptr<ScientificLibrary> libraryRef;
};
