#include "gtest/gtest.h"
#include "DynamicArray.h"
#include "LinkedList.h"
#include "Sequence.h"
#include <stdexcept>

// Фикс для MinGW
extern "C" 
{
    void _Exit(int status) { exit(status); }
    void quick_exit(int status) { exit(status); }
}

// =================== ТЕСТЫ ДЛЯ DynamicArray =================== //

// Тест конструктора и базового доступа к элементам
TEST(DynamicArrayTest, ConstructorAndGet) 
{
    int items[] = {1, 2, 3, 4, 5};
    DynamicArray<int> arr(items, 5);

    // Проверка корректности размера
    EXPECT_EQ(arr.GetSize(), 5);
    // Проверка доступа к первому элементу
    EXPECT_EQ(arr.Get(0), 1);
    // Проверка доступа к последнему элементу
    EXPECT_EQ(arr.Get(4), 5);
    // Проверка выброса исключения при отрицательном индексе
    EXPECT_THROW(arr.Get(-1), std::out_of_range);
    // Проверка выброса исключения при индексе за пределами массива
    EXPECT_THROW(arr.Get(5), std::out_of_range);
}

// Тест установки значений и изменения размера
TEST(DynamicArrayTest, SetAndResize) 
{
    DynamicArray<int> arr(3);
    // Установка значений элементов
    arr.Set(0, 10);
    arr.Set(1, 20);
    arr.Set(2, 30);

    // Проверка корректности установленных значений
    EXPECT_EQ(arr.Get(0), 10);
    EXPECT_EQ(arr.Get(1), 20);
    EXPECT_EQ(arr.Get(2), 30);
    
    // Увеличение размера массива
    arr.Resize(5);
    EXPECT_EQ(arr.GetSize(), 5);
    // Установка значений в новые элементы
    arr.Set(3, 40);
    arr.Set(4, 50);
    EXPECT_EQ(arr.Get(3), 40);
    
    // Уменьшение размера массива
    arr.Resize(2);
    // Проверка сохранения данных после уменьшения
    EXPECT_EQ(arr.GetSize(), 2);
    EXPECT_EQ(arr.Get(1), 20);
}

// Тест вставки элементов
TEST(DynamicArrayTest, InsertAt) 
{
    int items[] = {1, 2, 3};
    DynamicArray<int> arr(items, 3);
    
    // Вставка элемента в середину
    arr.InsertAt(10, 1);
    EXPECT_EQ(arr.GetSize(), 4);
    // Проверка порядка элементов после вставки
    EXPECT_EQ(arr.Get(0), 1);
    EXPECT_EQ(arr.Get(1), 10);
    EXPECT_EQ(arr.Get(2), 2);
    EXPECT_EQ(arr.Get(3), 3);
    
    // Вставка элемента в начало
    arr.InsertAt(20, 0);
    EXPECT_EQ(arr.Get(0), 20);
    
    // Вставка элемента за пределами текущего размера (должна увеличить массив)
    arr.InsertAt(30, 5);
    EXPECT_EQ(arr.Get(5), 30);
}

// =================== ТЕСТЫ ДЛЯ LinkedList =================== //

// Тест конструктора и базовых операций
TEST(LinkedListTest, ConstructorAndBasicOperations) 
{
    int items[] = {10, 20, 30};
    LinkedList<int> list(items, 3);
    
    // Проверка размера списка
    EXPECT_EQ(list.GetLength(), 3);
    // Проверка первого элемента
    EXPECT_EQ(list.GetFirst(), 10);
    // Проверка последнего элемента
    EXPECT_EQ(list.GetLast(), 30);
    // Проверка доступа по индексу
    EXPECT_EQ(list.Get(1), 20);
    // Проверка обработки недопустимых индексов
    EXPECT_THROW(list.Get(-1), std::out_of_range);
    EXPECT_THROW(list.Get(3), std::out_of_range);
}

// Тест вставки элементов
TEST(LinkedListTest, InsertAndRemove) 
{
    LinkedList<int> list;
    
    // Добавление элементов в конец
    list.Append(10);
    list.Append(20);
    // Добавление элемента в начало
    list.Prepend(5);
    
    // Проверка размера и порядка элементов
    EXPECT_EQ(list.GetLength(), 3);
    EXPECT_EQ(list.GetFirst(), 5);
    EXPECT_EQ(list.GetLast(), 20);
    
    // Вставка элемента по индексу
    list.InsertAt(15, 2);
    EXPECT_EQ(list.Get(2), 15);
    EXPECT_EQ(list.GetLength(), 4);
}

