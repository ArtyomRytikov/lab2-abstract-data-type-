#include "menu.h"
#include <locale>

using namespace std;

int main() 
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    SequenceMenu<int> menu;
    menu.showMainMenu();
    return 0;
}