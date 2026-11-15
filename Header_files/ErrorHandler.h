#pragma once
#include <exception>
#include "exceptions.h"

// Единая обработка исключений системы (лаб. №6).
// Вызывается из блока catch (const LibraryException&) и получает пойманное исключение
// (std::current_exception()): по его типу выводит своё сообщение.
// Возвращает false, если работу программы продолжать нельзя (закрыт поток ввода).
bool handleException(std::exception_ptr error);

// Выполняет действие; любая ошибка обрабатывается, программа продолжает работу.
template <typename Action>
bool runSafely(Action&& action) {
    try {
        action();
    }
    catch (const LibraryException&) {
        return handleException(std::current_exception());
    }
    return true;
}
