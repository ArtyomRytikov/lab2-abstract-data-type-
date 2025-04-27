#ifndef SEQUENCE_H
#define SEQUENCE_H
#include "DynamicArray.h"
#include "LinkedList.h"
template <class T>
class Sequence 
{
public:
    virtual T GetFirst() = 0;
    virtual T GetLast() = 0;
    virtual T Get(int index) = 0;
    virtual int GetLength() = 0;
    virtual Sequence<T>* Append(T item) = 0;
    virtual Sequence<T>* Prepend(T item) = 0;
    virtual Sequence<T>* InsertAt(T item, int index) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* list) = 0;
};
template <class T>
class ArraySequence : public Sequence<T> 
{
private:
    DynamicArray<T> array;

public:
    ArraySequence(T* items, int count) : array(items, count) {}
    ArraySequence() : array(0) {}
    ArraySequence(const LinkedList<T>& list);

    T GetFirst() override { return array.Get(0); }
    T GetLast() override { return array.Get(array.GetSize() - 1); }
    T Get(int index) override { return array.Get(index); }
    int GetLength() override { return array.GetSize(); }
    Sequence<T>* Append(T item) override 
    {
        array.Resize(array.GetSize() + 1);
        array.Set(array.GetSize() - 1, item);
        return this;
    }
    Sequence<T>* Prepend(T item) override 
    {
        DynamicArray<T> newArray(array.GetSize() + 1);
        newArray.Set(0, item);
        for (int i = 0; i < array.GetSize(); ++i) 
        {
            newArray.Set(i + 1, array.Get(i));
        }
        array = newArray;
        return this;
    }
    Sequence<T>* InsertAt(T item, int index) override 
    {
        if (index < 0 || index > array.GetSize()) throw std::out_of_range("Индекс вне диапазона");
        DynamicArray<T> newArray(array.GetSize() + 1);
        for (int i = 0; i < index; ++i) 
        {
            newArray.Set(i, array.Get(i));
        }
        newArray.Set(index, item);
        for (int i = index; i < array.GetSize(); ++i) 
        {
            newArray.Set(i + 1, array.Get(i));
        }
        array = newArray;
        return this;
    }
    Sequence<T>* Concat(Sequence<T>* seq) override 
    {
        if (seq->GetLength() == 0) return this;
        T newItems[seq->GetLength()];
        for (int i = 0; i < seq->GetLength(); ++i) 
        {
            newItems[i] = seq->Get(i);
        }
        for (int i = 0; i < seq->GetLength(); ++i)
        {
            Append(newItems[i]);
        }
        return this;
    }
};
template <class T>
class ListSequence : public Sequence<T> 
{
private:
    LinkedList<T> list;

public:
    ListSequence(T* items, int count) : list(items, count) {}
    ListSequence() : list() {}
    ListSequence(const LinkedList<T>& list) : list(list) {}

    T GetFirst() override { return list.GetFirst(); }
    T GetLast() override { return list.GetLast(); }
    T Get(int index) override { return list.Get(index); }
    int GetLength() override { return list.GetLength(); }
    Sequence<T>* Append(T item) override 
    {
        list.Append(item);
        return this;
    }
    Sequence<T>* Prepend(T item) override 
    {
        list.Prepend(item);
        return this;
    }
    Sequence<T>* InsertAt(T item, int index) override 
    {
        list.InsertAt(item, index);
        return this;
    }
    Sequence<T>* Concat(Sequence<T>* seq) override 
    {
        ListSequence<T>* result = new ListSequence<T>(*this);
        if (seq->GetLength() == 0) return result;

        for (int i = 0; i < seq->GetLength(); ++i) 
        {
            result->Append(seq->Get(i));
        }
        return result;
    }
};
#endif