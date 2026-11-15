#pragma once
#include <memory>
#include "ScientificLibrary.h"

void printMenu();
void executeChoice(int choice, const std::shared_ptr<ScientificLibrary>& lib);   