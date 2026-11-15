#include "ScientificLibrary.h"
#include <format>
#include <map>
#include <vector>
#include "Algs.h"
#include "Monograph.h"

ScientificLibrary::ScientificLibrary(std::string_view libName, size_t capacity)
    : name(libName), maxCapacity(capacity) {
    if (capacity == 0) throw InvalidDataException("вместимость библиотеки должна быть больше нуля!");
}

std::shared_ptr<Publication> ScientificLibrary::requireByTitle(std::string_view pubTitle) const {
    if (pubTitle.empty()) throw InvalidDataException("название издания не указано!");

    auto item = items.find([pubTitle](const Publication& p) { return p.getTitle() == pubTitle; });
    if (!item) throw ObjectNotFoundException("издание \"" + std::string(pubTitle) + "\" отсутствует в каталоге!");

    // Издание, привязанное к другой библиотеке, обслуживать здесь нельзя.
    const auto owner = item->getLibraryRef().lock();
    if (owner && owner.get() != this) {
        throw RelationException("издание \"" + std::string(pubTitle) + "\" привязано к другой библиотеке!");
    }
    return item;
}

void ScientificLibrary::removePublication(std::string_view pubTitle) {
    *this -= requireByTitle(pubTitle);
}

std::shared_ptr<Publication> ScientificLibrary::findPublication(std::string_view pubTitle) const {
    return requireByTitle(pubTitle);
}

// Номер считается так же, как в каталоге: с единицы.
std::shared_ptr<Publication> ScientificLibrary::getByNumber(int number) const {
    if (items.empty()) throw OutOfRangeException("каталог пуст, издания с таким номером нет!");
    if (number < 1 || static_cast<size_t>(number) > items.size()) {
        throw OutOfRangeException(std::format("номер {} вне каталога (допустимо от 1 до {})!", number, items.size()));
    }
    return items.get(static_cast<size_t>(number) - 1);
}

void ScientificLibrary::removeByNumber(int number) {
    *this -= getByNumber(number);
}

void ScientificLibrary::addPublication(const std::shared_ptr<Publication>& pub) {
    *this += pub;
}

void ScientificLibrary::issuePublication(std::string_view pubTitle, std::string_view userName) const {
    if (userName.empty()) throw InvalidDataException("не указано имя читателя!");

    auto item = requireByTitle(pubTitle);
    if (item->getIsBorrowed()) {
        throw InvalidOperationException("издание \"" + std::string(pubTitle) + "\" уже выдано читателю!");
    }

    item->setBorrowed(true);
    std::cout << "Издание \"" << pubTitle << "\" выдано читателю " << userName
        << " на " << item->getLoanPeriod() << " дн.\n";
}

