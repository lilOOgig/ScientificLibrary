#pragma once
#include <memory>
#include "ScientificLibrary.h"

// Пункты меню, в которых все данные вводятся с клавиатуры.
// Ошибки не перехватываются здесь: их обрабатывает main через handleException().
void issueFromInput(const ScientificLibrary& lib);
void returnFromInput(const ScientificLibrary& lib);
void extendFromInput(const ScientificLibrary& lib);
void searchFromInput(const ScientificLibrary& lib);
void showByTypeFromInput(const ScientificLibrary& lib);
void showSortedFromInput(const ScientificLibrary& lib);
void showByNumberFromInput(const ScientificLibrary& lib);
void detailsFromInput(const ScientificLibrary& lib);
void addFromInput(const std::shared_ptr<ScientificLibrary>& lib);
void removeFromInput(const std::shared_ptr<ScientificLibrary>& lib);
void removeByNumberFromInput(const std::shared_ptr<ScientificLibrary>& lib);
