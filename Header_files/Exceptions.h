#pragma once
#include <format>
#include <stdexcept>
#include <string>

// Базовый класс всех исключений системы. Позволяет одним catch перехватить любую "библиотечную" ошибку,
// а отдельными catch - обработать каждый вид ошибки по-своему.
class LibraryException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

// Некорректные данные: пустые строки, неверный год, неположительные числа, нулевые указатели, не-число при вводе.
class InvalidDataException : public LibraryException {
public:
    explicit InvalidDataException(const std::string& message)
        : LibraryException(std::format("Некорректные данные: {}", message)) {}
};

// Обращение к несуществующему объекту (издание не найдено в каталоге).
class ObjectNotFoundException : public LibraryException {
public:
    explicit ObjectNotFoundException(const std::string& message)
        : LibraryException(std::format("Объект не найден: {}", message)) {}
};

// Попытка создать объект с уже существующим уникальным признаком (то же издание, тот же ISBN).
class DuplicateException : public LibraryException {
public:
    explicit DuplicateException(const std::string& message)
        : LibraryException(std::format("Дублирование: {}", message)) {}
};

// Нарушено установленное ограничение (лимит фонда, максимальный срок продления).
class LimitExceededException : public LibraryException {
public:
    explicit LimitExceededException(const std::string& message)
        : LibraryException(std::format("Превышено ограничение: {}", message)) {}
};

// Недопустимая операция над объектом в его текущем состоянии (выдать уже выданное, вернуть то, что на полке).
class InvalidOperationException : public LibraryException {
public:
    explicit InvalidOperationException(const std::string& message)
        : LibraryException(std::format("Недопустимая операция: {}", message)) {}
};

// Обращение к элементу за пределами допустимого диапазона индексов.
class OutOfRangeException : public LibraryException {
public:
    explicit OutOfRangeException(const std::string& message)
        : LibraryException(std::format("Выход за пределы диапазона: {}", message)) {}
};

// Нарушение связи между объектами (издание привязано к другой библиотеке или находится на руках у читателя).
class RelationException : public LibraryException {
public:
    explicit RelationException(const std::string& message)
        : LibraryException(std::format("Нарушение связи: {}", message)) {}
};

// Ввод прерван (например, закончился поток ввода).
class InputAbortedException : public LibraryException {
public:
    explicit InputAbortedException(const std::string& message)
        : LibraryException(std::format("Ввод прерван: {}", message)) {}
};
