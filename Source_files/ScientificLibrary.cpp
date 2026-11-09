#include "ScientificLibrary.h"
#include <algorithm>
#include <ranges>

ScientificLibrary::ScientificLibrary(std::string_view libName, size_t capacity)
    : name(libName), maxCapacity(capacity) {
}

void ScientificLibrary::addPublication(const std::shared_ptr<Publication>& pub) {
    *this += pub;
}

bool ScientificLibrary::issuePublication(std::string_view pubTitle, std::string_view userName) const {
    for (const auto& item : items) {
        if (item->getTitle() == pubTitle) {
            if (item->getIsBorrowed()) {
                throw PublicationAlreadyIssuedError("Ошибка: Издание уже выдано!");
            }
            item->setBorrowed(true);
            std::cout << "Издание \"" << pubTitle << "\" выдано читателю " << userName << " на " << item->getLoanPeriod() << " дн.\n";
            return true; // Штатный возврат true
        }
    }
    throw PublicationNotFoundError("Ошибка: Издание не найдено!");
}

void ScientificLibrary::returnPublication(std::string_view pubTitle) const {
    for (const auto& item : items) {
        if (item->getTitle() == pubTitle) {
            if (!item->getIsBorrowed()) {
                throw PublicationAlreadyOnShelfError("Ошибка: Экземпляр уже на полке!");
            }
            item->setBorrowed(false);
            std::cout << "Экземпляр \"" << pubTitle << "\" возвращен.\n";
            return; // Штатный возврат void
        }
    }
    throw PublicationNotFoundError("Ошибка: Издание не найдено в каталоге!");
}

void ScientificLibrary::showCatalog() const {
    std::cout << "\n--- Каталог: " << name << " (" << items.size() << "/" << maxCapacity << ") ---\n";
    if (items.empty()) {
        std::cout << "Каталог пуст.\n";
        return;
    }
    size_t idx = 1;
    for (const auto& item : items) {
        std::cout << idx++ << ". " << *item << std::endl;
    }
}

void ScientificLibrary::extendAllLoans(int days) const {
    std::cout << "\n=== Продление срока выдачи на " << days << " дн. ===\n";
    for (const auto& item : items) {
        int granted = item->getAllowedExtension(days);
        std::cout << item->getType() << " \"" << item->getTitle() << "\": ";
        if (granted == 0) {
            std::cout << "продление недоступно, срок " << item->getLoanPeriod() << " дн.\n";
        } else {
            std::cout << "продлено на " << granted << " дн., новый срок " << item->getLoanPeriod() + granted << " дн.\n";
        }
    }
}

void ScientificLibrary::showLoanPeriods() const {
    std::cout << "\n=== Сроки выдачи изданий фонда ===\n";
    for (const auto& item : items) {
        std::cout << "--- " << item->getType() << " ---\n"
            << "Название: " << item->getTitle() << "\n"
            << "Срок выдачи (дней): " << item->getLoanPeriod() << "\n";
    }
}

void ScientificLibrary::findLongestLoan() const {
    if (items.empty()) {
        std::cout << "Каталог пуст.\n";
        return;
    }
    const auto& best = *std::ranges::max_element(items, [](const auto& a, const auto& b) {
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
    if (items.size() >= maxCapacity) throw LibraryFullError("Лимит фонда исчерпан!");
    
    if (std::ranges::any_of(items, [&pub](const auto& item) { return *item == *pub; })) {
        throw DuplicatePublicationError("Такое издание уже есть в библиотеке!");
    }
    
    items.add(pub);
    pub->setLibraryRef(weak_from_this());   
    std::cout << "Добавлено в фонд: " << pub->getTitle() << "\n";
    return *this;
}

ScientificLibrary& ScientificLibrary::operator-=(const std::shared_ptr<Publication>& pub) {
    if (!pub) return *this;
    if (size_t removedCount = items.removeIf([&pub](const Publication& item) { return item == *pub; }); removedCount > 0) {
        std::cout << "Удалено из фонда: " << pub->getTitle() << "\n";
        return *this;
    }
    throw PublicationNotFoundError("Издание для удаления не найдено!");
}
