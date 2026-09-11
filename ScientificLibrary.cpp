#include "Publication.h"
#include "ScientificLibrary.h"

// --- Реализация Publication ---
Publication::Publication(std::string t, std::string a, std::string tp, int y)
    : title(t), author(a), type(tp), year(y), isBorrowed(false) {
}

std::string Publication::getTitle() const { return title; }
std::string Publication::getAuthor() const { return author; }
std::string Publication::getType() const { return type; }
int Publication::getYear() const { return year; }
bool Publication::getIsBorrowed() const { return isBorrowed; }

void Publication::setTitle(const std::string& t) { title = t; }
void Publication::setAuthor(const std::string& a) { author = a; }
void Publication::setType(const std::string& tp) { type = tp; }
void Publication::setYear(int y) { year = y; }
void Publication::setBorrowed(bool status) { isBorrowed = status; }

void Publication::printInfo() const {
    std::cout << "[" << type << "] \"" << title << "\" — " << author
        << " (" << year << " г.) | Статус: "
        << (isBorrowed ? "Выдана" : "В наличии") << std::endl;
}

// --- Реализация ScientificLibrary ---
ScientificLibrary::ScientificLibrary(std::string name) : libraryName(name) {}

void ScientificLibrary::addPublication(const Publication& pub) {
    catalog.push_back(pub);
    std::cout << "Добавлено в каталог: " << pub.getTitle() << std::endl;
}

void ScientificLibrary::printCatalog() const {
    std::cout << "\n====================================================================================" << std::endl;
    std::cout << "Каталог библиотеки: " << libraryName << std::endl;
    std::cout << "====================================================================================" << std::endl;
    if (catalog.empty()) {
        std::cout << "Каталог пуст." << std::endl;
        return;
    }
    for (size_t i = 0; i < catalog.size(); ++i) {
        std::cout << i + 1 << ". ";
        catalog[i].printInfo();
    }
    std::cout << "====================================================================================\n" << std::endl;
}

bool ScientificLibrary::issuePublication(const std::string& title, const std::string& researcherName) {
    for (auto& pub : catalog) {
        if (pub.getTitle() == title) {
            if (pub.getIsBorrowed()) {
                std::cout << "ОШИБКА: Материал \"" << title
                    << "\" уже выдан другому исследователю!" << std::endl;
                return false;
            }
            pub.setBorrowed(true);
            std::cout << "УСПЕХ: Материал \"" << title
                << "\" успешно выдан исследователю " << researcherName << "." << std::endl;
            return true;
        }
    }
    std::cout << "ОШИБКА: Публикация с названием \"" << title << "\" не найдена." << std::endl;
    return false;
}

void ScientificLibrary::returnPublication(const std::string& title) {
    for (auto& pub : catalog) {
        if (pub.getTitle() == title) {
            if (!pub.getIsBorrowed()) {
                std::cout << "Материал \"" << title << "\" и так находится в библиотеке." << std::endl;
                return;
            }
            pub.setBorrowed(false);
            std::cout << "Материал \"" << title << "\" успешно возвращен в библиотеку." << std::endl;
            return;
        }
    }
    std::cout << "ОШИБКА: Публикация не найдена." << std::endl;
}

void ScientificLibrary::searchByAuthor(const std::string& author) const {
    std::cout << "\nРезультаты поиска по автору \"" << author << "\":" << std::endl;
    bool found = false;
    for (const auto& pub : catalog) {
        if (pub.getAuthor() == author) {
            pub.printInfo();
            found = true;
        }
    }
    if (!found) {
        std::cout << "Ничего не найдено." << std::endl;
    }
}