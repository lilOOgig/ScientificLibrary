#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include "ScientificLibrary.h"
#include "Publication.h"

int readNumber(std::string_view prompt) {
    std::string line;
    int val;
    char tail;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, line);
        if (std::stringstream ss(line); ss >> val && !(ss >> tail)) {
            return val;
        }
        std::cout << "Неверный ввод! Введите целое число.\n";
    }
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    std::setlocale(LC_ALL, "Russian");

    auto lib = std::make_shared<ScientificLibrary>("Научная Библиотека ВУЗа", 50);

    auto p1 = std::make_shared<Publication>("Квантовая механика", "Ландау Л.Д.", "Книга", 1989, lib);
    auto p2 = std::make_shared<Publication>("Теория алгоритмов", "Кормен Т.", "Книга", 2013, lib);
    auto p3 = std::make_shared<Publication>("Нейросети и обработка данных", "Иванов А.А.", "Статья", 2023, lib);

    lib->addPublication(p1);
    lib->addPublication(p2);
    lib->addPublication(p3);

    int userChoice = -1;
    while (userChoice != 0) {
        std::cout << "\n=== Управление библиотекой ===\n"
            << "1. Показать весь каталог\n"
            << "2. Выдать книгу читателю\n"
            << "3. Принять книгу обратно\n"
            << "4. Найти книги по автору\n"
            << "5. Изменить год издания книги\n"
            << "0. Выйти из программы\n";

        userChoice = readNumber("Выберите команду: ");

        switch (userChoice) {
        case 1:
            lib->showCatalog();
            break;
        case 2:
            lib->issuePublication("Квантовая механика", "д-р Сидоров");
            break;
        case 3:
            lib->returnPublication("Квантовая механика");
            break;
        case 4:
            lib->searchByAuthor("Кормен Т.");
            break;
        case 5:
            p1->setYear(2025);
            std::cout << "Год издания успешно изменен!\n";
            p1->printInfo();
            break;
        case 0:
            std::cout << "Программа завершена.\n";
            break;
        default:
            std::cout << "Такого пункта нет в меню!\n";
        }
    }

    return 0;
}
