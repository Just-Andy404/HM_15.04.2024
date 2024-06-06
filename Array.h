/*
Создать шаблонный класс-контейнер Array, который
является массивом, который позволяет хранить объекты заданного типа.
Класс должен реализовывать следующие функции:
■ GetSize - получение размера массива (количество элементов, под которые выделена память);
SetSize (int size, int grow = 1) - чтобы выбрать размер
массива (если параметр size больше предыдущего
размер массива, то выделяется дополнительный блок памяти, если нет, то "лишние" элементы теряются и память
освобождается); параметр grow определяет для какого количества элементов необходимо выделить память, если
количество элементов есть больше текущего размера
массива. Например, SetSize (5, 5); означает, что во время
добавления 6-го элемента размер массива становится равным
10, при добавлении 11-го - 15 и т.д.;
■ GetUpperBound - получение последнего допустимого
индекса в массиве. Например, если при размере массива 10,
вы добавляете в него 4 элемента, то функция вернет 3;
■ IsEmpty - массив пустой ?;
■ FreeExtra - удалить "лишнюю" память (выше последнего допустимого индекса);
■ GetAt - получение определенного элемента (по индексу);
SetAt - установка нового значения для определенного
элемента (индекс элемента должен быть меньше
текущий размер массива);
■ operator [] - для реализации двух предыдущих функций;
■ Add - добавление элемента в массив (при необходимости
массив увеличивается на значение grow функции SetSize);
■ Append - "сложение" двух массивов;
■ operator =;
■ InsertAt - вставка элемента (-ов) в заданную позицию;
■ RemoveAt - удаление элемента (-ов) из заданной позиции.
*/
#pragma once
#include <iostream>

using namespace std;

template<class T>
class Array {
    T* _array;
    int _size;
    int _capacity;
    int _grow;

public:
    Array() : _size(0), _capacity(1), _grow(2) { 
        _array = new T[_capacity];
    }

    explicit Array(int capacity) : _size(0), _capacity(capacity), _grow(2) {
        _array = new T[_capacity];
    }

    Array(const Array& other) : _size(other._size), _capacity(other._capacity), _grow(other._grow) {
        _array = new T[_capacity];
        for (int i = 0; i < _size; i++) {
            _array[i] = other._array[i];
        }
    }

    ~Array() {
        delete[] _array;
    }

    int getSize() const {
        return _size;
    }

    void setSize(int capacity, int grow) {
        if (capacity < _size || capacity == _capacity) return;
        T* newArr = new T[capacity];
        for (int i = 0; i < _size; i++) {
            newArr[i] = _array[i];
        }
        delete[] _array;
        _array = newArr;
        _capacity = capacity;
        _grow = grow;
    }

    int getUpperBound() const {
        return _size - 1;
    }

    bool isEmpty() const {
        return _size == 0;
    }

    void freeExtra() {
        if (_size == _capacity) return;
        T* newArr = new T[_size];
        for (int i = 0; i < _size; i++) {
            newArr[i] = _array[i];
        }
        delete[] _array;
        _array = newArr;
        _capacity = _size;
    }

    T getAt(int index) const {
        if (index < 0 || index >= _size) {
            return T();  
        }
        return _array[index];
    }

    void setAt(T value, int index) {
        if (index >= 0 && index < _size) {
            _array[index] = value;
        }
    }

    T& operator[](int index) {
        if (index < 0 || index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _array[index];
    }

    void add(T element) {
        if (_size >= _capacity) {
            _capacity = _capacity * _grow; 
            T* newArr = new T[_capacity];
            for (int i = 0; i < _size; i++) {
                newArr[i] = _array[i];
            }
            delete[] _array;
            _array = newArr;
        }
        _array[_size++] = element;
    }

    void append(const Array& other) {
        int newCapacity = _size + other._size;
        T* newArr = new T[newCapacity];
        for (int i = 0; i < _size; i++) {
            newArr[i] = _array[i];
        }
        for (int i = 0; i < other._size; i++) {
            newArr[_size + i] = other._array[i];
        }
        delete[] _array;
        _array = newArr;
        _size += other._size;
        _capacity = newCapacity;
    }

    T* getData() const {
        return _array; 
    }


    void insertAt(const T* elements, int numElements, int index) {
        if (index > _size) { 
            std::cout << "Index out of range\n";
            return;
        }
        if (_size + numElements > _capacity) {
            _capacity += (_grow + numElements);
            T* newArray = new T[_capacity];
            for (int i = 0; i < index; ++i) {
                newArray[i] = _array[i];
            }
            for (int i = 0; i < numElements; ++i) {
                newArray[index + i] = elements[i];
            }
            for (int i = index; i < _size; ++i) {
                newArray[i + numElements] = _array[i];
            }
            delete[] _array;
            _array = newArray;
        }
        else {
            for (int i = _size - 1; i >= index; --i) {
                _array[i + numElements] = _array[i];
            }
            for (int i = 0; i < numElements; ++i) {
                _array[index + i] = elements[i];
            }
        }
        _size += numElements;
    }

    void removeAt(int index, int count = 1) {
        if (index < 0 || index >= _size || index + count > _size) return;
        T* newArr = new T[_capacity];
        int j = 0;
        for (int i = 0; i < _size; i++) {
            if (i < index || i >= index + count) {
                newArr[j++] = _array[i];
            }
        }
        delete[] _array;
        _array = newArr;
        _size -= count;
    }

    void print() const {
        for (int i = 0; i < _size; i++) {
            cout << _array[i] << " ";
        }
        cout << endl;
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            T* newArr = new T[other._capacity];
            for (int i = 0; i < other._size; i++) {
                newArr[i] = other._array[i];
            }
            delete[] _array;
            _array = newArr;
            _size = other._size;
            _capacity = other._capacity;
            _grow = other._grow;
        }
        return *this;
    }

};
