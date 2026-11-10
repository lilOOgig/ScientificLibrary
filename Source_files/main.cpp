#include <clocale>
#include <format>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#ifdef _WIN32
#include <Windows.h>
#endif

#include "Algs.h"
#include "Article.h"
#include "Book.h"
#include "Collection.h"
#include "Conference.h"
#include "Journal.h"
#include "Monograph.h"
#include "Publication.h"
#include "ScientificLibrary.h"

// ---------- ввод ----------

int readNumber(std::string_view prompt) {
    std::string line;
    int val;
    char tail;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, line)) return 0;   // конец ввода: выходим из программы
        if (std::stringstream ss(line); ss >> val && !(ss >> tail)) return val;
        std::cout << "Неверный ввод! Введите целое число.\n";
    }
}

// ---------- оформление вывода ----------

void section(std::string_view title) {
    std::cout << "\n==================================================\n"
        << title << "\n"
        << "==================================================\n";
}

void step(std::string_view text) {
    std::cout << "\n>> " << text << "\n";
}

// ---------- лаб. №4: наследование и полиморфизм ----------

void demonstrateUniqueMethods(const ScientificLibrary& lib) {
    section("Унаследованные и уникальные свойства классов");
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

void demonstratePolymorphism(const ScientificLibrary& lib) {
    section("Полиморфные вызовы через интерфейс Publication");
    for (const auto& item : lib.getItems()) {
        const Publication& ref = *item;
        std::cout << "Тип (через указатель): " << item->getType() << "\n";
        std::cout << "Информация (через ссылку): ";
        ref.printInformation(std::cout);
        std::cout << "\n";
        std::cout << "Срок выдачи: " << item->getLoanPeriod() << " дн., максимум продления при запросе 30 дн.: "
            << item->getAllowedExtension(30) << " дн.\n\n";
    }
}

// ---------- лаб. №5: шаблоны ----------

// Полка изданий одного типа: собирается из фонда, пополняется новым поступлением.
// Одна и та же функция работает для Book, Article, Journal и любого другого наследника Publication.
template <typename T>
void demonstrateShelf(std::string_view label, const Collection<Publication>& fund, const std::shared_ptr<T>& arrival) {
    std::cout << "\n--- Collection<" << label << "> ---\n";
    auto shelf = selectByType<T>(fund);

    shelf.add(arrival);
    std::cout << "Полка после поступления нового издания:\n";
    shelf.print();

    std::cout << "get(1): " << *shelf.get(1) << "\n";
    if (auto available = shelf.find([](const T& p) { return !p.getIsBorrowed(); })) {
        std::cout << "find (первое свободное для выдачи): " << available->getTitle() << "\n";
    }

    shelf.removeAt(0);
    std::cout << "removeAt(0) (списание с полки), на полке: " << shelf.size() << "\n";
    shelf.clear();
    std::cout << "clear(), на полке: " << shelf.size() << "\n";
}

void demonstrateCollectionTemplates(const ScientificLibrary& lib) {
    section("Лаб №5: шаблонный контейнер Collection<T> в библиотеке");
    const auto& fund = lib.getItems();

    std::cout << "\nФонд целиком, Collection<Publication>: " << fund.size() << " изд.\n";
    fund.print();

    demonstrateShelf<Book>("Book", fund, std::make_shared<Book>("Структуры данных", "Седжвик Р.", 2011, 800));
    demonstrateShelf<Article>("Article", fund, std::make_shared<Article>("Графовые алгоритмы", "Левин М.", 2025, "Вестник ИТ", 1));
    demonstrateShelf<Journal>("Journal", fund, std::make_shared<Journal>("Вестник МГУ", "Коллектив", 2026, 5, "МГУ"));
}

void demonstrateTemplateFunctions(const ScientificLibrary& lib) {
    section("Лаб №5: шаблонные функции (Algs.h)");
    const auto& fund = lib.getItems();
    auto loanPeriod = [](const Publication& p) { return p.getLoanPeriod(); };

    if (auto best = maxByMetric(fund, loanPeriod)) {
        std::cout << "maxByMetric (наибольший срок выдачи): " << best->getType() << " \""
            << best->getTitle() << "\" — " << best->getLoanPeriod() << " дн.\n";
    }
    std::cout << std::format("averageMetric (средний срок выдачи, весь фонд): {:.1f} дн.\n", averageMetric(fund, loanPeriod));
    std::cout << std::format("averageMetric (средний срок выдачи, только книги): {:.1f} дн.\n",
        averageMetric(selectByType<Book>(fund), [](const Book& b) { return b.getLoanPeriod(); }));
    std::cout << "selectByType: монографий в фонде — " << selectByType<Monograph>(fund).size() << "\n";

    std::cout << "sortBy (фонд по году издания):\n";
    for (const auto& p : sortBy(fund, [](const Publication& a, const Publication& b) { return a.getYear() < b.getYear(); })) {
        std::cout << "   " << p->getYear() << " | " << p->getType() << " | " << p->getTitle() << "\n";
    }
}

// ---------- сценарии для пунктов меню (без ввода с клавиатуры) ----------

void issueIfNeeded(ScientificLibrary& lib, std::string_view title, std::string_view reader) {
    auto pub = lib.getItems().find([&](const Publication& p) { return p.getTitle() == title; });
    if (pub && !pub->getIsBorrowed()) lib.issuePublication(title, reader);
}

void scenarioIssue(ScientificLibrary& lib) {
    section("Выдача издания читателю");
    lib.issuePublication("Квантовая механика", "д-р Сидоров");
    std::cout << "(повторное нажатие покажет ошибку: издание уже выдано)\n";
}

void scenarioReturn(ScientificLibrary& lib) {
    section("Возврат издания в библиотеку");
    lib.returnPublication("Квантовая механика");
    std::cout << "(повторное нажатие покажет ошибку: экземпляр уже на полке)\n";
}

void scenarioExtend(ScientificLibrary& lib) {
    section("Продление срока для выданных изданий");
    std::cout << "Сначала выдаём несколько изданий разных типов:\n";
    issueIfNeeded(lib, "Квантовая механика", "д-р Сидоров");
    issueIfNeeded(lib, "Нейросети и обработка данных", "проф. Волков");
    issueIfNeeded(lib, "Научный Вестник", "асп. Ермакова");
    lib.extendAllLoans(10);
}

void scenarioSearch(const ScientificLibrary& lib) {
    section("Поиск изданий по автору");
    lib.searchByAuthor("Кормен Т.");
    lib.searchByAuthor("Неизвестный А.А.");
}

void scenarioAdd(const std::shared_ptr<ScientificLibrary>& lib) {
    section("Добавление издания в фонд");
    static const std::vector<std::shared_ptr<Publication>> samples = {
        std::make_shared<Book>("Структуры данных", "Седжвик Р.", 2011, 800),
        std::make_shared<Article>("Графовые алгоритмы", "Левин М.", 2025, "Вестник ИТ", 1),
        std::make_shared<Monograph>("Машинное обучение", "Смирнов К.К.", 2020, "978-5-9775-0001-1", 300),
        std::make_shared<Journal>("Вестник МГУ", "Коллектив", 2026, 5, "МГУ"),
        std::make_shared<Conference>("Доклад по ПО", "Орлова Н.Н.", 2015, "SoftConf", "Казань")
    };
    static size_t next = 0;

    if (next < samples.size()) {
        *lib += samples[next++];
    }
    else {
        std::cout << "Все заготовленные издания уже добавлены. Пробуем добавить первое ещё раз:\n";
        *lib += samples[0];   // сработает защита от дубликатов
    }
}

void scenarioRemove(const std::shared_ptr<ScientificLibrary>& lib) {
    section("Списание издания из фонда");
    auto found = lib->getItems().find([](const Publication& p) { return p.getTitle() == "Доклад по ИИ"; });
    if (!found) throw PublicationNotFoundError("Издание «Доклад по ИИ» уже списано!");
    *lib -= found;
}

// Единственное место, где данные вводятся с клавиатуры (operator>> из лабы №4)
void addPublicationInteractively(const std::shared_ptr<ScientificLibrary>& lib) {
    std::cout << "\nТип добавляемого издания:\n"
        << "1 - Книга\n2 - Статья\n3 - Монография\n4 - Журнал\n5 - Конференция\n";
    int choice = readNumber("Ваш выбор: ");

    std::shared_ptr<Publication> pub;
    switch (choice) {
    case 1: pub = std::make_shared<Book>(); break;
    case 2: pub = std::make_shared<Article>(); break;
    case 3: pub = std::make_shared<Monograph>(); break;
    case 4: pub = std::make_shared<Journal>(); break;
    case 5: pub = std::make_shared<Conference>(); break;
    default:
        std::cout << "Неверный тип издания!\n";
        return;
    }
    std::cin >> *pub;
    *lib += pub;
}

void printMenu() {
    std::cout << "\n=== СИСТЕМА УПРАВЛЕНИЯ НАУЧНОЙ БИБЛИОТЕКОЙ ===\n"
        << "Работа с фондом:\n"
        << "  1. Показать каталог\n"
        << "  2. Выдать издание читателю\n"
        << "  3. Принять издание обратно\n"
        << "  4. Продлить срок для выданных изданий\n"
        << "  5. Показать сроки выдачи\n"
        << "  6. Найти издание с наибольшим сроком выдачи\n"
        << "  7. Найти издания по автору\n"
        << "  8. Добавить издание в фонд\n"
        << "  9. Списать издание из фонда\n"
        << "Лабораторная №4 (наследование):\n"
        << " 10. Унаследованные и уникальные свойства классов\n"
        << " 11. Полиморфные вызовы\n"
        << "Лабораторная №5 (шаблоны):\n"
        << " 12. Collection<T>: фонд и полки по типам изданий\n"
        << " 13. Шаблонные функции: maxByMetric, averageMetric, sortBy\n"
        << "Дополнительно:\n"
        << "  0. Выход\n";
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

    int choice = -1;
    while (choice != 0) {
        printMenu();
        choice = readNumber("Выберите действие: ");

        try {
            switch (choice) {
            case 1: lib->showCatalog(); break;
            case 2: scenarioIssue(*lib); break;
            case 3: scenarioReturn(*lib); break;
            case 4: scenarioExtend(*lib); break;
            case 5: lib->showLoanPeriods(); break;
            case 6: lib->findLongestLoan(); break;
            case 7: scenarioSearch(*lib); break;
            case 8: scenarioAdd(lib); break;
            case 9: scenarioRemove(lib); break;
            case 10: demonstrateUniqueMethods(*lib); break;
            case 11: demonstratePolymorphism(*lib); break;
            case 12: demonstrateCollectionTemplates(*lib); break;
            case 13: demonstrateTemplateFunctions(*lib); break;
            case 14: addPublicationInteractively(lib); break;
            case 0: std::cout << "Завершение работы программы.\n"; break;
            default: std::cout << "Такого пункта нет в меню.\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "\n[ОШИБКА]: " << e.what() << "\n";
        }
    }
    return 0;
}
