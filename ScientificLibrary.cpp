#include "Publication.h"
#include "ScientificLibrary.h"

Publication::Publication(std::string_view t, std::string_view a, std::string_view tp, int y, std::weak_ptr<ScientificLibrary> lib)
    : title(t), author(a), type(tp), year(y), isBorrowed(false), libraryRef(lib) {
}

std::string_view Publication::getTitle() const { return title; }
std::string_view Publication::getAuthor() const { return author; }
std::string_view Publication::getType() const { return type; }
int Publication::getYear() const { return year; }
bool Publication::getIsBorrowed() const { return isBorrowed; }

void Publication::setTitle(std::string_view t) { title = t; }
void Publication::setAuthor(std::string_view a) { author = a; }
void Publication::setType(std::string_view tp) { type = tp; }
void Publication::setYear(int y) { year = y; }
void Publication::setBorrowed(bool status) { isBorrowed = status; }

void Publication::printInfo() const {
    std::cout << "[" << type << "] \"" << title << "\" — " << author
        << " (" << year << " г.) | "
        << (isBorrowed ? "Выдана" : "В наличии") << std::endl;
}

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
