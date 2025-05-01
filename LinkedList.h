#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdexcept>

template <class T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };
    
    Node* head;
    int length;

public:
    LinkedList(T* items, int count) : head(nullptr), length(0) {
        for (int i = 0; i < count; ++i) {
            Append(items[i]);
        }
    }

    LinkedList() : head(nullptr), length(0) {}

    LinkedList(const LinkedList<T>& list) : head(nullptr), length(0) {
        Node* current = list.head;
        while (current) {
            Append(current->data);
            current = current->next;
        }
    }

    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    T GetFirst() const {
        if (!head) throw std::runtime_error("Список пуст");
        return head->data;
    }

    T GetLast() const {
        if (!head) throw std::runtime_error("Список пуст");
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        return current->data;
    }

    T Get(int index) const {
        if (index < 0 || index >= length) throw std::out_of_range("Индекс вне диапазона");
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    LinkedList<T> GetSubList(int startIndex, int endIndex) const {
        if (startIndex < 0 || endIndex >= length || startIndex > endIndex) 
            throw std::out_of_range("Индекс вне диапазона");
        
        LinkedList<T> sublist;
        Node* current = head;

        for (int i = 0; current && i <= endIndex; ++i) {
            if (i >= startIndex) {
                sublist.Append(current->data);
            }
            current = current->next;
        }
        return sublist;
    }

    int GetLength() const {
        return length;
    }

    void Append(T item) {
        Node* newNode = new Node(item);
        if (!head) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        length++;
    }

    void Prepend(T item) {
        Node* newNode = new Node(item);
        newNode->next = head;
        head = newNode;
        length++;
    }

    void InsertAt(T item, int index) {
        if (index < 0 || index > length) throw std::out_of_range("Индекс вне диапазона");
        if (index == 0) {
            Prepend(item);
        } else {
            Node* current = head;
            for (int i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            Node* newNode = new Node(item);
            newNode->next = current->next;
            current->next = newNode;
            length++;
        }
    }

    LinkedList<T> Concat(const LinkedList<T>& list) const {
        LinkedList<T> result(*this);
        Node* current = list.head;
        while (current) {
            result.Append(current->data);
            current = current->next;
        }
        return result;
    }
};
#endif