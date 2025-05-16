#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H
#include <stdexcept>
template <class T>
class DynamicArray 
{
private:
    T* items;
    int size;

public:
    DynamicArray(T* items, int count) : size(count) 
    {
        this->items = new T[size];
        for (int i = 0; i < size; i++) 
        {
            this->items[i] = items[i];
        }
    }
    DynamicArray(int size) : size(size) 
    {
        this->items = new T[size];
    }
    DynamicArray(const DynamicArray<T>& dynamicArray) : size(dynamicArray.size) 
    {
        items = new T[size];
        for (int i = 0; i < size; i++) 
        {
            items[i] = dynamicArray.items[i];
        }
    }
    ~DynamicArray() 
    {
        delete[] items;
    }
    const T& Get(int index) const 
    {
        if (index < 0 || index >= size) throw std::out_of_range("Индекс вне диапазона");
        return items[index];
    }

    T& Get(int index) 
    {
        if (index < 0 || index >= size) throw std::out_of_range("Индекс вне диапазона");
        return items[index];
    }
    int GetSize() const 
    {
        return size;
    }
    void Set(int index, T value) 
    {
        if (index < 0 || index >= size) throw std::out_of_range("Индекс вне диапазона");
        items[index] = value;
    }
    void Resize(int newSize) 
    {
        T* newItems = new T[newSize];
        int copySize = (newSize < size) ? newSize : size;
        for (int i = 0; i < copySize; i++) 
        {
            newItems[i] = items[i];
        }
        delete[] items;
        items = newItems;
        size = newSize;
    }
    void InsertAt(T item, int index) 
    {
        if (index < 0 || index > size) throw std::out_of_range("Индекс вне диапазона");
        Resize(size + 1);
        for (int i = size - 1; i > index; i--) 
        {
            items[i] = items[i - 1];
        }
        items[index] = item;
    }
};
#endif