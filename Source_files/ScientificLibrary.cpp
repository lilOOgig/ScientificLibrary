#include "ScientificLibrary.h"

ScientificLibrary::ScientificLibrary(std::string_view libName, size_t capacity)
    : name(libName), maxCapacity(capacity) {
}

void ScientificLibrary::addPublication(const std::shared_ptr<Publication>& pub) {
    *this += pub; // [ИЗ ВЕРСИИ 2] Вызов оператора +=
}

bool ScientificLibrary::issuePublication(std::string_view pubTitle, std::string_view userName) {
    for (auto& item : items) {
        if (item->getTitle() == pubTitle) {
            if (item->getIsBorrowed()) {
                // [ИЗ ВЕРСИИ 2] Выброс исключения вместо простого вывода в консоль
                throw std::runtime_error("Ошибка: Издание \"" + std::string(pubTitle) + "\" уже выдано другому читателю!");
            }
            item->setBorrowed(true);
            std::cout << "Издание \"" << pubTitle << "\" успешно выдано читателю " << userName << ".\n";
            return true;
        }
    }
    // [ИЗ ВЕРСИИ 2] Выброс исключения при отсутствии книги
    throw std::runtime_error("Ошибка: Публикация \"" + std::string(pubTitle) + "\" не найдена!");
}

void ScientificLibrary::returnPublication(std::string_view pubTitle) {
    for (auto& item : items) {
        if (item->getTitle() == pubTitle) {
            if (!item->getIsBorrowed()) {
                // [ИЗ ВЕРСИИ 2] Выброс исключения
                throw std::runtime_error("Ошибка: Экземпляр \"" + std::string(pubTitle) + "\" уже на полке!");
            }
            item->setBorrowed(false);
            std::cout << "Экземпляр \"" << pubTitle << "\" успешно возвращён.\n";
            return;
        }
    }
    // [ИЗ ВЕРСИИ 2] Выброс исключения
    throw std::runtime_error("Ошибка: Издание не найдено в каталоге!");
}

void ScientificLibrary::showCatalog() const {
    std::cout << "\n--------------------------------------------------\n";
    std::cout << "Каталог: " << name << " (Заполнено: " << items.size() << "/" << maxCapacity << ")\n";
    std::cout << "--------------------------------------------------\n";
    if (items.empty()) {
        std::cout << "В каталоге пока нет книг.\n";
        return;
    }
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << i + 1 << ". " << *items[i] << std::endl; // [ИЗ ВЕРСИИ 2] Вывод через оператор <<
    }
    std::cout << "--------------------------------------------------\n";
}

void ScientificLibrary::searchByAuthor(std::string_view authorName) const {
    std::cout << "\nПоиск публикаций автора \"" << authorName << "\":\n";
    bool found = false;
    for (const auto& item : items) {
        if (item->getAuthor() == authorName) {
            std::cout << *item << std::endl; // [ИЗ ВЕРСИИ 2] Вывод через оператор <<
            found = true;
        }
    }
    if (!found) {
        std::cout << "Записей не обнаружено.\n";
    }
}

// [ИЗ ВЕРСИИ 2] Перегрузка оператора += с проверкой уникальности и лимита
ScientificLibrary& ScientificLibrary::operator+=(const std::shared_ptr<Publication>& pub) {
    if (!pub) return *this;

    if (items.size() >= maxCapacity) {
        throw std::runtime_error("Ошибка: Лимит фонда библиотеки превышен!");
    }

    // Использование std::any_of для Cppcheck, внутри которого вызывается [ИЗ ВЕРСИИ 2] перегруженный ==
    if (std::any_of(items.begin(), items.end(), [&pub](const auto& item) {
        return *item == *pub; // [ИЗ ВЕРСИИ 2] Использование перегруженного ==
    })) {
        throw std::runtime_error("Ошибка: Книга с таким названием уже есть в базе!");
    }

    items.push_back(pub);
    std::cout << "Добавлено в фонд: " << pub->getTitle() << std::endl;
    return *this;
}

// [ИЗ ВЕРСИИ 2] Перегрузка оператора -= для удаления публикаций
ScientificLibrary& ScientificLibrary::operator-=(const std::shared_ptr<Publication>& pub) {
    if (!pub) return *this;

    for (auto it = items.begin(); it != items.end(); ++it) {
        if (**it == *pub) { // [ИЗ ВЕРСИИ 2] Использование перегруженного ==
            std::cout << "Удалено из фонда: " << (*it)->getTitle() << std::endl;
            items.erase(it);
            return *this;
        }
    }

    throw std::runtime_error("Ошибка (-=): Нельзя удалить книгу, которой нет в коллекции!");
}
