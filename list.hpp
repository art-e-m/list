#ifndef list_hpp
#define list_hpp

#include <iostream>

using namespace std;

template<typename T>
struct elem{
    elem* next;
    elem* prev;
    T data;
    elem(T d): next(0), prev(0), data(d){}
};

template<typename T>
class list{
    elem<T> * head;
    elem<T> * last;
    int size;
public:
    list();
    ~list();
    
    T & operator[](const int number);
    void pushBack(const T& data);
    void delBack();
    void pushFront(const T& data);
    void delFront();
    void insert(int idx, const T& data);
    void del(int idx);
    void clearList();
    int getSize(){return size;}
    void cpyList(const list& l);
    void showList();
};

//-------------------------------------------------------------------------

template<typename T>
list<T>::list(){
    head = nullptr;
    last = nullptr;
    size = 0;
}

template<typename T>
list<T>::~list(){
    for (elem<T> * i = head; i != 0;){
        elem<T>* tmp = i;
        i = i->next;
        delete tmp;
    }
}

template<typename T>
void list<T>::pushBack(const T& data){
    elem<T> * e = new elem<T>(data);
    if (head == nullptr){
        head = e;
        head->prev = nullptr;
    } else {
        last->next = e;
        e->prev = last;
    }
    last = e;
    last->next = nullptr;
    e->data = data;
    size++;
}

template<typename T>
void list<T>::delBack(){
    if (head == nullptr) return;
    last = last->prev;
    delete last->next;
    last->next = nullptr;
    size--;
}

template<typename T>
void list<T>::pushFront(const T& data){
    elem<T> * e = new elem<T>(data);
    if (head == nullptr){
        head = e;
        head->prev = nullptr;
    } else {
        e->next = head;
        head = e;
        size++;
    }
    e->data = data;
    size++;
}

template<typename T>
void list<T>::delFront(){
    if (head == nullptr) return;
    head = head->next;
    delete head->prev;
    head->prev = nullptr;
    size--;
}

template<typename T>
void list<T>::showList(){
    for (elem<T> * i = head; i != 0; i = i->next){
        cout << i->data << " ";
    }
    cout << endl;
}

template<typename T>
void list<T>::del(int idx){
    if(idx >= size || idx < 0) return;
    if(idx == size-1){
        delBack();
        return;
    }
    if(idx == 0){
        delFront();
        return;
    }

    int cnt = 0;
    for (elem<T> * i = head; i != 0; i = i->next){
        if (cnt == idx){
            i->prev->next = i->next;
            delete i;
            size--;
            break;
        }
        cnt++;
    }
}

template<typename T>
void list<T>::insert(int idx, const T& data){
    if(idx >= size || idx < 0) return;
    if(idx == size-1){
        pushBack(data);
        return;
    }
    if(idx == 0){
        pushFront(data);
        return;
    }

    int cnt = 0;
    for (elem<T> * i = head; i != 0; i = i->next){
        if (cnt == idx){
            elem<T> * e = new elem<T>(data);
            e->data = data;
            i->prev->next = e;
            e->next = i;
            size++;
            break;
        }
        cnt++;
    }
}

template<typename T>
T & list<T>::operator[](const int number){
    int cnt = 0;
        for (elem<T>* i = head; i != 0; i = i->next){
            if (number == cnt){
                return i->data;
            }
            cnt++;
        }
    throw "error: double & list::operator[](const int number)";
}

template<typename T>
void list<T>::clearList(){
    if (head == nullptr) return;
    for(elem<T>* i = head; i != 0; i = i->next){
        delete i;
        size--;
    }
    head = nullptr;
    last = nullptr;
}

template<typename T>
void list<T>::cpyList(const list& l){
    if (l.head == head){
        return;
    }
    for(elem<T>* i = l.head; i != 0; i = i->next){
        pushBack(i->data);
    }
}

#endif /* list_hpp */
