#ifndef      __FISTACK__HPP__
#define     __FISTACK__HPP__
#include "../contains/contains.h"

template<typename T>
class FIStack
{
public:
    FIStack();
    ~FIStack();

    void        pushData(T data);
    T           popData();
    unsigned    getSize() { return _size; }

private:
    typedef struct node{
        node    *previous;
        node    *next;
        T       data;
    } Node;

    Node        *_bottom;
    Node        *_top;
    Node        *_next;
    unsigned    _size;
};

template<typename T>
FIStack<T>::FIStack()
{
    _bottom = new Node;
    _top = new Node;
    _next = new Node;

    _bottom->previous = nullptr;
    _bottom->data = 0;
    _bottom->next = _top;

    _size = 0;

    _top->previous = _bottom;
    _top->data = 0;
    _top->next = nullptr;
}

template<typename T>
FIStack<T>::~FIStack()
{
    _bottom->previous = nullptr;
    _bottom->data = 0;
    _bottom->next = _top;

    _size = 0;

    _top->previous = _bottom;
    _top->data = 0;
    _top->next = nullptr;

}

template<typename T>
void FIStack<T>::pushData( T data )
{
    _top->data = data;
    
    _next = _top;

    _top = new Node;
    _top->previous = _next;
    _top->data = 0;
    _top->next = nullptr;

    _next->next = _top;

    ++_size;
}

template<typename T>
T FIStack<T>::popData()
{
    if( _size <= 0 )
    {
        cout << "Its empty." << endl;
        return 0;
    }
    //_top is empty all the time.
    delete _top;
    
    _top = _next;
    _next = _top->previous;

    --_size;

    return _top->data;
}

#endif      //__FISTACK__HPP__
