#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <limits>
#include <windows.h>

#include "ScientificLibrary.h"
#include "Publication.h"
#include "Book.h"
#include "Article.h"
#include "Monograph.h"
#include "Journal.h"
#include "Conference.h"

int readNumber(std::string_view prompt) {
    std::string line;
    int val;
    char tail;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, line)) {
            std::cin.clear();
            continue;
        }
        std::stringstream ss(line);
        if (ss >> val && !(ss >> tail)) {
            return val;
        }
        std::cout << "Неверный ввод! Введите целое число.\n";
    }
}

int main() {
    std::setlocale(LC_ALL, "Russian");

    SetConsoleCP(1251);        
    SetConsoleOutputCP(1251);

    auto lib = std::make_shared<ScientificLibrary>("Научная Библиотека ВУЗа", 50);

    // Создаем тестовые объекты производных классов
    auto p1 = std::make_shared<Book>("Квантовая механика", "Ландау Л.Д.", 1989, 450, lib);
    auto p2 = std::make_shared<Article>("Теория алгоритмов", "Кормен Т.", 2013, "Вестник ИТ", 4, lib);
    auto p3 = std::make_shared<Monograph>("Нейросети и обработка данных", "Иванов А.А.", 2023, "978-5-4461-1234-5", 1000, lib);

    try {
        *lib += p1;
        *lib += p2;
        *lib += p3;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    int userChoice = -1;
    while (userChoice != 0) {
        std::cout << "\n=== Управление библиотекой (Лабораторная №3: Наследование) ===\n"
            << "1. Показать весь каталог\n"
            << "2. Выдать книгу читателю\n"
            << "3. Принять книгу обратно\n"
            << "4. Найти книги по автору\n"
            << "5. Ввести новую публикацию (выбор типа)\n"
            << "6. Удалить публикацию\n"
            << "7. Сравнить книги\n"
            << "8. Посчитать разницу лет\n"
            << "0. Выйти из программы\n";

        userChoice = readNumber("Выберите команду: ");

        try {
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
            case 5: {
                std::cout << "\nВыберите тип создаваемого издания:\n"
                    << "1 - Книга (Book)\n"
                    << "2 - Статья (Article)\n"
                    << "3 - Монография (Monograph)\n"
                    << "4 - Журнал (Journal)\n"
                    << "5 - Конференция (Conference)\n";
                int typeChoice = readNumber("Ваш выбор: ");

                std::shared_ptr<Publication> newPub;

                if (typeChoice == 1) {
                    newPub = std::make_shared<Book>();
                }
                else if (typeChoice == 2) {
                    newPub = std::make_shared<Article>();
                }
                else if (typeChoice == 3) {
                    newPub = std::make_shared<Monograph>();
                }
                else if (typeChoice == 4) {
                    newPub = std::make_shared<Journal>();
                }
                else if (typeChoice == 5) {
                    newPub = std::make_shared<Conference>();
                }
                else {
                    std::cout << "Неверный тип издания!\n";
                    break;
                }

                std::cin >> *newPub; // Полиморфный ввод
                *lib += newPub;
                break;
            }
            case 6:
                *lib -= p3;
                break;
            case 7: {
                if (*p1 == *p2) {
                    std::cout << "Книги одинаковые.\n";
                }
                else {
                    std::cout << "Книги разные.\n";
                }

                if (*p1 < *p2) {
                    std::cout << "\"" << p1->getTitle() << "\" издана раньше, чем \"" << p2->getTitle() << "\".\n";
                }
                break;
            }
            case 8: {
                int diff = getYearDifference(*p1, *p2);
                std::cout << "Разница в годах издания: " << diff << " лет.\n";
                break;
            }
            case 0:
                std::cout << "Программа завершена.\n";
                break;
            default:
                std::cout << "Такого пункта нет в меню!\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "\n[ОБРАБОТКА ИСКЛЮЧЕНИЯ]: " << e.what() << "\n";
        }
    }

    return 0;
}
