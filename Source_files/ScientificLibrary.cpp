#include "ScientificLibrary.h"
#include <algorithm>

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
                throw std::runtime_error("Ошибка: Издание уже выдано!");
            }
            item->setBorrowed(true);
            std::cout << "Издание \"" << pubTitle << "\" выдано читателю " << userName << " на " << item->getLoanPeriod() << " дн.\n";
            return true;
        }
    }
    throw std::runtime_error("Ошибка: Издание не найдено!");
}

void ScientificLibrary::returnPublication(std::string_view pubTitle) {
    for (auto& item : items) {
        if (item->getTitle() == pubTitle) {
            if (!item->getIsBorrowed()) {
                throw std::runtime_error("Ошибка: Экземпляр уже на полке!");
            }
            item->setBorrowed(false);
            std::cout << "Экземпляр \"" << pubTitle << "\" возвращен.\n";
            return;
        }
    }
    throw std::runtime_error("Ошибка: Издание не найдено в каталоге!");
}

void ScientificLibrary::showCatalog() const {
    std::cout << "\n--- Каталог: " << name << " (" << items.size() << "/" << maxCapacity << ") ---\n";
    if (items.empty()) {
        std::cout << "Каталог пуст.\n";
        return;
    }
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << i + 1 << ". " << *items[i] << std::endl;
    }
}

// Продление срока выдачи: допустимое число дней зависит от фактического типа издания
void ScientificLibrary::extendAllLoans(int days) const {
    std::cout << "\n=== Продление срока выдачи на " << days << " дн. ===\n";
    for (const auto& item : items) {
        int granted = item->getAllowedExtension(days);
        std::cout << item->getType() << " \"" << item->getTitle() << "\": ";
        if (granted == 0) {
            std::cout << "продление недоступно, срок " << item->getLoanPeriod() << " дн.\n";
        }
        else {
            std::cout << "продлено на " << granted << " дн., новый срок " << item->getLoanPeriod() + granted << " дн.\n";
        }
    }
}

// Срок выдачи каждого издания (полиморфизм)
void ScientificLibrary::showLoanPeriods() const {
    std::cout << "\n=== Сроки выдачи изданий фонда ===\n";
    for (const auto& item : items) {
        std::cout << "--- " << item->getType() << " ---\n"
            << "Название: " << item->getTitle() << "\n"
            << "Срок выдачи (дней): " << item->getLoanPeriod() << "\n";
    }
}

// Издание с наибольшим сроком выдачи (сравнение через operator<)
void ScientificLibrary::findLongestLoan() const {
    if (items.empty()) {
        std::cout << "Каталог пуст.\n";
        return;
    }
    const auto& best = *std::max_element(items.begin(), items.end(), [](const auto& a, const auto& b) {
        return *a < *b;
        });
    std::cout << "\nИздание с наибольшим сроком выдачи:\n"
        << "Тип: " << best->getType() << "\n"
        << "Название: " << best->getTitle() << "\n"
        << "Срок выдачи (дней): " << best->getLoanPeriod() << "\n";
}

void ScientificLibrary::searchByAuthor(std::string_view authorName) const {
    std::cout << "\nПоиск автора \"" << authorName << "\":\n";
    bool found = false;
    for (const auto& item : items) {
        if (item->getAuthor() == authorName) {
            std::cout << *item << std::endl;
            found = true;
        }
    }
    if (!found) std::cout << "Ничего не найдено.\n";
}

ScientificLibrary& ScientificLibrary::operator+=(const std::shared_ptr<Publication>& pub) {
    if (!pub) return *this;
    if (items.size() >= maxCapacity) throw std::runtime_error("Лимит фонда исчерпан!");
    if (std::any_of(items.begin(), items.end(), [&pub](const auto& item) { return *item == *pub; })) {
        throw std::runtime_error("Такое издание уже есть в библиотеке!");
    }
    items.push_back(pub);
    pub->setLibraryRef(weak_from_this());   // библиотека должна быть создана через make_shared
    std::cout << "Добавлено в фонд: " << pub->getTitle() << "\n";
    return *this;
}

ScientificLibrary& ScientificLibrary::operator-=(const std::shared_ptr<Publication>& pub) {
    if (!pub) return *this;
    auto it = std::find_if(items.begin(), items.end(), [&pub](const auto& item) { return *item == *pub; });
    if (it != items.end()) {
        std::cout << "Удалено из фонда: " << (*it)->getTitle() << "\n";
        items.erase(it);
        return *this;
    }
    throw std::runtime_error("Издание для удаления не найдено!");
}
