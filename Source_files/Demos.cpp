#include "Demos.h"
#include <iostream>
#include <memory>
#include <vector>
#include "Book.h"
#include "Console.h"
#include "ErrorHandler.h"
#include "ScientificLibrary.h"
#include "exceptions.h"

// ---------- ëàá. ¹6: îáðàáîòêà èñêëþ÷åíèé ----------

namespace {

    std::shared_ptr<ScientificLibrary> makeDemoLibrary(size_t capacity) {
        auto lib = std::make_shared<ScientificLibrary>("Äåìî-áèáëèîòåêà", capacity);
        *lib += std::make_shared<Book>("Òåñòîâàÿ êíèãà", "Àâòîð À.À.", 2020, 300);
        return lib;
    }

    void demoInvalidData() {
        step("InvalidDataException: êíèãà ñ îòðèöàòåëüíûì ÷èñëîì ñòðàíèö");
        Book book("Íåêîððåêòíàÿ êíèãà", "Àâòîð À.À.", 2020, -5);
    }

    void demoLimitExceeded() {
        step("LimitExceededException: äîáàâëåíèå â áèáëèîòåêó, ðàññ÷èòàííóþ íà 1 èçäàíèå");
        auto lib = makeDemoLibrary(1);
        *lib += std::make_shared<Book>("Âòîðàÿ êíèãà", "Àâòîð Á.Á.", 2021, 200);
    }

    void demoDuplicate() {
        step("DuplicateException: ïîâòîðíîå äîáàâëåíèå òàêîãî æå èçäàíèÿ");
        auto lib = makeDemoLibrary(5);
        *lib += std::make_shared<Book>("Òåñòîâàÿ êíèãà", "Àâòîð À.À.", 2020, 300);
    }

    void demoNotFound() {
        step("ObjectNotFoundException: âûäà÷à íåñóùåñòâóþùåãî èçäàíèÿ");
        makeDemoLibrary(5)->issuePublication("Íåñóùåñòâóþùàÿ êíèãà", "Èâàíîâ È.È.");
    }

    void demoOutOfRange() {
        step("OutOfRangeException: îáðàùåíèå ê èçäàíèþ ïîä íîìåðîì 10 â êàòàëîãå èç îäíîãî èçäàíèÿ");
        makeDemoLibrary(5)->getByNumber(10);
    }

    void demoInvalidOperation() {
        step("InvalidOperationException: ïîâòîðíàÿ âûäà÷à óæå âûäàííîãî èçäàíèÿ");
        auto lib = makeDemoLibrary(5);
        lib->issuePublication("Òåñòîâàÿ êíèãà", "Èâàíîâ È.È.");
        lib->issuePublication("Òåñòîâàÿ êíèãà", "Ïåòðîâ Ï.Ï.");
    }

    void demoRelation() {
        step("RelationException: ñïèñàíèå èçäàíèÿ, êîòîðîå íàõîäèòñÿ íà ðóêàõ ó ÷èòàòåëÿ");
        auto lib = makeDemoLibrary(5);
        lib->issuePublication("Òåñòîâàÿ êíèãà", "Èâàíîâ È.È.");
        lib->removePublication("Òåñòîâàÿ êíèãà");
    }

}  // namespace

bool demonstrateExceptions() {
    section("Ëàá ¹6: äåìîíñòðàöèÿ èñêëþ÷èòåëüíûõ ñèòóàöèé");
    const std::vector<void (*)()> demos = {
        demoInvalidData, demoLimitExceeded, demoDuplicate, demoNotFound,
        demoOutOfRange, demoInvalidOperation, demoRelation
    };
    for (auto demo : demos) {
        if (!runSafely(demo)) return false;
    }
    std::cout << "\nÂñå ñèòóàöèè îáðàáîòàíû, ïðîãðàììà ïðîäîëæàåò ðàáîòó.\n";
    return true;
}
