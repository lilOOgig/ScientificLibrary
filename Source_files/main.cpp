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
    setlocale(LC_ALL, "Russian");

    auto lib = std::make_shared<ScientificLibrary>("Научная Библиотека ВУЗа", 50);

    // Из версии 1 сохранены аргументы PublicationType::Book / PublicationType::Article
    auto p1 = std::make_shared<Publication>("Квантовая механика", "Ландау Л.Д.", PublicationType::Book, 1989, lib);
    auto p2 = std::make_shared<Publication>("Теория алгоритмов", "Кормен Т.", PublicationType::Book, 2013, lib);
    auto p3 = std::make_shared<Publication>("Нейросети и обработка данных", "Иванов А.А.", PublicationType::Article, 2023, lib);

    try {
        // [ИЗ ВЕРСИИ 2] Добавление элементов через оператор +=
        *lib += p1;
        *lib += p2;
        *lib += p3;
    }
    catch (const std::exception& e) { // [ИЗ ВЕРСИИ 2] Обработка исключений
        std::cerr << e.what() << '\n';
    }

    int userChoice = -1;
    while (userChoice != 0) {
        std::cout << "\n=== Управление библиотекой ===\n"
            << "1. Показать весь каталог\n"
            << "2. Выдать книгу читателю\n"
            << "3. Принять книгу обратно\n"
            << "4. Найти книги по автору\n"
            << "5. Ввести новую публикацию\n"  // [ИЗ ВЕРСИИ 2] Новый пункт меню
            << "6. Удалить публикацию\n"        // [ИЗ ВЕРСИИ 2] Новый пункт меню
            << "7. Сравнить книги\n"             // [ИЗ ВЕРСИИ 2] Новый пункт меню
            << "8. Посчитать разницу лет\n"     // [ИЗ ВЕРСИИ 2] Новый пункт меню
            << "0. Выйти из программы\n";

        userChoice = readNumber("Выберите команду: ");

        try { // [ИЗ ВЕРСИИ 2] Оборачивание обработки команд в try-catch
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
            case 5: { // [ИЗ ВЕРСИИ 2] Ввод через оператор >> и добавление через +=
                auto newPub = std::make_shared<Publication>();
                std::cin >> *newPub; 
                *lib += newPub;    
                break;
            }
            case 6: // [ИЗ ВЕРСИИ 2] Удаление через оператор -=
                *lib -= p3; 
                break;
            case 7: { // [ИЗ ВЕРСИИ 2] Использование перегруженных операторов == и <
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
            case 8: { // [ИЗ ВЕРСИИ 2] Вызов дружественной функции getYearDifference
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
        catch (const std::exception& e) { // [ИЗ ВЕРСИИ 2] Перехват исключений
            std::cout << "\n[ОБРАБОТКА ИСКЛЮЧЕНИЯ]: " << e.what() << "\n";
        }
        
    }

    return 0;
}
