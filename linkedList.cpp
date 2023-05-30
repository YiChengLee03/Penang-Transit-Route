// template<class T> struct node {
//     T element;
//     T* next;
// };

// template<class T> class linkedList {
// public: 
//     linkedList();
//     linkedList(node* head);
//     bool isEmpty();
//     void push_back(node* other);
// private:
//     node* head;
// };

// template<class T> linkedList<T>::linkedList() : head(nullptr) {}

// template<class T> linkedList<T>::linkedList(node* head) : head(head) {}


template<class T> class linkedList {
private:
    struct node {
        T value;
        T* next;
    };
    node* head;
    node* tail;
public: 
    linkedList();
    bool isEmpty();
    void push_back();
};

// remove
// pushback
// front