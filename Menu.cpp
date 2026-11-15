#include "Menu.h"
#include <iostream>
#include "Demos.h"
#include "Scenarios.h"
#include "exceptions.h"

void printMenu() {
    std::cout << "\n=== СИСТЕМА УПРАВЛЕНИЯ НАУЧНОЙ БИБЛИОТЕКОЙ ===\n"
        << "Просмотр и поиск:\n"
        << "  1. Показать каталог\n"
        << "  2. Показать каталог с сортировкой\n"
        << "  3. Показать издания определённого типа\n"
        << "  4. Показать издание по номеру\n"
        << "  5. Подробная информация об издании\n"
        << "  6. Найти издания по автору\n"
        << "Выдача и возврат:\n"
        << "  7. Выдать издание читателю\n"
        << "  8. Принять издание обратно\n"
        << "  9. Продлить срок для выданных изданий\n"
        << " 10. Показать сроки выдачи\n"
        << " 11. Найти издание с наибольшим сроком выдачи\n"
        << " 12. Статистика фонда\n"
        << "Изменение фонда:\n"
        << " 13. Добавить издание\n"
        << " 14. Списать издание по названию\n"
        << " 15. Списать издание по номеру\n"
        << "Проверка обработки ошибок:\n"
        << " 16. Демонстрация исключительных ситуаций\n"
        << "  0. Выход\n";
}

void executeChoice(int choice, const std::shared_ptr<ScientificLibrary>& lib) {
    switch (choice) {
    case 1: lib->showCatalog(); break;
    case 2: showSortedFromInput(*lib); break;
    case 3: showByTypeFromInput(*lib); break;
    case 4: showByNumberFromInput(*lib); break;
    case 5: detailsFromInput(*lib); break;
    case 6: searchFromInput(*lib); break;
    case 7: issueFromInput(*lib); break;
    case 8: returnFromInput(*lib); break;
    case 9: extendFromInput(*lib); break;
    case 10: lib->showLoanPeriods(); break;
    case 11: lib->findLongestLoan(); break;
    case 12: lib->showStatistics(); break;
    case 13: addFromInput(lib); break;
    case 14: removeFromInput(lib); break;
    case 15: removeByNumberFromInput(lib); break;
    case 16:
        if (!demonstrateExceptions()) throw InputAbortedException("демонстрация остановлена!");
        break;
    case 0: std::cout << "Завершение работы программы.\n"; break;
    default: std::cout << "Такого пункта нет в меню.\n";
    }
}