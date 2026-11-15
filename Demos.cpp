#include "Demos.h"
#include <iostream>
#include <memory>
#include <vector>
#include "Book.h"
#include "Console.h"
#include "ErrorHandler.h"
#include "ScientificLibrary.h"
#include "exceptions.h"

// ---------- лаб. №6: обработка исключений ----------

namespace {

    std::shared_ptr<ScientificLibrary> makeDemoLibrary(size_t capacity) {
        auto lib = std::make_shared<ScientificLibrary>("Демо-библиотека", capacity);
        *lib += std::make_shared<Book>("Тестовая книга", "Автор А.А.", 2020, 300);
        return lib;
    }

    void demoInvalidData() {
        step("InvalidDataException: книга с отрицательным числом страниц");
        Book book("Некорректная книга", "Автор А.А.", 2020, -5);
    }

    void demoLimitExceeded() {
        step("LimitExceededException: добавление в библиотеку, рассчитанную на 1 издание");
        auto lib = makeDemoLibrary(1);
        *lib += std::make_shared<Book>("Вторая книга", "Автор Б.Б.", 2021, 200);
    }

    void demoDuplicate() {
        step("DuplicateException: повторное добавление такого же издания");
        auto lib = makeDemoLibrary(5);
        *lib += std::make_shared<Book>("Тестовая книга", "Автор А.А.", 2020, 300);
    }

    void demoNotFound() {
        step("ObjectNotFoundException: выдача несуществующего издания");
        makeDemoLibrary(5)->issuePublication("Несуществующая книга", "Иванов И.И.");
    }

    void demoOutOfRange() {
        step("OutOfRangeException: обращение к изданию под номером 10 в каталоге из одного издания");
        makeDemoLibrary(5)->getByNumber(10);
    }

    void demoInvalidOperation() {
        step("InvalidOperationException: повторная выдача уже выданного издания");
        auto lib = makeDemoLibrary(5);
        lib->issuePublication("Тестовая книга", "Иванов И.И.");
        lib->issuePublication("Тестовая книга", "Петров П.П.");
    }

    void demoRelation() {
        step("RelationException: списание издания, которое находится на руках у читателя");
        auto lib = makeDemoLibrary(5);
        lib->issuePublication("Тестовая книга", "Иванов И.И.");
        lib->removePublication("Тестовая книга");
    }

}  // namespace

bool demonstrateExceptions() {
    section("Лаб №6: демонстрация исключительных ситуаций");
    const std::vector<void (*)()> demos = {
        demoInvalidData, demoLimitExceeded, demoDuplicate, demoNotFound,
        demoOutOfRange, demoInvalidOperation, demoRelation
    };
    for (auto demo : demos) {
        if (!runSafely(demo)) return false;
    }
    std::cout << "\nВсе ситуации обработаны, программа продолжает работу.\n";
    return true;
}