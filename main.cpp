#include <iostream>
#include <vector>

template<class Type>
class Node
{
private:
    Type data;
public:
    Node(Type data) : data(data) {}
    Type &getData() { return data; }
    Node<Type> *ptr_next = nullptr;
};

template<class Type>
class List
{
private:
    Node<Type> *ptr_first = nullptr;
public:
    void push_back(Type data);//добавление элемента в конец списка
    void push_front(Type data);//добавление в начало
    void insert(int index, Type data);//вставка в произвольное место
    int size_list();//вывод общего числа элементов
    void out_all();//вывод всех элементов
    void delet(int index);//удаление элемента по индексу
    void delet_front();//удаление первого элемента
    void delet_back();//удаление последнего элемента
    std::vector<int> search(Type data);//поиск элемента по занчению

    Type &operator[](int index);//Перегруженный оператор для объекта

    ~List();
};

template<class Type>
void List<Type>::push_back(Type data)
{
    if(ptr_first == nullptr)
    {
        ptr_first = new Node<Type>(data);

        return;
    }

    Node<Type> *ptr_first_cope = ptr_first;//получаем копию указателя на первый элемент, чтобы не изменить его

    while(ptr_first_cope->ptr_next)//проходимся по списку
    {
        ptr_first_cope = ptr_first_cope->ptr_next; 
    }

    ptr_first_cope->ptr_next = new Node<Type>(data);

}

template<class Type>
void List<Type>::out_all()
{
    if(ptr_first == nullptr)
    {
        std::cout << "Элементов нет!\n";

        return;
    }

    Node<Type> *ptr_first_cope = ptr_first;

    while(ptr_first_cope->ptr_next)
    {
        std::cout << ptr_first_cope->getData() << " ";

        ptr_first_cope = ptr_first_cope->ptr_next;
    }

    std::cout << ptr_first_cope->getData() << " ";
    std::cout << std::endl;
}

template<class Type>
void List<Type>::delet(int index)
{
    if(ptr_first == nullptr)
    {
        std::cout << "Элементов нет!\n";
        return;
    }

    Node<Type> *ptr_first_cope = ptr_first;
    Node<Type> *ptr_prev = nullptr;

    if(index == 0)//удаление первого элемента
    {
        ptr_first = ptr_first->ptr_next;
        delete ptr_first_cope;
        return;
    }

    for (int i = 0; i < index; ++i)
    {
        if(ptr_first_cope->ptr_next == nullptr)
        {
            std::cout << "Вы вышли за границы списка!\n";
            return;
        }
        ptr_prev = ptr_first_cope;
        ptr_first_cope = ptr_first_cope->ptr_next;
    }

    if(ptr_first_cope->ptr_next == nullptr)//удаление последнего элемента
    {
        delete ptr_first_cope;
        ptr_prev->ptr_next = nullptr;
        return;
    }

    ptr_prev->ptr_next = ptr_first_cope->ptr_next;
    ptr_first_cope->ptr_next = nullptr;
    delete ptr_first_cope;

}

template<class Type>
void List<Type>::push_front(Type data)
{
    Node<Type> *ptr_first_cope = new Node<Type>(data);
    ptr_first_cope->ptr_next = ptr_first;
    ptr_first = ptr_first_cope;
    ptr_first_cope = nullptr;
}

template<class Type>
void List<Type>::delet_front()
{
    if(ptr_first == nullptr)
    {
        std::cout << "Элементов нет!\n";
        return;
    }

    Node<Type> *ptr_first_cope = ptr_first;
    ptr_first = ptr_first->ptr_next;
    ptr_first_cope->ptr_next = nullptr;
    delete ptr_first_cope;
}

template<class Type>
void List<Type>::delet_back()
{
    if(ptr_first == nullptr)
    {
        std::cout << "Элементов нет!\n";
        return;
    }

    if(ptr_first->ptr_next == nullptr)
    {
        delet_front();
        return;
    }

    Node<Type> *ptr_first_cope = ptr_first;
    Node<Type> *ptr_prev = nullptr;

    while(ptr_first_cope->ptr_next)
    {
        ptr_prev = ptr_first_cope;
        ptr_first_cope = ptr_first_cope->ptr_next;
    }

    ptr_prev->ptr_next = nullptr;
    delete ptr_first_cope;
}

template<class Type>
int List<Type>::size_list()
{
    int size = 0;
    if(ptr_first == nullptr)
    {
        return size;
    }

    ++size;

    Node<Type> *ptr_first_cope = ptr_first;

    while(ptr_first_cope->ptr_next)
    {
        ++size;
        ptr_first_cope = ptr_first_cope->ptr_next;
    }

    return size;
}

template<class Type>
Type &List<Type>::operator[](int index)
{
    if(ptr_first == nullptr || index < 0)
    {
        throw std::out_of_range("Вы вышли за границы списка!");
    }

    Node<Type> *ptr_first_cope = ptr_first;

    for (int i = 0; i < index; ++i)
    {
        if(ptr_first_cope->ptr_next == nullptr)
        {
            throw std::out_of_range("Вы вышли за границы списка!");
        }
        ptr_first_cope = ptr_first_cope->ptr_next;
    }

    return ptr_first_cope->getData();
}

template<class Type>
void List<Type>::insert(int index, Type data)//добавляем значение data непосредственно перед элементом заданным индексом index
{
    if(ptr_first == nullptr)
    {
        std::cout << "Список пуст\n";
    }
    if(index < 0)
    {
        std::cout << "Вы вышли за границу списка\n";
        return;
    }

    Node<Type> *ptr_first_copy = ptr_first;
    Node<Type> *ptr_prev = nullptr;

    if(index == 0) 
    {
        push_front(data);
        return;
    }
    
    for(int i = 0; i < index; ++i)
    {
        if(ptr_first_copy->ptr_next == nullptr)
        {
            std::cout << "Вы вышли за границы списка\n";
            return;
        }

        ptr_prev = ptr_first_copy;
        ptr_first_copy = ptr_first_copy->ptr_next;
    }

    Node<Type> *ptr_prev_copy = new Node<Type>(data);
    ptr_prev->ptr_next = ptr_prev_copy;
    ptr_prev_copy->ptr_next = ptr_first_copy;
}

template<class Type>
List<Type>::~List()
{
    Node<Type> *ptr_first_copy = ptr_first;

    while (ptr_first_copy)
    {
        ptr_first = ptr_first->ptr_next;
        ptr_first_copy->ptr_next = nullptr;
        delete ptr_first_copy;
        ptr_first_copy = ptr_first;
    }
    
}

template<class Type>
std::vector<int> List<Type>::search(Type data)
{
    std::vector<int> indexes;
    Node<Type> *ptr_first_copy = ptr_first;
    int index = 0;

    if(ptr_first == nullptr)
    {
        std::cout << "Список пуст\n";
        return indexes;
    }

    while(ptr_first_copy)
    {
        if(ptr_first_copy->getData() == data) indexes.push_back(index);
        
        ptr_first_copy = ptr_first_copy->ptr_next;
        ++index;
    }

    return indexes;
}



int main() 
{
    List<int> list;
    try {
        list.push_back(87);
        list.push_back(82);
        list.push_back(1);
        list.push_back(855);
        list.push_back(89);

        list.out_all();

    } catch (const std::out_of_range& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
