bool ScientificLibrary::issuePublication(std::string_view pubTitle, std::string_view userName) const {
    for (const auto& item : items) {
        if (item->getTitle() == pubTitle) {
            if (item->getIsBorrowed()) {
                throw PublicationAlreadyIssuedError("Ошибка: Издание уже выдано!");
            }
            item->setBorrowed(true);
            std::cout << "Издание \"" << pubTitle << "\" выдано читателю " << userName << " на " << item->getLoanPeriod() << " дн.\n";
            return true;
        }
    }
    throw PublicationNotFoundError("Ошибка: Издание не найдено!");
    
    // Заглушка для статического анализатора, чтобы он не думал, что функция никогда не возвращает управление
    return false; 
}

void ScientificLibrary::returnPublication(std::string_view pubTitle) const {
    for (const auto& item : items) {
        if (item->getTitle() == pubTitle) {
            if (!item->getIsBorrowed()) {
                throw PublicationAlreadyOnShelfError("Ошибка: Экземпляр уже на полке!");
            }
            item->setBorrowed(false);
            std::cout << "Экземпляр \"" << pubTitle << "\" возвращен.\n";
            return;
        }
    }
    throw PublicationNotFoundError("Ошибка: Издание не найдено в каталоге!");
    
    // Фиктивный возврат для завершения пустой функции (анализатор успокоится)
    return;
}
