#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include "Node.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

//////////////////////////////////////////////////////////////////////////////
//                         class template definition                        //
//////////////////////////////////////////////////////////////////////////////

template<typename T>
class DoublyLinkedList {
public:
    /* uncomment the declarations as you implement them */
    DoublyLinkedList();
    DoublyLinkedList(T val);
    DoublyLinkedList(const DoublyLinkedList<T>&);
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>&);
    ~DoublyLinkedList();
    unsigned int size() const { return sz; }
    T& front();
    const T& front() const {return head -> data;}
    T& back(){return tail -> data;}
    const T& back() const {return tail -> data;}
    void push_back(T data) 
    {
      Node<T> *node = new Node<T>(data);
      if(tail == nullptr)
      {
        node -> next = nullptr;
        node -> prev = nullptr;
        head = node;
        tail = node;
      }
      else
      {
        node -> next = nullptr;
        node -> prev = tail;
        tail -> next = node;
        tail = node;
      }
      sz++;

    }
    void push_front(T data)
    {
      Node<T>* node = new Node<T>(data);
      if(head == nullptr)
      {
        node -> next = nullptr;
        node -> prev = nullptr;
        head = node;
        tail = node;
      }
      else
      {
        node -> next = head;
        node -> prev = nullptr;
        head -> prev = node;
        head = node;
      }
      sz++;
    }
    void pop_back();
    void pop_front();
    void erase(unsigned int);
    void insert(T data, unsigned int idx);
    void clear();
    std::string to_str() const;
    // breaks encapsulation... gives operator== access to private data... not great approach, but makes the homework easier for you since we haven't talked about iterators :).
    // template<typename U> friend bool operator==(DoublyLinkedList<U> const&, DoublyLinkedList<U> const&);
private:
    // do not change ordering.
    Node<T> *head;
    Node<T> *tail;
    unsigned int sz;
};

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), sz(0){}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(T data)
{
  head = nullptr;
  tail = nullptr;
  sz = 0;
  Node<T>* node = new Node<T>(data);
  head = node;
  tail = node;
  sz++;
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T> &list)
{
  head = nullptr;
  tail = nullptr;
  sz = 0;
  Node<T> *node = list.head;
  while(node != nullptr)
  {
    this -> push_back(node -> data);
    node = node -> next;
  }
}

template<typename T>
T& DoublyLinkedList<T>:: front()
{
  return this -> head -> data;
}

template<typename T>
void DoublyLinkedList<T>::pop_back()
{
  if(sz == 1)
  {
    delete tail;
    tail = nullptr;
    head = nullptr;
    sz--;
  }
  else if(sz == 0)
  {
    return;
  }
  else
  {
    Node<T> *node = tail -> prev;
    delete tail;
    tail = node;
    tail -> next = nullptr;
    sz--;
  }
  
}

template<typename T>
void DoublyLinkedList<T>::pop_front()
{
  if(sz == 1)
  {
    delete head;
    head = nullptr;
    tail = nullptr;
    sz--;
  }
  else if(sz == 0)
  {
    return;
  }
  else
  {
    Node<T> *node = head -> next;
    delete head;
    head = node;
    head -> prev = nullptr;
    sz--;
  }
}

template<typename T>
void DoublyLinkedList<T>::erase(unsigned int index)
{
  if (sz == 0) 
  {
		return;
	}
  else if (sz == 1) 
  {
		delete head;
		head = nullptr;
		tail = nullptr;
		sz--;
	}
  else 
  {
		
		Node<T>* moving = head;
		unsigned int i = 0;
		for (i = 0; i <index; i++) 
    {
			moving = moving->next;
		}
		if (moving == tail) 
    {
			Node<T>* before = tail->prev;
			delete tail;
			tail = before;
			tail->next = nullptr;
			sz--;
		}
    else if (moving == head) 
    {
			Node<T>* after = head->next;
			delete head;
			head = after;
			head->prev = nullptr;
			sz--;
		}
    else 
    {
			Node<T>* before = moving->prev;
			Node<T>* after = moving->next;
			delete moving;
			sz--;
			before->next = after;
			after->prev = before;
		}
	}
  
}

