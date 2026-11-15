#include "Scenarios.h"
#include <format>
#include <iostream>
#include "Algs.h"
#include "Article.h"
#include "Book.h"
#include "Conference.h"
#include "Console.h"
#include "Journal.h"
#include "Monograph.h"

namespace {

// Выбирает из фонда издания конкретного типа (selectByType из лаб. №5) и печатает их.
template <typename Derived>
void printByType(const ScientificLibrary& lib, std::string_view label) {
    const auto found = selectByType<Derived>(lib.getItems());
    std::cout << "\n" << label << " в фонде: " << found.size() << "\n";
    for (const auto& item : found) std::cout << " - " << *item << "\n";
}

}  // namespace

void issueFromInput(const ScientificLibrary& lib) {
    section("Выдача издания читателю");
    const std::string title = readText("Название издания: ");
    const std::string reader = readText("Имя читателя: ");
    lib.issuePublication(title, reader);
}

void returnFromInput(const ScientificLibrary& lib) {
    section("Возврат издания в библиотеку");
    lib.returnPublication(readText("Название издания: "));
}

void extendFromInput(const ScientificLibrary& lib) {
    section("Продление срока для выданных изданий");
    lib.extendAllLoans(readInteger("На сколько дней продлить: "));
}

void searchFromInput(const ScientificLibrary& lib) {
    section("Поиск изданий по автору");
    lib.searchByAuthor(readText("Автор: "));
}

// Данные издания вводятся через operator>> (лаб. №4); ошибки ввода бросают исключения из сеттеров.
void addFromInput(const std::shared_ptr<ScientificLibrary>& lib) {
    section("Добавление издания в фонд");
    std::cout << "Тип добавляемого издания:\n"
              << "1 - Книга\n2 - Статья\n3 - Монография\n4 - Журнал\n5 - Конференция\n";
    const int choice = readInteger("Ваш выбор: ");

    std::shared_ptr<Publication> pub;
    switch (choice) {
    case 1: pub = std::make_shared<Book>(); break;
    case 2: pub = std::make_shared<Article>(); break;
    case 3: pub = std::make_shared<Monograph>(); break;
    case 4: pub = std::make_shared<Journal>(); break;
    case 5: pub = std::make_shared<Conference>(); break;
    default: throw InvalidDataException(std::format("неизвестный тип издания: {}!", choice));
    }
    std::cin >> *pub;
    *lib += pub;
}

void removeFromInput(const std::shared_ptr<ScientificLibrary>& lib) {
    section("Списание издания из фонда");
    lib->removePublication(readText("Название издания: "));
}

void showByTypeFromInput(const ScientificLibrary& lib) {
    section("Издания определённого типа");
    std::cout << "1 - Книги\n2 - Статьи\n3 - Монографии\n4 - Журналы\n5 - Конференции\n";
    const int choice = readInteger("Ваш выбор: ");
    switch (choice) {
    case 1: printByType<Book>(lib, "Книги"); break;
    case 2: printByType<Article>(lib, "Статьи"); break;
    case 3: printByType<Monograph>(lib, "Монографии"); break;
    case 4: printByType<Journal>(lib, "Журналы"); break;
    case 5: printByType<Conference>(lib, "Конференции"); break;
    default: throw InvalidDataException(std::format("неизвестный тип издания: {}!", choice));
    }
}

void showSortedFromInput(const ScientificLibrary& lib) {
    section("Каталог с сортировкой");
    std::cout << "1 - по названию\n2 - по году издания\n3 - по сроку выдачи\n";
    const int choice = readInteger("Ваш выбор: ");
    using enum SortKey;
    switch (choice) {
    case 1: lib.showSorted(Title); break;
    case 2: lib.showSorted(Year); break;
    case 3: lib.showSorted(LoanPeriod); break;
    default: throw InvalidDataException(std::format("неизвестный вариант сортировки: {}!", choice));
    }
}

void showByNumberFromInput(const ScientificLibrary& lib) {
    section("Издание по номеру в каталоге");
    const auto pub = lib.getByNumber(readInteger("Номер издания: "));
    std::cout << *pub << "\n";
}

// У каждого типа издания есть свой метод, которого нет у остальных (лаб. №4).
void detailsFromInput(const ScientificLibrary& lib) {
    section("Подробная информация об издании");
    const auto pub = lib.findPublication(readText("Название издания: "));
    std::cout << *pub << "\nСрок выдачи: " << pub->getLoanPeriod() << " дн.\n";

    if (const auto book = std::dynamic_pointer_cast<Book>(pub)) {
        const int pagesPerDay = readInteger("Сколько страниц в день вы читаете: ");
        const int days = book->getReadingDays(pagesPerDay);   // при неверной норме бросит исключение до вывода
        std::cout << "Книгу можно прочитать за " << days << " дн.\n";
    } else if (const auto article = std::dynamic_pointer_cast<Article>(pub)) {
        std::cout << "Библиографическая ссылка: " << article->getCitation() << "\n";
    } else if (const auto mono = std::dynamic_pointer_cast<Monograph>(pub)) {
        std::cout << (mono->isLimitedEdition() ? "Ограниченное издание (тираж меньше 500 экз.)\n" : "Обычное издание\n");
    } else if (const auto journal = std::dynamic_pointer_cast<Journal>(pub)) {
        std::cout << (journal->isCurrent() ? "Свежий выпуск\n" : "Архивный выпуск\n");
    } else if (const auto conf = std::dynamic_pointer_cast<Conference>(pub)) {
        std::cout << "С момента доклада прошло лет: " << conf->getAge() << "\n";
    }
}

void removeByNumberFromInput(const std::shared_ptr<ScientificLibrary>& lib) {
    section("Списание издания по номеру в каталоге");
    lib->removeByNumber(readInteger("Номер издания: "));
}
