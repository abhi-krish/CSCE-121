#ifndef NODE_H
#define NODE_H

//////////////////////////////////////////////////////////////////////////////
//                         class template definition                        //
//////////////////////////////////////////////////////////////////////////////
template<typename T>
struct Node {
    Node(T data): data(data), next(nullptr), prev(nullptr){} // need to define this
    T data;
    Node* next;
    Node* prev;
};

//////////////////////////////////////////////////////////////////////////////
//                       helper function declarations                       //
//////////////////////////////////////////////////////////////////////////////

template <typename T>
bool operator==(const Node<T> &rhs, const Node<T> &lhs);
template <typename T>
bool operator!=(const Node<T> &rhs, const Node<T> &lhs);
template <typename T>
bool operator<(const Node<T> &rhs, const Node<T> &lhs);
template <typename T>
bool operator<=(const Node<T> &rhs, const Node<T> &lhs);
template <typename T>
bool operator>(const Node<T> &rhs, const Node<T> &lhs);
template <typename T>
bool operator>=(const Node<T> &rhs, const Node<T> &lhs);
template<typename T> 

/////////////////////////////////////////


bool operator==(const Node<T>& rhs, const Node<T>& lhs)
{
  if(lhs -> data == rhs -> data)
    return true;
  return false;
}
template<typename T> 
bool operator!=(const Node<T>& rhs, const Node<T>& lhs)
{
  if(lhs -> data != rhs -> data)
    return true;
  return false;
}
template<typename T> 
bool operator<(const Node<T>& rhs, const Node<T>& lhs)
{
  if(lhs -> data < rhs -> data)
    return true;
  return false;
}
template<typename T>
bool operator<=(const Node<T>& rhs, const Node<T>& lhs)
{
  if(lhs -> data <= rhs -> data)
    return true;
  return false;
}
template<typename T> 
bool operator>(const Node<T>& rhs, const Node<T>& lhs)
{
  if(lhs -> data > rhs -> data)
    return true;
  return false;
}
template<typename T> 
bool operator>=(const Node<T>& rhs, const Node<T>& lhs)
{
  if(lhs -> data >= rhs -> data)
    return true;
  return false;
}
template<typename T>
std::ostream& operator<<(std::ostream& os, const Node<T> &rhs)
{
    os << rhs -> data <<  std::endl;
    return os;
}
//////////////////////////////////////////////////////////////////////////////
//                     member template function definitions                 //
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//                     helper template function definitions                 //
//////////////////////////////////////////////////////////////////////////////

#endif