void ScientificLibrary::returnPublication(std::string_view pubTitle) const {
    auto item = requireByTitle(pubTitle);
    if (!item->getIsBorrowed()) {
        throw InvalidOperationException("экземпляр \"" + std::string(pubTitle) + "\" уже на полке, возвращать нечего!");
    }

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
    if (days <= 0) throw InvalidDataException("срок продления должен быть положительным (введено " + std::to_string(days) + ")!");
    if (days > MAX_EXTENSION_DAYS) {
        throw LimitExceededException("продлить можно не более чем на " + std::to_string(MAX_EXTENSION_DAYS) +
            " дн. за раз (запрошено " + std::to_string(days) + ")!");
    }

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

void ScientificLibrary::showSorted(SortKey key) const {
    std::vector<std::shared_ptr<Publication>> sorted;
    std::string label;
    switch (key) {
    case SortKey::Title:
        label = "по названию";
        sorted = sortBy(items, [](const Publication& a, const Publication& b) { return a.getTitle() < b.getTitle(); });
        break;
    case SortKey::Year:
        label = "по году издания";
        sorted = sortBy(items, [](const Publication& a, const Publication& b) { return a.getYear() < b.getYear(); });
        break;
    case SortKey::LoanPeriod:
        label = "по сроку выдачи";
        sorted = sortBy(items, [](const Publication& a, const Publication& b) { return a < b; });
        break;
    }

    std::cout << "\n--- Каталог " << label << " ---\n";
    if (sorted.empty()) {
        std::cout << "Каталог пуст.\n";
        return;
    }
    size_t idx = 1;
    for (const auto& item : sorted) std::cout << idx++ << ". " << *item << "\n";
}

void ScientificLibrary::showStatistics() const {
    std::cout << "\n--- Статистика фонда: " << name << " ---\n";
    const size_t issued = items.findAll([](const Publication& p) { return p.getIsBorrowed(); }).size();
    std::cout << "Изданий в фонде: " << items.size() << " из " << maxCapacity << "\n"
        << "Выдано читателям: " << issued << ", на полке: " << items.size() - issued << "\n";
    if (items.empty()) return;

    std::cout << std::format("Средний срок выдачи: {:.1f} дн.\n",
        averageMetric(items, [](const Publication& p) { return p.getLoanPeriod(); }));
    std::cout << std::format("Средний год издания: {:.1f}\n",
        averageMetric(items, [](const Publication& p) { return p.getYear(); }));

    std::map<std::string, int> byType;
    for (const auto& item : items) ++byType[std::string(item->getType())];
    std::cout << "По типам:\n";
    for (const auto& [type, count] : byType) std::cout << "  " << type << ": " << count << "\n";
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
    if (authorName.empty()) throw InvalidDataException("не указан автор для поиска!");
    std::cout << "\nПоиск автора \"" << authorName << "\":\n";
    auto found = items.findAll([authorName](const Publication& p) { return p.getAuthor() == authorName; });
    if (found.empty()) {
        std::cout << "Ничего не найдено.\n";
        return;
    }
    found.print();
}

ScientificLibrary& ScientificLibrary::operator+=(const std::shared_ptr<Publication>& pub) {
    if (!pub) throw InvalidDataException("нельзя добавить пустое издание!");

    // Издание уже привязано к другой библиотеке - добавлять его сюда нельзя.
    const auto owner = pub->getLibraryRef().lock();
    if (owner && owner.get() != this) {
        throw RelationException("издание \"" + std::string(pub->getTitle()) + "\" уже числится в другой библиотеке!");
    }

    if (items.find([&pub](const Publication& p) { return p == *pub; })) {
        throw DuplicateException("издание \"" + std::string(pub->getTitle()) + "\" уже есть в библиотеке!");
    }
    // ISBN - уникальный идентификатор монографии
    if (const auto* mono = dynamic_cast<const Monograph*>(pub.get())) {
        const bool isbnTaken = items.find([mono](const Publication& p) {
            const auto* other = dynamic_cast<const Monograph*>(&p);
            return other && other->getIsbn() == mono->getIsbn();
            }) != nullptr;
        if (isbnTaken) throw DuplicateException("монография с ISBN " + std::string(mono->getIsbn()) + " уже есть в фонде!");
    }

    if (items.size() >= maxCapacity) {
        throw LimitExceededException("лимит фонда исчерпан (" + std::to_string(maxCapacity) + " изд.)!");
    }

    items.add(pub);
    pub->setLibraryRef(weak_from_this());
    std::cout << "Добавлено в фонд: " << pub->getTitle() << "\n";
    return *this;
}

ScientificLibrary& ScientificLibrary::operator-=(const std::shared_ptr<Publication>& pub) {
    if (!pub) throw InvalidDataException("не указано издание для удаления!");

    auto stored = items.find([&pub](const Publication& p) { return p == *pub; });
    if (!stored) throw ObjectNotFoundException("издание для удаления отсутствует в фонде!");
    if (stored->getIsBorrowed()) {
        throw RelationException("нельзя списать издание \"" + std::string(stored->getTitle()) +
            "\", пока оно на руках у читателя!");
    }

    items.removeIf([&stored](const Publication& p) { return &p == stored.get(); });
    stored->setLibraryRef({});
    std::cout << "Удалено из фонда: " << stored->getTitle() << "\n";
    return *this;
}
