#include "ScientificLibrary.h"

ScientificLibrary::ScientificLibrary(std::string_view libName, size_t capacity)
    : name(libName), maxCapacity(capacity) {
}

void ScientificLibrary::addPublication(const std::shared_ptr<Publication>& pub) {
    *this += pub;
}

bool ScientificLibrary::issuePublication(std::string_view pubTitle, std::string_view userName) {
    for (auto& item : items) {
        if (item->getTitle() == pubTitle) {
            if (item->getIsBorrowed()) {
                throw std::runtime_error("Ошибка: Издание \"" + std::string(pubTitle) + "\" уже выдано другому читателю!");
            }
            item->setBorrowed(true);
            std::cout << "Издание \"" << pubTitle << "\" успешно выдано читателю " << userName << ".\n";
            return true;
        }
    }
    throw std::runtime_error("Ошибка: Публикация \"" + std::string(pubTitle) + "\" не найдена!");
}

void ScientificLibrary::returnPublication(std::string_view pubTitle) {
    for (auto& item : items) {
        if (item->getTitle() == pubTitle) {
            if (!item->getIsBorrowed()) {
                throw std::runtime_error("Ошибка: Экземпляр \"" + std::string(pubTitle) + "\" уже на полке!");
            }
            item->setBorrowed(false);
            std::cout << "Экземпляр \"" << pubTitle << "\" успешно возвращён.\n";
            return;
        }
    }
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
        std::cout << i + 1 << ". " << *items[i] << std::endl;
    }
    std::cout << "--------------------------------------------------\n";
}

void ScientificLibrary::searchByAuthor(std::string_view authorName) const {
    std::cout << "\nПоиск публикаций автора \"" << authorName << "\":\n";
    bool found = false;
    for (const auto& item : items) {
        if (item->getAuthor() == authorName) {
            std::cout << *item << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "Записей не обнаружено.\n";
    }
}

ScientificLibrary& ScientificLibrary::operator+=(const std::shared_ptr<Publication>& pub) {
    if (!pub) return *this;

    if (items.size() >= maxCapacity) {
        throw std::runtime_error("Ошибка: Лимит фонда библиотеки превышен!");
    }

    for (const auto& item : items)
    {
        if (*item == *pub) {
            throw std::runtime_error("Ошибка: Книга с таким названием уже есть в базе!");
        }
    }

    items.push_back(pub);
    std::cout << "Добавлено в фонд: " << pub->getTitle() << std::endl;
    return *this;
}

ScientificLibrary& ScientificLibrary::operator-=(const std::shared_ptr<Publication>& pub) {
    if (!pub) return *this;

    for (auto it = items.begin(); it != items.end(); ++it) {
        if (**it == *pub) {
            std::cout << "Удалено из фонда через: " << (*it)->getTitle() << std::endl;
            items.erase(it);
            return *this;
        }
    }

    throw std::runtime_error("Ошибка (-=): Нельзя удалить книгу, которой нет в коллекции!");
}