// Тест получения подсписка и объединения списков
TEST(LinkedListTest, SubListAndConcat) 
{
    int items1[] = {1, 2, 3};
    int items2[] = {4, 5, 6};
    LinkedList<int> list1(items1, 3);
    LinkedList<int> list2(items2, 3);
    
    // Получение подсписка
    auto sublist = list1.GetSubList(1, 2);
    EXPECT_EQ(sublist.GetLength(), 2);
    EXPECT_EQ(sublist.GetFirst(), 2);
    
    // Объединение списков
    auto concated = list1.Concat(list2);
    EXPECT_EQ(concated.GetLength(), 6);
    EXPECT_EQ(concated.GetLast(), 6);
}

// =================== ТЕСТЫ ДЛЯ Sequence =================== //

// Тест базовых операций ArraySequence
TEST(SequenceTest, ArraySequenceBasic) 
{
    int items[] = {1, 2, 3};
    MutableArraySequence<int> seq(items, 3);
    
    // Проверка базовых свойств
    EXPECT_EQ(seq.GetLength(), 3);
    EXPECT_EQ(seq.GetFirst(), 1);
    EXPECT_EQ(seq.GetLast(), 3);
    EXPECT_EQ(seq[1], 2);
    
    // Добавление в конец
    seq.Append(4);
    EXPECT_EQ(seq.GetLength(), 4);
    EXPECT_EQ(seq.GetLast(), 4);
    
    // Добавление в начало
    seq.Prepend(0);
    EXPECT_EQ(seq.GetFirst(), 0);
}

// Тест операций ListSequence
TEST(SequenceTest, ListSequenceOperations) 
{
    MutableListSequence<int> seq;
    // Добавление элементов
    seq.Append(10);
    seq.Append(20);
    seq.Prepend(5);
    
    // Проверка состояния
    EXPECT_EQ(seq.GetLength(), 3);
    EXPECT_EQ(seq.GetFirst(), 5);
    
    // Вставка по индексу
    seq.InsertAt(15, 2);
    EXPECT_EQ(seq.Get(2), 15);
    
    // Получение подпоследовательности
    auto subseq = seq.GetSubsequence(1, 2);
    EXPECT_EQ(subseq->GetLength(), 2);
    EXPECT_EQ(subseq->GetFirst(), 10);
    delete subseq;
}

// Тест неизменяемой ArraySequence
TEST(SequenceTest, ImmutableArraySequence) 
{
    int items[] = {1, 2, 3};
    ImmutableArraySequence<int> seq(items, 3);
    
    // Добавление элемента (должен вернуть новый объект)
    auto newSeq = seq.Append(4);
    // Проверка что исходная последовательность не изменилась
    EXPECT_EQ(seq.GetLength(), 3);
    // Проверка новой последовательности
    EXPECT_EQ(newSeq->GetLength(), 4);
    EXPECT_EQ(newSeq->GetLast(), 4);
    delete newSeq;
    
    // Добавление в начало
    newSeq = seq.Prepend(0);
    EXPECT_EQ(newSeq->GetFirst(), 0);
    delete newSeq;
}

// Тест неизменяемой ListSequence
TEST(SequenceTest, ImmutableListSequence) 
{
    ImmutableListSequence<int> seq;
    // Последовательные изменения с созданием новых объектов
    auto seq1 = seq.Append(10);
    auto seq2 = seq1->Append(20);
    
    // Проверка что исходная последовательность не изменилась
    EXPECT_EQ(seq.GetLength(), 0);
    // Проверка промежуточных состояний
    EXPECT_EQ(seq1->GetLength(), 1);
    EXPECT_EQ(seq2->GetLength(), 2);
    
    // Очистка
    delete seq1;
    delete seq2;
}

// Тест обработки исключений
TEST(SequenceExceptionTest, OutOfRange) 
{
    MutableArraySequence<int> seq;
    
    // Проверка операций с пустой последовательностью
    EXPECT_THROW(seq.GetFirst(), std::out_of_range);
    EXPECT_THROW(seq.GetLast(), std::out_of_range);
    EXPECT_THROW(seq.Get(0), std::out_of_range);
    
    // Добавление элемента
    seq.Append(1);
    // Проверка граничных значений
    EXPECT_EQ(seq.GetFirst(), 1);
    EXPECT_EQ(seq.GetLast(), 1);
    
    // Проверка недопустимых индексов
    EXPECT_THROW(seq.Get(-1), std::out_of_range);
    EXPECT_THROW(seq.Get(1), std::out_of_range);
    
    // Проверка недопустимых позиций вставки
    EXPECT_THROW(seq.InsertAt(2, -1), std::out_of_range);
    EXPECT_THROW(seq.InsertAt(2, 2), std::out_of_range);
}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}