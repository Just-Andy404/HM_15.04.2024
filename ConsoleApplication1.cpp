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
#include <iostream>
#include "Array.h"

int main() {
    Array<int> list(5);
    list.add(10);
    list.add(15);
    list.add(20);
    list.add(25);
    list.add(30);
    list.print();

    list[0] = 999;
    list.print();

    cout << "Size: " << list.getSize() << endl;
    list.setSize(10, 5);
    list.print();

    cout << "Last item index: " << list.getUpperBound() << endl;
    cout << (list.isEmpty() ? "List is empty" : "List is not empty") << endl;

    list.add(598);
    cout << (list.isEmpty() ? "List is empty" : "List is not empty") << endl;
    cout << "Size: " << list.getSize() << endl;

    list.freeExtra();
    cout << "Size after freeExtra: " << list.getSize() << endl;
    list.print();

    cout << "Element at index 2: " << list.getAt(2) << endl;
    list.setAt(666, 2);
    list.print();

    Array<int> list2(2);
    list2.add(77);
    list2.add(4321);
    list2.print();

    list2.removeAt(0);
    list2.print();

    int arr[] = { 5, 6, 7 };
    list2.insertAt(arr, 3, 0);
    list2.print();

    list.append(list2);
    list.print();

    Array<int> list3;
    list3 = list2;
    list3.add(777777);
    list3.print();

    return 0;
}
