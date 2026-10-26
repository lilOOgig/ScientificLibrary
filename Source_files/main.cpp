#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <vector>
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

    // Инициализация библиотеки объектами разных типов
    *lib += std::make_shared<Book>("Квантовая механика", "Ландау Л.Д.", 1989, 450, lib);
    *lib += std::make_shared<Article>("Теория алгоритмов", "Кормен Т.", 2013, "Вестник ИТ", 4, lib);
    *lib += std::make_shared<Monograph>("Нейросети и обработка данных", "Иванов А.А.", 2023, "978-5-4461-1234-5", 1000, lib);
    *lib += std::make_shared<Journal>("Научный Вестник", "Коллектив", 2022, 12, "Наука", lib);
    *lib += std::make_shared<Conference>("Доклад по ИИ", "Петров П.П.", 2024, "ИТ-Форум", "Москва", lib);

    int userChoice = -1;
    while (userChoice != 0) {
        std::cout << "\n=== СИСТЕМА УПРАВЛЕНИЯ НАУЧНОЙ БИБЛИОТЕКОЙ ===\n"
            << "1. Показать весь каталог библиотеки\n"
            << "2. Изменить параметры всех изданий (добавить страниц/тираж)\n"
            << "3. Показать специфические характеристики изданий (страницы, тираж, тома)\n"
            << "4. Найти главное издание фонда (по максимальному профильному показателю)\n"
            << "5. Выдать издание читателю\n"
            << "6. Вернуть издание в библиотеку\n"
            << "7. Найти публикации по автору\n"
            << "8. Добавить новое издание в фонд\n"
            << "0. Выход из программы\n";

        userChoice = readNumber("Выберите действие: ");

        try {
            switch (userChoice) {
            case 1:
                lib->showCatalog();
                break;
            case 2: {
                int val = readNumber("Введите число для изменения параметров изданий: ");
                lib->applyMassEffect(val);
                std::cout << "Параметры успешно обновлены для всех объектов!\n";
                break;
            }
            case 3:
                lib->showSpecificValues();
                break;
            case 4:
                lib->findMostValuable();
                break;
            case 5:
                lib->issuePublication("Квантовая механика", "д-р Сидоров");
                break;
            case 6:
                lib->returnPublication("Квантовая механика");
                break;
            case 7:
                lib->searchByAuthor("Кормен Т.");
                break;
            case 8: {
                std::cout << "\nВыберите тип добавляемого издания:\n"
                    << "1 - Книга\n"
                    << "2 - Статья\n"
                    << "3 - Монография\n"
                    << "4 - Журнал\n"
                    << "5 - Конференция\n";
                int tChoice = readNumber("Ваш выбор: ");
                std::shared_ptr<Publication> newPub;
                if (tChoice == 1) newPub = std::make_shared<Book>();
                else if (tChoice == 2) newPub = std::make_shared<Article>();
                else if (tChoice == 3) newPub = std::make_shared<Monograph>();
                else if (tChoice == 4) newPub = std::make_shared<Journal>();
                else if (tChoice == 5) newPub = std::make_shared<Conference>();
                else { std::cout << "Неверный тип издания!\n"; break; }

                std::cin >> *newPub;
                *lib += newPub;
                break;
            }
            case 0:
                std::cout << "Завершение работы программы.\n";
                break;
            default:
                std::cout << "Ошибка: такого пункта нет в меню. Попробуйте снова.\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "\n[ОШИБКА]: " << e.what() << "\n";
        }
    }

    return 0;
}

