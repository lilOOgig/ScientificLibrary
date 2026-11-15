#pragma once
#include <stdexcept>
#include <string>

// Базовый класс всех исключений системы. Позволяет одним catch перехватить любую "библиотечную" ошибку,
// а отдельными catch - обработать каждый вид ошибки по-своему.
class LibraryException : public std::runtime_error {
public:
    explicit LibraryException(const std::string& message) : std::runtime_error(message) {}
};

// Некорректные данные: пустые строки, неверный год, неположительные числа, нулевые указатели, не-число при вводе.
class InvalidDataException : public LibraryException {
public:
    explicit InvalidDataException(const std::string& message)
        : LibraryException("Некорректные данные: " + message) {
    }
};

// Обращение к несуществующему объекту (издание не найдено в каталоге).
class ObjectNotFoundException : public LibraryException {
public:
    explicit ObjectNotFoundException(const std::string& message)
        : LibraryException("Объект не найден: " + message) {
    }
};

// Попытка создать объект с уже существующим уникальным признаком (то же издание, тот же ISBN).
class DuplicateException : public LibraryException {
public:
    explicit DuplicateException(const std::string& message)
        : LibraryException("Дублирование: " + message) {
    }
};

// Нарушено установленное ограничение (лимит фонда, максимальный срок продления).
class LimitExceededException : public LibraryException {
public:
    explicit LimitExceededException(const std::string& message)
        : LibraryException("Превышено ограничение: " + message) {
    }
};

// Недопустимая операция над объектом в его текущем состоянии (выдать уже выданное, вернуть то, что на полке).
class InvalidOperationException : public LibraryException {
public:
    explicit InvalidOperationException(const std::string& message)
        : LibraryException("Недопустимая операция: " + message) {
    }
};

// Обращение к элементу за пределами допустимого диапазона индексов.
class OutOfRangeException : public LibraryException {
public:
    explicit OutOfRangeException(const std::string& message)
        : LibraryException("Выход за пределы диапазона: " + message) {
    }
};

// Нарушение связи между объектами (издание привязано к другой библиотеке или находится на руках у читателя).
class RelationException : public LibraryException {
public:
    explicit RelationException(const std::string& message)
        : LibraryException("Нарушение связи: " + message) {
    }
};

// Ввод прерван (например, закончился поток ввода).
class InputAbortedException : public LibraryException {
public:
    explicit InputAbortedException(const std::string& message)
        : LibraryException("Ввод прерван: " + message) {
    }
};