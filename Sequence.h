#ifndef SEQUENCE_H
#define SEQUENCE_H
#include "DynamicArray.h"
#include "LinkedList.h"
template <class T>
class Sequence 
{
public:
    virtual ~Sequence() = default;
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;
    virtual int GetLength() const = 0;
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;
    virtual Sequence<T>* Clone() const = 0;
    virtual Sequence<T>* Append(T item) = 0;
    virtual Sequence<T>* Prepend(T item) = 0;
    virtual Sequence<T>* InsertAt(T item, int index) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* list) = 0;
};

template <class T>
class MutableArraySequence;
template <class T>
class ImmutableArraySequence;
template <class T>
class BaseArraySequence : public Sequence<T> 
{
protected:
    DynamicArray<T> array;

public:
    BaseArraySequence(T* items, int count) : array(items, count) {}
    BaseArraySequence() : array(0) {}
    BaseArraySequence(const DynamicArray<T>& arr) : array(arr) {}
    T GetFirst() const override { return array.Get(0); }
    T GetLast() const override { return array.Get(array.GetSize() - 1); }
    T Get(int index) const override { return array.Get(index); }
    int GetLength() const override { return array.GetSize(); }
    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override 
    {
        DynamicArray<T> subArray(endIndex - startIndex + 1);
        for (int i = startIndex; i <= endIndex; i++) 
        {
            subArray.Set(i - startIndex, array.Get(i));
        }
        return new MutableArraySequence<T>(subArray);
    }
    Sequence<T>* Clone() const override {
        return new MutableArraySequence<T>(array);
    }
    Sequence<T>* Append(T item) override { return nullptr; }
    Sequence<T>* Prepend(T item) override { return nullptr; }
    Sequence<T>* InsertAt(T item, int index) override { return nullptr; }
    Sequence<T>* Concat(Sequence<T>* list) override { return nullptr; }
};
template <class T>
class MutableArraySequence : public BaseArraySequence<T> 
{
public:
    using BaseArraySequence<T>::BaseArraySequence;
    Sequence<T>* Append(T item) override 
    {
        this->array.Resize(this->array.GetSize() + 1);
        this->array.Set(this->array.GetSize() - 1, item);
        return this;
    }
    Sequence<T>* Prepend(T item) override 
    {
        this->array.InsertAt(item, 0);
        return this;
    }
    Sequence<T>* InsertAt(T item, int index) override 
    {
        this->array.InsertAt(item, index);
        return this;
    } 
    Sequence<T>* Concat(Sequence<T>* seq) override 
    {
        for (int i = 0; i < seq->GetLength(); i++) 
        {
            this->Append(seq->Get(i));
        }
        return this;
    }
};
template <class T>
class ImmutableArraySequence : public BaseArraySequence<T> 
{
public:
    using BaseArraySequence<T>::BaseArraySequence;
    Sequence<T>* Append(T item) override 
    {
        ImmutableArraySequence<T>* newSeq = new ImmutableArraySequence<T>(this->array);
        newSeq->array.Resize(newSeq->array.GetSize() + 1);
        newSeq->array.Set(newSeq->array.GetSize() - 1, item);
        return newSeq;
    }
    Sequence<T>* Prepend(T item) override 
    {
        ImmutableArraySequence<T>* newSeq = new ImmutableArraySequence<T>(this->array);
        newSeq->array.InsertAt(item, 0);
        return newSeq;
    }
    Sequence<T>* InsertAt(T item, int index) override 
    {
        ImmutableArraySequence<T>* newSeq = new ImmutableArraySequence<T>(this->array);
        newSeq->array.InsertAt(item, index);
        return newSeq;
    }
    Sequence<T>* Concat(Sequence<T>* seq) override 
    {
        ImmutableArraySequence<T>* newSeq = new ImmutableArraySequence<T>(this->array);
        for (int i = 0; i < seq->GetLength(); i++) {
            newSeq->Append(seq->Get(i));
        }
        return newSeq;
    }
};
template <class T>
class MutableListSequence;
template <class T>
class ImmutableListSequence;
template <class T>
class BaseListSequence : public Sequence<T> 
{
protected:
    LinkedList<T> list;

public:
    BaseListSequence(T* items, int count) : list(items, count) {}
    BaseListSequence() : list() {}
    BaseListSequence(const LinkedList<T>& list) : list(list) {}
    T GetFirst() const override { return list.GetFirst(); }
    T GetLast() const override { return list.GetLast(); }
    T Get(int index) const override { return list.Get(index); }
    int GetLength() const override { return list.GetLength(); }
    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override 
    {
        LinkedList<T> subList = list.GetSubList(startIndex, endIndex);
        return new MutableListSequence<T>(subList);
    }
    Sequence<T>* Clone() const override 
    {
        return new MutableListSequence<T>(list);
    }
    Sequence<T>* Append(T item) override { return nullptr; }
    Sequence<T>* Prepend(T item) override { return nullptr; }
    Sequence<T>* InsertAt(T item, int index) override { return nullptr; }
    Sequence<T>* Concat(Sequence<T>* list) override { return nullptr; }
};
template <class T>
class MutableListSequence : public BaseListSequence<T> 
{
public:
    using BaseListSequence<T>::BaseListSequence;
    Sequence<T>* Append(T item) override 
    {
        this->list.Append(item);
        return this;
    }
    Sequence<T>* Prepend(T item) override 
    {
        this->list.Prepend(item);
        return this;
    }
    Sequence<T>* InsertAt(T item, int index) override 
    {
        this->list.InsertAt(item, index);
        return this;
    }
    Sequence<T>* Concat(Sequence<T>* seq) override 
    {
        for (int i = 0; i < seq->GetLength(); i++) 
        {
            this->list.Append(seq->Get(i));
        }
        return this;
    }
};
template <class T>
class ImmutableListSequence : public BaseListSequence<T> 
{
public:
    using BaseListSequence<T>::BaseListSequence;
    
    Sequence<T>* Append(T item) override 
    {
        ImmutableListSequence<T>* newSeq = new ImmutableListSequence<T>(this->list);
        newSeq->list.Append(item);
        return newSeq;
    }
    
    Sequence<T>* Prepend(T item) override 
    {
        ImmutableListSequence<T>* newSeq = new ImmutableListSequence<T>(this->list);
        newSeq->list.Prepend(item);
        return newSeq;
    }
    
    Sequence<T>* InsertAt(T item, int index) override 
    {
        ImmutableListSequence<T>* newSeq = new ImmutableListSequence<T>(this->list);
        newSeq->list.InsertAt(item, index);
        return newSeq;
    }
    
    Sequence<T>* Concat(Sequence<T>* seq) override 
    {
        ImmutableListSequence<T>* newSeq = new ImmutableListSequence<T>(this->list);
        for (int i = 0; i < seq->GetLength(); i++) 
        {
            newSeq->list.Append(seq->Get(i));
        }
        return newSeq;
    }
};
#endif