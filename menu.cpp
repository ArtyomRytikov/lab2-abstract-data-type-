#include "menu.h"
#include "DynamicArray.h"
#include "LinkedList.h"

void menu() 
{
    cout << "Выберите тип последовательности:" << endl;
    cout << "1. Последовательность на основе массива" << endl;
    cout << "2. Последовательность на основе списка" << endl;
    cout << "0. Выход" << endl;
}

int get_menu(int min, int max) 
{
    int menu;
    while (true) 
    {
        cout << "Введите выбор: ";
        cin >> menu;
        cout << "\n";
        if (cin.fail()) 
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Неверный ввод. Повторите." << endl;
            continue;
        }
        if (menu < min || menu > max) 
        {
            cout << "Пожалуйста, выберите от " << min << " до " << max + 1 << "." << endl;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return menu;
    }
}

void run_menu() 
{
    while (true) 
    {
        menu();
        int menu = get_menu(0, 2);
        if (menu == 0) break;
        if (menu == 1) 
        {
            menu_ArraySequence();
        } 
        else if (menu == 2) 
        {
            menu_ListSequence();
        }
    }
}

void menu_ArraySequence() 
{
    cout <<"Вы выбрали последовательность на основе массива." << endl;
    int size;
    cout << "Введите размер последовательности: ";
    cin >> size;
    if (size <= 0) 
    {
        cout << "Размер должен быть положительным." << endl;
        return;
    }
    int* items = new int[size];
    cout << "Введите " << size << " элементов:" << endl;
    for (int i = 0; i < size; ++i) 
    {
        cout << "Элемент " << (i + 1) << ": ";
        cin >> items[i];
    }
    Sequence<int>* sequence = new ArraySequence<int>(items, size);
    delete[] items;
    processSequence(sequence);
    delete sequence;
}

void menu_ListSequence() 
{
    cout <<"Вы выбрали последовательность на основе списка." << endl;
    int size;
    cout << "Введите размер последовательности: ";
    cin >> size;
    if (size <= 0) 
    {
        cout << "Размер должен быть положительным." << endl;
        return;
    }
    int* items = new int[size];
    cout << "Введите " << size << " элементов:" << endl;
    for (int i = 0; i < size; ++i) 
    {
        cout << "Элемент " << (i + 1) << ": ";
        cin >> items[i];
    }
    Sequence<int>* sequence = new ListSequence<int>(items, size);
    delete[] items;
    processSequence(sequence);
    delete sequence;
}

void processSequence(Sequence<int>* sequence) 
{
    while (true) 
    {
        cout << "\n";
        cout << "Доступные операции:" << endl;
        cout << "1. Получить первый элемент" << endl;
        cout << "2. Получить последний элемент" << endl;
        cout << "3. Получить элемент по индексу" << endl;
        cout << "4. Добавить элемент в конец" << endl;
        cout << "5. Добавить элемент в начало" << endl;
        cout << "6. Вставить элемент по индексу" << endl;
        cout << "7. Получить длину последовательности" << endl;
        cout << "8. Вывести все элементы" << endl;
        cout << "0. Вернуться в главное меню" << endl;
        int operation = get_menu(0, 7);
        if (operation == 0) break;
        try 
        {
            if (operation == 1) 
            {
                cout << "Первый элемент: " << sequence->GetFirst() << endl;
            }
            else if (operation == 2) 
            {
                cout << "Последний элемент: " << sequence->GetLast() << endl;
            }
            else if (operation == 3) 
            {
                int index;
                cout << "Введите индекс: ";
                cin >> index;
                cout << "Элемент: " << sequence->Get(index) << endl;
            }
            else if (operation == 4) 
            {
                int value;
                cout << "Введите значение: ";
                cin >> value;
                sequence = sequence->Append(value);
                cout << "Элемент добавлен." << endl;
            }
            else if (operation == 5) 
            {
                int value;
                cout << "Введите значение: ";
                cin >> value;
                sequence = sequence->Prepend(value);
                cout << "Элемент добавлен." << endl;
            }
            else if (operation == 6) 
            {
                int index, value;
                cout << "Введите индекс: ";
                cin >> index;
                cout << "Введите значение: ";
                cin >> value;
                sequence = sequence->InsertAt(value, index);
                cout << "Элемент вставлен." << endl;
            }
            else if (operation == 7) 
            {
                cout << "Длина последовательности: " << sequence->GetLength() << endl;
            }
            else if (operation == 8) 
            {
                cout << "Элементы последовательности: ";
                for (int i = 0; i < sequence->GetLength(); ++i) 
                {
                    cout << sequence->Get(i) << " ";
                }
                cout << endl;
            }
        } 
        catch (const exception& e) 
        {
            cout << "Ошибка: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}