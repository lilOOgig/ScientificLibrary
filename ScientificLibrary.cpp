#include "ScientificLibrary.h"

ScientificLibrary::ScientificLibrary(std::string_view libName, size_t capacity)
    : name(libName), maxCapacity(capacity) {
}

void ScientificLibrary::addPublication(const std::shared_ptr<Publication>& pub) {
    if (items.size() >= maxCapacity) {
        std::cout << "Лимит фонда библиотеки превышен!\n";
        return;
    }
    items.push_back(pub);
    std::cout << "В каталог добавлено: " << pub->getTitle() << std::endl;
}

bool ScientificLibrary::issuePublication(std::string_view pubTitle, std::string_view userName) {
    for (auto& item : items) {
        if (item->getTitle() == pubTitle) {
            if (item->getIsBorrowed()) {
                std::cout << "Ошибочка: Издание \"" << pubTitle << "\" уже на руках у другого читателя!\n";
                return false;
            }
            item->setBorrowed(true);
            std::cout << "Издание \"" << pubTitle << "\" выдано читателю " << userName << ".\n";
            return true;
        }
    }
    std::cout << "Книга с таким названием не найдена.\n";
    return false;
}

void ScientificLibrary::returnPublication(std::string_view pubTitle) {
    for (auto& item : items) {
        if (item->getTitle() == pubTitle) {
            if (!item->getIsBorrowed()) {
                std::cout << "Экземпляр \"" << pubTitle << "\" уже находится на полке.\n";
                return;
            }
            item->setBorrowed(false);
            std::cout << "Экземпляр \"" << pubTitle << "\" успешно возвращен в фонд.\n";
            return;
        }
    }
    std::cout << "Издание не найдено.\n";
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
        std::cout << i + 1 << ". ";
        items[i]->printInfo();
    }
    std::cout << "--------------------------------------------------\n";
}

void ScientificLibrary::searchByAuthor(std::string_view authorName) const {
    std::cout << "\nПоиск публикаций автора \"" << authorName << "\":\n";
    bool found = false;
    for (const auto& item : items) {
        if (item->getAuthor() == authorName) {
            item->printInfo();
            found = true;
        }
    }
    if (!found) {
        std::cout << "Записей не обнаружено.\n";
    }
}
