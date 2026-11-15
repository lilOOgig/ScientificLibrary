#pragma once
#include <string>
#include <string_view>

// Ââîä è îôîðìëåíèå âûâîäà â êîíñîëè
int readNumber(std::string_view prompt);         // ïóíêò ìåíþ: ïðè íåâåðíîì ââîäå ïðîñèò ïîâòîðèòü, ïðè êîíöå ââîäà âîçâðàùàåò 0
std::string readText(std::string_view prompt);   // ñòðîêà öåëèêîì; çàêðûòûé ââîä -> InputAbortedException
int readInteger(std::string_view prompt);        // öåëîå ÷èñëî; íå ÷èñëî -> InvalidDataException
void section(std::string_view title);            // êðóïíûé çàãîëîâîê ðàçäåëà
void step(std::string_view text);                // ïîäçàãîëîâîê øàãà
