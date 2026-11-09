#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <vector>
#include <limits>
#ifdef _WIN32
#include <Windows.h>
#endif

#include "ScientificLibrary.h"
#include "Publication.h"
#include "Book.h"
#include "Article.h"
#include "Monograph.h"
#include "Journal.h"
#include "Conference.h"
#include "Algs.h" // Подключаем наши шаблонные алгоритмы обработки

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
        if (std::stringstream ss(line); ss >> val && !(ss >> tail)) {
            return val;
        }
        std::cout << "Неверный ввод! Введите целое число.\n";
    }
}

void demonstratePolymorphism(const ScientificLibrary& lib) {
    std::cout << "\n=== Полиморфные вызовы через интерфейс Publication ===\n";
    for (const auto& item : lib.getItems()) {
        const std::shared_ptr<Publication>& ptr = item;   
        const Publication& ref = *item;                   

        std::cout << "Тип (через указатель): " << ptr->getType() << "\n";
        std::cout << "Информация (через ссылку): ";
        ref.printInformation(std::cout);
        std::cout << "\n";
        std::cout << "Срок выдачи: " << ptr->getLoanPeriod() << " дн., максимум продления: "
            << ptr->getAllowedExtension(30) << " дн.\n\n";
    }
}

void demonstrateUniqueMethods(const ScientificLibrary& lib) {
    std::cout << "\n=== Унаследованные и уникальные свойства классов ===\n";
    for (const auto& item : lib.getItems()) {
        std::cout << "--- " << item->getType() << " ---\n";

        std::cout << "Унаследованные: ";
        item->printTitle(std::cout);  std::cout << " | ";
        item->printAuthor(std::cout); std::cout << " | ";
        item->printYear(std::cout);   std::cout << "\n";

        std::cout << "Собственные: ";
        if (auto book = std::dynamic_pointer_cast<Book>(item)) {
            book->printPageCount(std::cout);
            std::cout << "\nУникальный метод: при 30 стр. в день читать " << book->getReadingDays(30) << " дн.\n";
        }
        else if (auto mono = std::dynamic_pointer_cast<Monograph>(item)) {
            mono->printIsbn(std::cout); std::cout << " | "; mono->printCirculation(std::cout);
            std::cout << "\nУникальный метод: ограниченный тираж - " << (mono->isLimitedEdition() ? "да" : "нет") << "\n";
        }
        else if (auto article = std::dynamic_pointer_cast<Article>(item)) {
            article->printJournalName(std::cout); std::cout << " | "; article->printIssueNumber(std::cout);
            std::cout << "\nУникальный метод: ссылка - " << article->getCitation() << "\n";
        }
        else if (auto journal = std::dynamic_pointer_cast<Journal>(item)) {
            journal->printVolumeNumber(std::cout); std::cout << " | "; journal->printPublisher(std::cout);
            std::cout << "\nУникальный метод: свежий выпуск - " << (journal->isCurrent() ? "да" : "нет") << "\n";
        }
        else if (auto conf = std::dynamic_pointer_cast<Conference>(item)) {
            conf->printConferenceName(std::cout); std::cout << " | "; conf->printLocation(std::cout);
            std::cout << "\nУникальный метод: доклад сделан " << conf->getAge() << " г. назад\n";
        }
        std::cout << "\n";
    }
}

// Новая демонстрация шаблонных алгоритмов из файла algs.h и методов Collection
void demonstrateTemplatesAndAlgorithms(const ScientificLibrary& lib) {
    std::cout << "\n=== ДЕМОНСТРАЦИЯ ШАБЛОНОВ И АЛГОРИТМОВ (Лабораторная работа №5) ===\n";
    
    const auto& collection = lib.getItems();

    // 1. Использование шаблонной функции maxByMetric
    auto maxPub = maxByMetric(collection);
    if (maxPub) {
        std::cout << "[Шаблонная функция maxByMetric]: Найдено издание с максимальной метрикой срока выдачи -> " 
                  << maxPub->getType() << " \"" << maxPub->getTitle() << "\" (" << maxPub->getLoanPeriod() << " дн.)\n";
    }

    // 2. Использование шаблонной функции averageMetric
    double avgLoan = averageMetric(collection);
    std::cout << "[Шаблонная функция averageMetric]: Средний срок выдачи по коллекции = " << avgLoan << " дн.\n";

    // 3. Использование шаблонной функции sortBy (сортировка по году издания)
    auto sortedByYear = sortBy(collection, [](const Publication& a, const Publication& b) {
        return a.getYear() < b.getYear();
    });
    std::cout << "[Шаблонная функция sortBy]: Отсортировано по году издания:\n";
    for (const auto& item : sortedByYear) {
        std::cout << " - " << item->getYear() << " г. | " << item->getTitle() << "\n";
    }

    // 4. Демонстрация метода Collection::findAll с лямбда-предикатом
    auto modernPubs = collection.findAll([](const Publication& p) {
        return p.getYear() >= 2022;
    });
    std::cout << "[Метод Collection::findAll]: Издания 2022 года и новее (всего " << modernPubs.size() << "):\n";
    modernPubs.print(std::cout);
    std::cout << "=================================================================\n";
}

int main() {
    std::setlocale(LC_ALL, "Russian");
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    auto lib = std::make_shared<ScientificLibrary>("Научная Библиотека ВУЗа", 50);

    *lib += std::make_shared<Book>("Квантовая механика", "Ландау Л.Д.", 1989, 450, lib);
    *lib += std::make_shared<Article>("Теория алгоритмов", "Кормен Т.", 2013, "Вестник ИТ", 4, lib);
    *lib += std::make_shared<Monograph>("Нейросети и обработка данных", "Иванов А.А.", 2023, "978-5-4461-1234-5", 1000, lib);
    *lib += std::make_shared<Journal>("Научный Вестник", "Коллектив", 2022, 12, "Наука", lib);
    *lib += std::make_shared<Conference>("Доклад по ИИ", "Петров П.П.", 2024, "ИТ-Форум", "Москва", lib);

    int userChoice = -1;
    while (userChoice != 0) {
        std::cout << "\n=== СИСТЕМА УПРАВЛЕНИЯ НАУЧНОЙ БИБЛИОТЕКОЙ ===\n"
            << "1. Показать весь каталог библиотеки\n"
            << "2. Запросить продление срока выдачи для всех изданий\n"
            << "3. Показать сроки выдачи изданий\n"
            << "4. Найти издание с наибольшим сроком выдачи\n"
            << "5. Выдать издание читателю\n"
            << "6. Вернуть издание в библиотеку\n"
            << "7. Найти публикации по автору\n"
            << "8. Добавить новое издание в фонд\n"
            << "9. Показать унаследованные и уникальные свойства классов\n"
            << "10. Показать полиморфные вызовы (тип, вывод, срок выдачи)\n"
            << "11. Демонстрация шаблонов и алгоритмов (Лаб №5)\n" // Новый пункт меню для проверки лабы
            << "0. Выход из программы\n";

        userChoice = readNumber("Выберите действие: ");

        try {
            switch (userChoice) {
            case 1:
                lib->showCatalog();
                break;
            case 2: {
                int days = readNumber("На сколько дней продлить срок выдачи: ");
                lib->extendAllLoans(days);
                break;
            }
            case 3:
                lib->showLoanPeriods();
                break;
            case 4:
                lib->findLongestLoan();
                break;
            case 9:
                demonstrateUniqueMethods(*lib);
                break;
            case 10:
                demonstratePolymorphism(*lib);
                break;
            case 11:
                demonstrateTemplatesAndAlgorithms(*lib); // Запуск демонстрации шаблонов
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
