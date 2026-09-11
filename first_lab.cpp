#include "ScientificLibrary.h"

int main() {
    // Установка русской локали для корректного вывода в консоль
    setlocale(LC_ALL, "Russian");

    // Создание библиотеки
    ScientificLibrary lib("Центральная Научная Библиотека");

    // Создание объектов публикаций
    Publication pub1("Квантовая механика", "Ландау Л.Д.", "Книга", 1989);
    Publication pub2("Теория алгоритмов", "Кормен Т.", "Книга", 2013);
    Publication pub3("Оптимизация нейросетей", "Иванов А.А.", "Статья", 2023);
    Publication pub4("Исследование систем", "Петров Б.В.", "Диссертация", 2021);

    // Добавление в каталог
    lib.addPublication(pub1);
    lib.addPublication(pub2);
    lib.addPublication(pub3);
    lib.addPublication(pub4);

    // Вывод каталога
    lib.printCatalog();

    // Выдача книг (проверка ограничения)
    std::cout << "--- Проверка выдачи книг ---" << std::endl;
    lib.issuePublication("Квантовая механика", "д-р Сидоров");

    // Попытка выдать ту же книгу повторно
    lib.issuePublication("Квантовая механика", "проф. Кузнецов");

    // Вывод состояния каталога
    lib.printCatalog();

    // Поиск
    lib.searchByAuthor("Кормен Т.");

    // Возврат и повторная выдача
    std::cout << "\n--- Проверка возврата ---" << std::endl;
    lib.returnPublication("Квантовая механика");
    lib.issuePublication("Квантовая механика", "проф. Кузнецов");

    return 0;
}