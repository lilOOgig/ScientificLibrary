#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <map>
#include <functional>
#ifdef _WIN32
#include <windows.h>
#endif

#include "ScientificLibrary.h"
#include "Publication.h"
#include "Book.h"
#include "Article.h"
#include "Monograph.h"
#include "Journal.h"
#include "Conference.h"

// ---------- Ввод ----------

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

// ---------- Подготовка данных и меню ----------

void fillLibrary(const std::shared_ptr<ScientificLibrary>& lib) {
    *lib += std::make_shared<Book>("Квантовая механика", "Ландау Л.Д.", 1989, 450, lib);
    *lib += std::make_shared<Article>("Теория алгоритмов", "Кормен Т.", 2013, "Вестник ИТ", 4, lib);
    *lib += std::make_shared<Monograph>("Нейросети и обработка данных", "Иванов А.А.", 2023, "978-5-4461-1234-5", 1000, lib);
    *lib += std::make_shared<Journal>("Научный Вестник", "Коллектив", 2022, 12, "Наука", lib);
    *lib += std::make_shared<Conference>("Доклад по ИИ", "Петров П.П.", 2024, "ИТ-Форум", "Москва", lib);
}

void printMenu() {
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
        << "0. Выход из программы\n";
}

// ---------- Добавление издания (пункт 8) ----------

std::shared_ptr<Publication> createPublication(int type) {
    switch (type) {
    case 1: return std::make_shared<Book>();
    case 2: return std::make_shared<Article>();
    case 3: return std::make_shared<Monograph>();
    case 4: return std::make_shared<Journal>();
    case 5: return std::make_shared<Conference>();
    default: return nullptr;
    }
}

void addNewPublication(ScientificLibrary& lib) {
    std::cout << "\nВыберите тип добавляемого издания:\n"
        << "1 - Книга\n"
        << "2 - Статья\n"
        << "3 - Монография\n"
        << "4 - Журнал\n"
        << "5 - Конференция\n";
    auto newPub = createPublication(readNumber("Ваш выбор: "));
    if (!newPub) {
        std::cout << "Неверный тип издания!\n";
        return;
    }
    std::cin >> *newPub;
    lib += newPub;
}

// ---------- Пункт 10: полиморфные вызовы через указатель и ссылку ----------

void demonstratePolymorphism(const ScientificLibrary& lib) {
    std::cout << "\n=== Полиморфные вызовы через интерфейс Publication ===\n";
    for (const auto& item : lib.getItems()) {
        const std::shared_ptr<Publication>& ptr = item;   // указатель на базовый класс
        const Publication& ref = *item;                   // ссылка на базовый класс

        std::cout << "Тип (через указатель): " << ptr->getType() << "\n";
        std::cout << "Информация (через ссылку): ";
        ref.printInformation(std::cout);
        std::cout << "\n";
        std::cout << "Срок выдачи: " << ptr->getLoanPeriod() << " дн., максимум продления: "
            << ptr->getAllowedExtension(30) << " дн.\n\n";
    }
}

// ---------- Пункт 9: унаследованные и уникальные свойства ----------

void printInheritedFields(const Publication& pub) {
    std::cout << "Унаследованные: ";
    pub.printTitle(std::cout);  std::cout << " | ";
    pub.printAuthor(std::cout); std::cout << " | ";
    pub.printYear(std::cout);   std::cout << "\n";
}

void describe(const Book& book) {
    book.printPageCount(std::cout);
    std::cout << "\nУникальный метод: при 30 стр. в день читать " << book.getReadingDays(30) << " дн.\n";
}

void describe(const Monograph& mono) {
    mono.printIsbn(std::cout); std::cout << " | "; mono.printCirculation(std::cout);
    std::cout << "\nУникальный метод: ограниченный тираж - " << (mono.isLimitedEdition() ? "да" : "нет") << "\n";
}

void describe(const Article& article) {
    article.printJournalName(std::cout); std::cout << " | "; article.printIssueNumber(std::cout);
    std::cout << "\nУникальный метод: ссылка - " << article.getCitation() << "\n";
}

void describe(const Journal& journal) {
    journal.printVolumeNumber(std::cout); std::cout << " | "; journal.printPublisher(std::cout);
    std::cout << "\nУникальный метод: свежий выпуск - " << (journal.isCurrent() ? "да" : "нет") << "\n";
}

void describe(const Conference& conf) {
    conf.printConferenceName(std::cout); std::cout << " | "; conf.printLocation(std::cout);
    std::cout << "\nУникальный метод: доклад сделан " << conf.getAge() << " г. назад\n";
}

// Если издание имеет тип T, выводит его собственные поля и уникальный метод
template <typename T>
bool describeIf(const std::shared_ptr<Publication>& item) {
    auto concrete = std::dynamic_pointer_cast<T>(item);
    if (!concrete) return false;
    describe(*concrete);
    return true;
}

void demonstrateUniqueMethods(const ScientificLibrary& lib) {
    std::cout << "\n=== Унаследованные и уникальные свойства классов ===\n";
    for (const auto& item : lib.getItems()) {
        std::cout << "--- " << item->getType() << " ---\n";
        printInheritedFields(*item);

        std::cout << "Собственные: ";
        describeIf<Book>(item) || describeIf<Monograph>(item) || describeIf<Article>(item)
            || describeIf<Journal>(item) || describeIf<Conference>(item);
        std::cout << "\n";
    }
}

// ---------- Таблица действий меню ----------

using Action = std::function<void(ScientificLibrary&)>;

const std::map<int, Action>& menuActions() {
    static const std::map<int, Action> actions = {
        { 1, [](ScientificLibrary& lib) { lib.showCatalog(); } },
        { 2, [](ScientificLibrary& lib) { lib.extendAllLoans(readNumber("На сколько дней продлить срок выдачи: ")); } },
        { 3, [](ScientificLibrary& lib) { lib.showLoanPeriods(); } },
        { 4, [](ScientificLibrary& lib) { lib.findLongestLoan(); } },
        { 5, [](ScientificLibrary& lib) { lib.issuePublication("Квантовая механика", "д-р Сидоров"); } },
        { 6, [](ScientificLibrary& lib) { lib.returnPublication("Квантовая механика"); } },
        { 7, [](ScientificLibrary& lib) { lib.searchByAuthor("Кормен Т."); } },
        { 8, addNewPublication },
        { 9, demonstrateUniqueMethods },
        { 10, demonstratePolymorphism },
    };
    return actions;
}

void handleChoice(ScientificLibrary& lib, int choice) {
    const auto& actions = menuActions();
    auto it = actions.find(choice);
    if (it == actions.end()) {
        std::cout << "Ошибка: такого пункта нет в меню. Попробуйте снова.\n";
        return;
    }
    it->second(lib);
}

int main() {
    std::setlocale(LC_ALL, "Russian");
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    auto lib = std::make_shared<ScientificLibrary>("Научная Библиотека ВУЗа", 50);
    fillLibrary(lib);

    int userChoice = -1;
    while (userChoice != 0) {
        printMenu();
        userChoice = readNumber("Выберите действие: ");
        try {
            if (userChoice == 0) {
                std::cout << "Завершение работы программы.\n";
            } else {
                handleChoice(*lib, userChoice);
            }
        }
        catch (const std::exception& e) {
            std::cout << "\n[ОШИБКА]: " << e.what() << "\n";
        }
    }
    return 0;
}
