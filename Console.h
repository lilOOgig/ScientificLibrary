#pragma once
#include <string>
#include <string_view>

// ¬вод и оформление вывода в консоли
int readNumber(std::string_view prompt);         // пункт меню: при неверном вводе просит повторить, при конце ввода возвращает 0
std::string readText(std::string_view prompt);   // строка целиком; закрытый ввод -> InputAbortedException
int readInteger(std::string_view prompt);        // целое число; не число -> InvalidDataException
void section(std::string_view title);            // крупный заголовок раздела
void step(std::string_view text);                // подзаголовок шага