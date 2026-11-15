#include <clocale>
#include <memory>
#ifdef _WIN32
#include <Windows.h>
#endif

#include "Article.h"
#include "Book.h"
#include "Conference.h"
#include "Console.h"
#include "ErrorHandler.h"
#include "exceptions.h"
#include "Journal.h"
#include "Menu.h"
#include "Monograph.h"
#include "ScientificLibrary.h"

int main() {
    std::setlocale(LC_ALL, "Russian");
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    auto lib = std::make_shared<ScientificLibrary>("Научная Библиотека ВУЗа", 50);

    try {
        *lib += std::make_shared<Book>("Квантовая механика", "Ландау Л.Д.", 1989, 450, lib);
        *lib += std::make_shared<Article>("Теория алгоритмов", "Кормен Т.", 2013, "Вестник ИТ", 4, lib);
        *lib += std::make_shared<Monograph>("Нейросети и обработка данных", "Иванов А.А.", 2023, "978-5-4461-1234-5", 1000, lib);
        *lib += std::make_shared<Journal>("Научный Вестник", "Коллектив", 2022, 12, "Наука", lib);
        *lib += std::make_shared<Conference>("Доклад по ИИ", "Петров П.П.", 2024, "ИТ-Форум", "Москва", lib);
    }
    catch (const LibraryException&) {
        handleException(std::current_exception());   // начальный фонд мог не заполниться полностью, но меню всё равно работает
    }

    int choice = -1;
    while (choice != 0) {
        printMenu();
        choice = readNumber("Выберите действие: ");

        try {
            executeChoice(choice, lib);
        }
        catch (const LibraryException&) {
            if (!handleException(std::current_exception())) choice = 0;   // ввод закрыт - выходим штатно
        }
    }
    return 0;
}
