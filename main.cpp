#include <iostream>
#include <locale>
#include "menu.h"
using namespace std;
int main() 
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    run_menu();
    return 0;
}