template<typename T>
void DoublyLinkedList<T>::insert(T data, unsigned int idx)
{
  if(idx >= sz)
    return;
  if(idx == 0)
  {
    Node<T> *node = new Node<T>(data);
    head -> prev = node;
    node -> next = head;
    node -> prev = nullptr;
    head = node;
    sz++;
  }
  else
  {
    Node<T> *node = new Node<T>(data);
    Node<T> *start = head;
    for(int x = 0; x < idx; x++)
    {
      start = start -> next;
    }
    //start is the left node
    Node<T> *before = start -> prev;
    node -> next = start;
    start -> prev = node;
    node -> prev = before;
    before -> next = node;
    sz++;
  } 
}

template<typename T>
void DoublyLinkedList<T>::clear()
{
  Node<T> *node = head;
  while(node != nullptr)
  {
    Node<T> *after = node -> next;
    delete node;
    node = after;
  }
  delete node;
  head = nullptr;
  tail = nullptr;
  sz = 0;

}
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////
//                       helper function declarations                       //
//////////////////////////////////////////////////////////////////////////////
template<typename T> std::ostream& operator<<(std::ostream &, DoublyLinkedList<T> const&);

template<typename T> bool operator==(DoublyLinkedList<T> const&, DoublyLinkedList<T> const&);

template<typename T> bool operator!=(DoublyLinkedList<T> const&, DoublyLinkedList<T> const&);

//////////////////////////////////////////////////////////////////////////////
//                     member template function definitions                 //
//////////////////////////////////////////////////////////////////////////////
template<typename T>
std::string DoublyLinkedList<T>::to_str() const
{
    std::stringstream os;
    const Node<T> *curr = head;
    os << std::endl << std::setfill('-') << std::setw(80) << '-' << std::setfill(' ') << std::endl;
    os << "head: " << head << std::endl;
    os << "tail: " << tail << std::endl;
    os << "  sz: " << sz << std::endl;
    os << std::setw(16) << "node" << std::setw(16) << "node.prev" << std::setw(16) << "node.data" <<  std::setw(16) << "node.next" << std::endl;
    while (curr) {
        os << std::setw(16) << curr;
        os << std::setw(16) << curr->prev;
        os << std::setw(16) << curr->data;
        os << std::setw(16) << curr->next;
        os << std::endl;
        curr = curr->next;
    }
    os << std::setfill('-') << std::setw(80) << '-' << std::setfill(' ') << std::endl;
    return os.str();
}

//////////////////////////////////////////////////////////////////////////////
//                     helper template function definitions                 //
//////////////////////////////////////////////////////////////////////////////
template<typename T>
bool operator==(DoublyLinkedList<T> const& lhs, DoublyLinkedList<T> const& rhs)
{
    // getting you started on this once... definition for this overloaded operator will go here.
    if (lhs.size() == rhs.size()) 
    {
		  return true;
	  }
    else 
    {
		  return false;
	  }
 
}
template<typename T>
bool operator!=(const DoublyLinkedList<T> &lhs, const DoublyLinkedList<T> &rhs)
{
  if (lhs.size() != rhs.size()) 
    {
		  return true;
	  }
    else 
    {
		  return false;
	  }
  
}
template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& val)
{
  if(this != &val)
  {
    clear();
    if(val.head == nullptr)
    {
      head = nullptr;
      tail = nullptr;
      sz = 0;
    }
    else
    {
      Node<T> *node = val.head;
      while(node != nullptr)
      {
        this -> push_back(node -> data);
        node = node -> next;
      }
    }
  }
  return *this;
  
}

template<typename T>
std::ostream& operator<<(std::ostream& os, DoublyLinkedList<T> const& rhs)
{
    os << rhs.to_str();
    return os;
}

#endif