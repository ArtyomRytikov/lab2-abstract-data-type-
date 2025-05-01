#include "menu.h"
using namespace std;
template <typename T>
void SequenceMenu<T>::showMainMenu() 
{
    while (true) 
    {
        cout << "\nГлавное меню:\n";
        cout << "1. Создать ArraySequence\n";
        cout << "2. Создать ListSequence\n";
        cout << "0. Выход\n";
        cout << "Выберите вариант: ";
        int menu;
        cin >> menu;
        if (cin.fail()) 
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Неверный ввод. Пожалуйста, введите число.\n";
            continue;
        }
        if (menu == 0) break;
        try 
        {
            Sequence<T>* seq = nullptr;
            if (menu == 1) 
            {
                seq = createSequence(true);
            } 
            else if (menu == 2) 
            {
                seq = createSequence(false);
            } 
            else 
            {
                cout << "Неверный выбор. Попробуйте снова.\n";
                continue;
            }
            if (seq) 
            {
                processSequence(seq);
                delete seq;
            }
        } 
        catch (const exception& e) 
        {
            cout << "Ошибка: " << e.what() << "\n";
        }
    }
}
template <typename T>
Sequence<T>* SequenceMenu<T>::createSequence(bool isArray) 
{
    int size;
    cout << "Введите размер последовательности: ";
    cin >> size;
    if (size <= 0) 
    {
        throw invalid_argument("Размер должен быть положительным");
    }
    T* items = new T[size];
    cout << "Введите " << size << " элементов:\n";
    for (int i = 0; i < size; i++) 
    {
        cout << "Элемент " << (i + 1) << ": ";
        cin >> items[i];
    }
    Sequence<T>* sequence;
    if (isArray) 
    {
        sequence = new MutableArraySequence<T>(items, size);
    } 
    else 
    {
        sequence = new MutableListSequence<T>(items, size);
    }
    delete[] items;
    return sequence;
}

template <typename T>
void SequenceMenu<T>::processSequence(Sequence<T>* seq) 
{
    while (true) 
    {
        cout << "\nОперации с последовательностью:\n";
        cout << "1. Получить первый элемент\n";
        cout << "2. Получить последний элемент\n";
        cout << "3. Получить элемент по индексу\n";
        cout << "4. Добавить в конец\n";
        cout << "5. Добавить в начало\n";
        cout << "6. Вставить по индексу\n";
        cout << "7. Объединить с другой последовательностью\n";
        cout << "8. Получить подпоследовательность\n";
        cout << "9. Получить длину\n";
        cout << "10. Вывести все элементы\n";
        cout << "0. Вернуться в главное меню\n";
        cout << "Выберите операцию: ";
        int operation;
        cin >> operation;
        if (operation == 0) break;
        try 
        {
            if (operation == 1) 
            {
                cout << "Первый элемент: " << seq->GetFirst() << "\n";
            }
            else if (operation == 2) 
            {
                cout << "Последний элемент: " << seq->GetLast() << "\n";
            }
            else if (operation == 3) 
            {
                int index;
                cout << "Введите индекс: ";
                cin >> index;
                cout << "Элемент: " << seq->Get(index) << "\n";
            }
            else if (operation == 4) 
            {
                T value;
                cout << "Введите значение: ";
                cin >> value;
                seq = seq->Append(value);
                cout << "Элемент добавлен.\n";
            }
            else if (operation == 5) 
            {
                T value;
                cout << "Введите значение: ";
                cin >> value;
                seq = seq->Prepend(value);
                cout << "Элемент добавлен.\n";
            }
            else if (operation == 6) 
            {
                int index;
                T value;
                cout << "Введите индекс: ";
                cin >> index;
                cout << "Введите значение: ";
                cin >> value;
                seq = seq->InsertAt(value, index);
                cout << "Элемент вставлен.\n";
            }
            else if (operation == 7) 
            {
                cout << "Создайте последовательность для объединения:\n";
                Sequence<T>* other = createSequence(true);
                seq = seq->Concat(other);
                delete other;
                cout << "Последовательности объединены.\n";
            }
            else if (operation == 8) 
            {
                int start, end;
                cout << "Введите начальный индекс: ";
                cin >> start;
                cout << "Введите конечный индекс: ";
                cin >> end;
                Sequence<T>* subseq = seq->GetSubsequence(start, end);
                cout << "Подпоследовательность: ";
                for (int i = 0; i < subseq->GetLength(); i++) 
                {
                    cout << subseq->Get(i) << " ";
                }
                cout << "\n";
                delete subseq;
            }
            else if (operation == 9) 
            {
                cout << "Длина: " << seq->GetLength() << "\n";
            }
            else if (operation == 10) 
            {
                cout << "Элементы: ";
                for (int i = 0; i < seq->GetLength(); i++) 
                {
                    cout << seq->Get(i) << " ";
                }
                cout << "\n";
            }
        } 
        catch (const exception& e) 
        {
            cout << "Ошибка: " << e.what() << "\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}
template class SequenceMenu<int>;