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
#include "algs.h"

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

// 1. Демонстрация базовых операций контейнера (Условие лабы: add, get, removeAt, size, clear, print)
void demonstrateCollectionBasics() {
    std::cout << "\n=== [Лаб №5] 1. Базовые операции шаблонного класса Collection<T> ===\n";
    Collection<Publication> testCol;

    std::cout << "Создана пустая коллекция. Размер: " << testCol.size() << "\n";
    std::cout << "Содержимое пустой коллекции:\n";
    testCol.print();

    std::cout << "\nДобавление 2 элементов в коллекцию (add)...\n";
    testCol.add(std::make_shared<Book>("Чистый код", "Роберт Мартин", 2008, 464));
    testCol.add(std::make_shared<Article>("Параллельные вычисления", "Алексеев В.", 2021, "Вестник Программирования", 2));

    std::cout << "Размер коллекции после добавления: " << testCol.size() << "\n";
    std::cout << "Текущее содержимое коллекции (print):\n";
    testCol.print();

    std::cout << "\nПолучение объекта по индексу [0] (get):\n";
    if (auto item = testCol.get(0); item) {
        std::cout << "Найден объект: " << *item << "\n";
    }

    std::cout << "\nУдаление объекта по индексу [0] (removeAt)...\n";
    testCol.removeAt(0);
    std::cout << "Размер коллекции после удаления: " << testCol.size() << "\n";
    testCol.print();

    std::cout << "\nОчистка коллекции (clear)...\n";
    testCol.clear();
    std::cout << "Размер после clear(): " << testCol.size() << "\n";
    std::cout << "=================================================================\n";
}

// 2. Демонстрация шаблонного поиска и удаления по предикату (Условие лабы: find, findAll, removeIf)
void demonstrateCollectionPredicates(const ScientificLibrary& lib) {
    std::cout << "\n=== [Лаб №5] 2. Шаблонный поиск и фильтрация по критериям ===\n";
    const auto& collection = lib.getItems();

    std::cout << "1. Поиск первого издания автора 'Кормен Т.' (find):\n";
    if (auto item = collection.find([](const Publication& p) { return p.getAuthor() == "Кормен Т."; }); item) {
        std::cout << "   Найдено: " << *item << "\n";
    } else {
        std::cout << "   Не найдено.\n";
    }

    std::cout << "\n2. Получение подколлекции изданий от 2022 года и новее (findAll):\n";
    auto modernPubs = collection.findAll([](const Publication& p) { return p.getYear() >= 2022; });
    modernPubs.print();

    std::cout << "\n3. Демонстрация группового удаления по критерию (removeIf):\n";
    Collection<Publication> tempCol = collection; // Создаем копию для теста удаления
    std::cout << "   Исходный размер временной коллекции: " << tempCol.size() << "\n";
    size_t removed = tempCol.removeIf([](const Publication& p) { return p.getYear() < 2015; });
    std::cout << "   Удалено изданий старше 2015 года: " << removed << "\n";
    std::cout << "   Новый размер коллекции: " << tempCol.size() << "\n";
    std::cout << "=================================================================\n";
}

// 3. Демонстрация шаблонных функций обработки (Условие лабы: не менее 1 шаблонной функции)
void demonstrateTemplateFunctions(const ScientificLibrary& lib) {
    std::cout << "\n=== [Лаб №5] 3. Шаблонные функции обработки данных (algs.h) ===\n";
    const auto& collection = lib.getItems();

    // 1. maxByMetric
    if (auto maxPub = maxByMetric(collection); maxPub) {
        std::cout << "1. [maxByMetric]: Издание с максимальным сроком выдачи -> " 
                  << maxPub->getType() << " \"" << maxPub->getTitle() << "\" (" << maxPub->getLoanPeriod() << " дн.)\n";
    }

    // 2. averageMetric
    double avgLoan = averageMetric(collection);
    std::cout << "2. [averageMetric]: Среднее значение срока выдачи = " << avgLoan << " дн.\n";

    // 3. sortBy (ranges::sort)
    auto sortedByYear = sortBy(collection, [](const Publication& a, const Publication& b) {
        return a.getYear() < b.getYear();
    });
    std::cout << "3. [sortBy]: Отсортировано по году издания:\n";
    for (const auto& item : sortedByYear) {
        std::cout << "   - " << item->getYear() << " г. | " << item->getTitle() << "\n";
    }
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
            << "--- Проверка Лабораторной работы №5 (Шаблоны) ---\n"
            << "11. Лаб №5: Базовые операции контейнера Collection<T> (add, get, remove, clear)\n"
            << "12. Лаб №5: Шаблонный поиск и фильтрация (find, findAll, removeIf)\n"
            << "13. Лаб №5: Шаблонные функции обработки данных (maxByMetric, averageMetric, sortBy)\n"
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
                demonstrateCollectionBasics();
                break;
            case 12:
                demonstrateCollectionPredicates(*lib);
                break;
            case 13:
                demonstrateTemplateFunctions(*lib);
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
