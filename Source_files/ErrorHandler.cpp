#include "ErrorHandler.h"
#include <iostream>
#include "exceptions.h"

// Åäèíàÿ òî÷êà îáðàáîòêè: âûçûâàåòñÿ èç áëîêà catch(...) è ïî òèïó èñêëþ÷åíèÿ âûáèðàåò ñâîþ ðåàêöèþ.
// Âîçâðàùàåò false, åñëè ðàáîòó ïðîãðàììû ïðîäîëæàòü íåëüçÿ (çàêðûò ïîòîê ââîäà).
bool handleException() {
    try {
        throw;
    }
    catch (const InvalidDataException& e) {
        std::cout << "\n[ÎØÈÁÊÀ ÄÀÍÍÛÕ] " << e.what() << "\nÏðîâåðüòå ââåä¸ííûå çíà÷åíèÿ è ïîâòîðèòå îïåðàöèþ.\n";
    }
    catch (const ObjectNotFoundException& e) {
        std::cout << "\n[ÍÅ ÍÀÉÄÅÍÎ] " << e.what() << "\nÏîñìîòðèòå êàòàëîã (ïóíêò 1) è ïðîâåðüòå íàçâàíèå.\n";
    }
    catch (const DuplicateException& e) {
        std::cout << "\n[ÄÓÁËÈÊÀÒ] " << e.what() << "\nÎïåðàöèÿ îòêëîíåíà, ôîíä íå èçìåí¸í.\n";
    }
    catch (const LimitExceededException& e) {
        std::cout << "\n[ÎÃÐÀÍÈ×ÅÍÈÅ] " << e.what() << "\nÓìåíüøèòå çíà÷åíèå èëè îñâîáîäèòå ìåñòî.\n";
    }
    catch (const InvalidOperationException& e) {
        std::cout << "\n[ÍÅÄÎÏÓÑÒÈÌÀß ÎÏÅÐÀÖÈß] " << e.what() << "\nÑîñòîÿíèå èçäàíèÿ íå èçìåíèëîñü.\n";
    }
    catch (const OutOfRangeException& e) {
        std::cout << "\n[ÂÛÕÎÄ ÇÀ ÃÐÀÍÈÖÛ] " << e.what() << "\nÓêàæèòå çíà÷åíèå èç äîïóñòèìîãî äèàïàçîíà.\n";
    }
    catch (const RelationException& e) {
        std::cout << "\n[ÑÂßÇÜ ÍÀÐÓØÅÍÀ] " << e.what() << "\nÑíà÷àëà óñòðàíèòå ñâÿçü (íàïðèìåð, âåðíèòå èçäàíèå).\n";
    }
    catch (const InputAbortedException& e) {
        std::cout << "\n[ÂÂÎÄ ÏÐÅÐÂÀÍ] " << e.what() << "\nÏðîãðàììà çàâåðøàåò ðàáîòó.\n";
        return false;
    }
    catch (const LibraryException& e) {
        std::cout << "\n[ÎØÈÁÊÀ ÁÈÁËÈÎÒÅÊÈ] " << e.what() << "\n";
    }
    catch (const std::exception& e) {
        std::cout << "\n[ÍÅÏÐÅÄÂÈÄÅÍÍÀß ÎØÈÁÊÀ] " << e.what() << "\n";
    }
    catch (...) {
        std::cout << "\n[ÍÅÈÇÂÅÑÒÍÀß ÎØÈÁÊÀ]\n";
    }
    return true;
}

// Âûïîëíÿåò äåéñòâèå; ëþáàÿ îøèáêà îáðàáàòûâàåòñÿ, ïðîãðàììà ïðîäîëæàåò ðàáîòó.
bool runSafely(const std::function<void()>& action) {
    try {
        action();
    }
    catch (...) {
        return handleException();
    }
    return true;
}
