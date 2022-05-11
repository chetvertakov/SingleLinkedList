# SingleLinkedList

Реализован аналог шаблонного класса Односвязный список (forward_list) из стандартной библиотеки. Данные хранятся в нодах, создаваемых в динамической памяти (в куче). Каждая нода хранит значение и указатель на следующую ноду в списке.

Для списка реализован собственный итератор типа forward_iterator. Для итераторов реализованы операторы сравнения, оператор разыменования **\*** и доступа **->**. Реализован оператор инкремента **++**. 


## Функционал класса
### Создание списка
* конструктор по-умолчанию, создающий пустой список
```c++
SingleLinkedList<int> list;
``` 
* конструктор из списка инициализации
```c++
SingleLinkedList<int> list{1, 2, 3, 4, 5};
``` 
* копирующий конструктор
```c++
SingleLinkedList<int> non_empty_list{1, 2, 3, 4};
auto list_copy(non_empty_list);
``` 
* оператор копирующего присваивания
```c++
const SingleLinkedList<int> source_list{1, 2, 3, 4};
SingleLinkedList<int> receiver = source_list;
```  
### Методы
* возврат константных/неконстантных итераторов на начало и конец списка, возможно использование в for-range циклах
```c++
SingleLinkedList<int> non_empty_list{1, 2, 3, 4};
for (auto elem : non_empty_list) {
    std::cout << elem << " ";
}
``` 
* обмен данными двух списков
```c++
SingleLinkedList<int> non_empty_list1{1, 2, 3, 4};
SingleLinkedList<int> non_empty_list2{12, 13, 14, 15, 16};
non_empty_list1.swap(non_empty_list2);
for (auto elem : non_empty_list1) {
    std::cout << elem << " ";
}
``` 
* возврат информации о состоянии списка : текущий размер/проверка на пустоту
```c++
SingleLinkedList<int> non_empty_list{1, 2, 3, 4};
std::cout << non_empty_list.GetSize() << std::endl;
std::cout << std::boolalpha << non_empty_list.IsEmpty() << std::endl;
``` 
* добавление/удаление элемента в начало списка
```c++
SingleLinkedList<int> list;
list.PushFront(5).PushFront(13).PushFront(44).PushFront(0);
list.PopFront();
for (auto elem : list) {
    std::cout << elem << " ";
}
``` 
* добавление/удаление элемента в произвольное место в списке (по итератору)
```c++
SingleLinkedList<int> list;
list.InsertAfter(list.cbefore_begin(), 1);
list.InsertAfter(list.cbefore_begin(), 2);
list.InsertAfter(list.cbefore_begin(), 3);
list.InsertAfter(list.cbefore_begin(), 4);
list.EraseAfter(list.cbegin());
for (auto elem : list) {
    std::cout << elem << " ";
}
``` 
* операторы сравнения для двух списков (лексикографически, поэлементно)
```c++
SingleLinkedList<int> list1 = {1, 2, 3, 4, 5};
SingleLinkedList<int> list2 = {1, 2, 3, 4, 6};
std::cout << std::boolalpha << (list2 > list1);
``` 
## Установка и использование
Просто скопируйте файл singlelinkedlist.h в папку с вашим проектом и подключите через директиву *#include<singlelinkedlist.h>*
Класс списка и вспомогательные функции находятся в неймспейсе List.

## Тесты
Тесты находятся в файле test.cpp. При желании можно собрать тестовую программу с использованием приложенного CMakeLists.txt

## Системные требования
Компилятор С++ с поддержкой стандарта C++17 или новее

