#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <stdexcept> 
#include <initializer_list>
#include <cstddef>
template <typename T>
class ForwardList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& data) : data(data), next(nullptr) {}
    };
    Node* head;

public:
    ForwardList() : head(nullptr) {}
    ForwardList(std::initializer_list<T> init_list);
    ~ForwardList();

    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();
    const T& front() const;
    const T& back() const;
    std::size_t size() const;
    bool empty() const;
    void clear();
    T& operator[](int index);
};

template<typename T>
ForwardList<T>::ForwardList(std::initializer_list<T> init_list):head(nullptr){
    for(const T& value : init_list){
        push_back(value);
    }
}

template <typename T>
ForwardList<T>::~ForwardList() {
    clear();
}

template <typename T>
void ForwardList<T>::push_front(const T& value) {
    Node* new_node = new Node(value);
    new_node->next = head;
    head = new_node;
}

template <typename T>
void ForwardList<T>::push_back(const T& value) {
    Node* new_node = new Node(value);
    if (head == nullptr) {
        head = new_node;
    } else {
        Node* it = head;
        while (it->next != nullptr) {
            it = it->next;
        }
        it->next = new_node;
    }
}

template <typename T>
void ForwardList<T>::pop_front() {
    if (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

template <typename T>
void ForwardList<T>::pop_back(){
    if(!head) throw std::out_of_range("List is empty");

    if(!head->next){
        delete head;
        head=nullptr;
        return;
    }

    Node* temp=head;
    while(temp->next->next){
        temp=temp->next;
    }

    delete temp->next;
    temp->next=nullptr;
}

template <typename T>
const T& ForwardList<T>::front() const{
    if(!head){
        throw std::out_of_range("List is empty");
    }

    return head->data;
}

template <typename T>
bool ForwardList<T>::empty() const {
    return head == nullptr;
}

template <typename T>
void ForwardList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template <typename T>
const T& ForwardList<T>::back() const {
    if(!head) throw std::out_of_range("List is empty");

    Node* temp=head;

    while(temp->next){ 
        temp=temp->next;
    }

    return temp->data;
}

template<typename T>
std::size_t ForwardList<T>::size() const{
    size_t size=0;
    Node* temp=head;
    while(temp){
        size++;
        temp=temp->next;
    }
    return size;
}

template<typename T>
T& ForwardList<T>::operator[](int index){
    if(index<0) throw std::out_of_range("Index is out of range");

    Node* temp=head;
    for(int i=0; i<index ; ++i){
        if(!temp){
            throw std::out_of_range("Index is out of range");
        }
        temp=temp->next;
    }

    if(!temp) throw std::out_of_range("Index is out of range");

    return temp->data;

}

#endif // FORWARD_LIST_H
