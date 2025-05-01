#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <limits>
#include "Sequence.h"
template <typename T>
class SequenceMenu {
public:
    void showMainMenu();
    void processSequence(Sequence<T>* seq);
    Sequence<T>* createSequence(bool isArray);
};

#endif