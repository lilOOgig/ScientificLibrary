#pragma once
#include <stdexcept>
#include <string>

// Áàçîâûé êëàññ âñåõ èñêëþ÷åíèé ñèñòåìû. Ïîçâîëÿåò îäíèì catch ïåðåõâàòèòü ëþáóþ "áèáëèîòå÷íóþ" îøèáêó,
// à îòäåëüíûìè catch - îáðàáîòàòü êàæäûé âèä îøèáêè ïî-ñâîåìó.
class LibraryException : public std::runtime_error {
public:
    explicit LibraryException(const std::string& message) : std::runtime_error(message) {}
};

// Íåêîððåêòíûå äàííûå: ïóñòûå ñòðîêè, íåâåðíûé ãîä, íåïîëîæèòåëüíûå ÷èñëà, íóëåâûå óêàçàòåëè, íå-÷èñëî ïðè ââîäå.
class InvalidDataException : public LibraryException {
public:
    explicit InvalidDataException(const std::string& message)
        : LibraryException("Íåêîððåêòíûå äàííûå: " + message) {
    }
};

// Îáðàùåíèå ê íåñóùåñòâóþùåìó îáúåêòó (èçäàíèå íå íàéäåíî â êàòàëîãå).
class ObjectNotFoundException : public LibraryException {
public:
    explicit ObjectNotFoundException(const std::string& message)
        : LibraryException("Îáúåêò íå íàéäåí: " + message) {
    }
};

// Ïîïûòêà ñîçäàòü îáúåêò ñ óæå ñóùåñòâóþùèì óíèêàëüíûì ïðèçíàêîì (òî æå èçäàíèå, òîò æå ISBN).
class DuplicateException : public LibraryException {
public:
    explicit DuplicateException(const std::string& message)
        : LibraryException("Äóáëèðîâàíèå: " + message) {
    }
};

// Íàðóøåíî óñòàíîâëåííîå îãðàíè÷åíèå (ëèìèò ôîíäà, ìàêñèìàëüíûé ñðîê ïðîäëåíèÿ).
class LimitExceededException : public LibraryException {
public:
    explicit LimitExceededException(const std::string& message)
        : LibraryException("Ïðåâûøåíî îãðàíè÷åíèå: " + message) {
    }
};

// Íåäîïóñòèìàÿ îïåðàöèÿ íàä îáúåêòîì â åãî òåêóùåì ñîñòîÿíèè (âûäàòü óæå âûäàííîå, âåðíóòü òî, ÷òî íà ïîëêå).
class InvalidOperationException : public LibraryException {
public:
    explicit InvalidOperationException(const std::string& message)
        : LibraryException("Íåäîïóñòèìàÿ îïåðàöèÿ: " + message) {
    }
};

// Îáðàùåíèå ê ýëåìåíòó çà ïðåäåëàìè äîïóñòèìîãî äèàïàçîíà èíäåêñîâ.
class OutOfRangeException : public LibraryException {
public:
    explicit OutOfRangeException(const std::string& message)
        : LibraryException("Âûõîä çà ïðåäåëû äèàïàçîíà: " + message) {
    }
};

// Íàðóøåíèå ñâÿçè ìåæäó îáúåêòàìè (èçäàíèå ïðèâÿçàíî ê äðóãîé áèáëèîòåêå èëè íàõîäèòñÿ íà ðóêàõ ó ÷èòàòåëÿ).
class RelationException : public LibraryException {
public:
    explicit RelationException(const std::string& message)
        : LibraryException("Íàðóøåíèå ñâÿçè: " + message) {
    }
};

// Ââîä ïðåðâàí (íàïðèìåð, çàêîí÷èëñÿ ïîòîê ââîäà).
class InputAbortedException : public LibraryException {
public:
    explicit InputAbortedException(const std::string& message)
        : LibraryException("Ââîä ïðåðâàí: " + message) {
    }
};
