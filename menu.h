#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <limits>
#include "Sequence.h"
using namespace std;
void menu();
int get_menu(int min, int max);
void run_menu();
void processSequence(Sequence<int>* sequence);
void menu_ArraySequence();
void menu_ListSequence();
#endif 