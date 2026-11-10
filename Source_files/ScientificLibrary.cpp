#include "ScientificLibrary.h"
#include "Algs.h"

ScientificLibrary::ScientificLibrary(std::string_view libName, size_t capacity)
    : name(libName), maxCapacity(capacity) {
}

void ScientificLibrary::addPublication(const std::shared_ptr<Publication>& pub) {
    *this += pub;
}

void ScientificLibrary::issuePublication(std::string_view pubTitle, std::string_view userName) {
    auto item = items.find([&](const Publication& p) { return p.getTitle() == pubTitle; });
    if (!item) throw PublicationNotFoundError("Ошибка: Издание не найдено!");
    if (item->getIsBorrowed()) throw PublicationAlreadyIssuedError("Ошибка: Издание уже выдано!");

    item->setBorrowed(true);
    std::cout << "Издание \"" << pubTitle << "\" выдано читателю " << userName
        << " на " << item->getLoanPeriod() << " дн.\n";
}

void ScientificLibrary::returnPublication(std::string_view pubTitle) {
    auto item = items.find([&](const Publication& p) { return p.getTitle() == pubTitle; });
    if (!item) throw PublicationNotFoundError("Ошибка: Издание не найдено в каталоге!");
    if (!item->getIsBorrowed()) throw PublicationAlreadyOnShelfError("Ошибка: Экземпляр уже на полке!");

    item->setBorrowed(false);
    std::cout << "Экземпляр \"" << pubTitle << "\" возвращен.\n";
}

void ScientificLibrary::showCatalog() const {
    std::cout << "\n--- Каталог: " << name << " (" << items.size() << "/" << maxCapacity << ") ---\n";
    if (items.empty()) {
        std::cout << "Каталог пуст.\n";
        return;
    }
    size_t idx = 1;
    for (const auto& item : items) {
        std::cout << idx++ << ". " << *item << "\n";
    }
}

// Продлить можно только то, что сейчас на руках у читателей.
void ScientificLibrary::extendAllLoans(int days) const {
    if (days <= 0) throw std::invalid_argument("Ошибка: срок продления должен быть положительным!");

    std::cout << "\n=== Продление выданных изданий на " << days << " дн. ===\n";
    auto issued = items.findAll([](const Publication& p) { return p.getIsBorrowed(); });
    if (issued.empty()) {
        std::cout << "Сейчас нет выданных изданий, продлевать нечего.\n";
        return;
    }
    for (const auto& item : issued) {
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

void ScientificLibrary::showLoanPeriods() const {
    std::cout << "\n=== Сроки выдачи изданий фонда ===\n";
    for (const auto& item : items) {
        std::cout << item->getType() << " \"" << item->getTitle() << "\" — "
            << item->getLoanPeriod() << " дн.\n";
    }
}

void ScientificLibrary::findLongestLoan() const {
    auto best = maxByMetric(items, [](const Publication& p) { return p.getLoanPeriod(); });
    if (!best) {
        std::cout << "Каталог пуст.\n";
        return;
    }
    std::cout << "\nИздание с наибольшим сроком выдачи:\n"
        << best->getType() << " \"" << best->getTitle() << "\" — "
        << best->getLoanPeriod() << " дн.\n";
}

void ScientificLibrary::searchByAuthor(std::string_view authorName) const {
    std::cout << "\nПоиск автора \"" << authorName << "\":\n";
    auto found = items.findAll([&](const Publication& p) { return p.getAuthor() == authorName; });
    if (found.empty()) {
        std::cout << "Ничего не найдено.\n";
        return;
    }
    found.print();
}

ScientificLibrary& ScientificLibrary::operator+=(const std::shared_ptr<Publication>& pub) {
    if (!pub) throw std::invalid_argument("Ошибка: нельзя добавить пустое издание!");
    if (items.size() >= maxCapacity) throw LibraryFullError("Лимит фонда исчерпан!");
    if (items.find([&](const Publication& p) { return p == *pub; })) {
        throw DuplicatePublicationError("Такое издание уже есть в библиотеке!");
    }

    items.add(pub);
    pub->setLibraryRef(weak_from_this());
    std::cout << "Добавлено в фонд: " << pub->getTitle() << "\n";
    return *this;
}

ScientificLibrary& ScientificLibrary::operator-=(const std::shared_ptr<Publication>& pub) {
    if (!pub) throw std::invalid_argument("Ошибка: не указано издание для удаления!");

    auto stored = items.find([&](const Publication& p) { return p == *pub; });
    if (!stored) throw PublicationNotFoundError("Издание для удаления не найдено!");
    if (stored->getIsBorrowed()) throw PublicationAlreadyIssuedError("Нельзя списать издание, пока оно на руках у читателя!");

    items.removeIf([&](const Publication& p) { return &p == stored.get(); });
    stored->setLibraryRef({});
    std::cout << "Удалено из фонда: " << stored->getTitle() << "\n";
    return *this;
}
