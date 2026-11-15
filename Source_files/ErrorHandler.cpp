#include "ErrorHandler.h"
#include <iostream>
#include "exceptions.h"

// Единая точка обработки: вызывается из блока catch(...) и по типу исключения выбирает свою реакцию.
// Возвращает false, если работу программы продолжать нельзя (закрыт поток ввода).
bool handleException() {
    try {
        throw;
    }
    catch (const InvalidDataException& e) {
        std::cout << "\n[ОШИБКА ДАННЫХ] " << e.what() << "\nПроверьте введённые значения и повторите операцию.\n";
    }
    catch (const ObjectNotFoundException& e) {
        std::cout << "\n[НЕ НАЙДЕНО] " << e.what() << "\nПосмотрите каталог (пункт 1) и проверьте название.\n";
    }
    catch (const DuplicateException& e) {
        std::cout << "\n[ДУБЛИКАТ] " << e.what() << "\nОперация отклонена, фонд не изменён.\n";
    }
    catch (const LimitExceededException& e) {
        std::cout << "\n[ОГРАНИЧЕНИЕ] " << e.what() << "\nУменьшите значение или освободите место.\n";
    }
    catch (const InvalidOperationException& e) {
        std::cout << "\n[НЕДОПУСТИМАЯ ОПЕРАЦИЯ] " << e.what() << "\nСостояние издания не изменилось.\n";
    }
    catch (const OutOfRangeException& e) {
        std::cout << "\n[ВЫХОД ЗА ГРАНИЦЫ] " << e.what() << "\nУкажите значение из допустимого диапазона.\n";
    }
    catch (const RelationException& e) {
        std::cout << "\n[СВЯЗЬ НАРУШЕНА] " << e.what() << "\nСначала устраните связь (например, верните издание).\n";
    }
    catch (const InputAbortedException& e) {
        std::cout << "\n[ВВОД ПРЕРВАН] " << e.what() << "\nПрограмма завершает работу.\n";
        return false;
    }
    catch (const LibraryException& e) {
        std::cout << "\n[ОШИБКА БИБЛИОТЕКИ] " << e.what() << "\n";
    }
    catch (const std::exception& e) {
        std::cout << "\n[НЕПРЕДВИДЕННАЯ ОШИБКА] " << e.what() << "\n";
    }
    catch (...) {
        std::cout << "\n[НЕИЗВЕСТНАЯ ОШИБКА]\n";
    }
    return true;
}

// Выполняет действие; любая ошибка обрабатывается, программа продолжает работу.
bool runSafely(const std::function<void()>& action) {
    try {
        action();
    }
    catch (...) {
        return handleException();
    }
    return true;
}
