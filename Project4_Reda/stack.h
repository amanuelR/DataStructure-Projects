#ifndef STACK_H_
#define STACK_H_

#include"list.h"

// Stack ADT using linked list as primary data structure.
// 
template<typename Type>
class Stack {
public:

	Stack();

	// Basic stack operations
	void	push(Type item);
	void	pop();
	Type	peek() const;

	// Check to see if there is anything on the stack
	bool	empty() const;

	// Use to see what is in the stack for debugging
	void	print() const;

#ifndef MAKE_MEMBERS_PUBLIC
private:
#endif

	List<Type> m_list;
};

// Stack Implementation
//

// Stack() Default constrcutor:
//		Call the defualt constructor for its List.
//		Already implemented.
template<typename Type>
Stack<Type>::Stack() :m_list() {}

// push():
//		Add item to the stack in a manor appropriate for
//		Stack behavoir.
//
template<typename Type>
void Stack<Type>::push(Type item) {

	m_list.push_back(item);

}

// pop():
//		Remove the item on the "top" of the stack.
//
template<typename Type>
void Stack<Type>::pop() {

	m_list.pop_rear();

}

// isEmpty():
//		return true if there are no items in the stack
//		otherwise return false.
//
template<typename Type>
bool Stack<Type>::empty() const {

	if(m_list.empty())
		return true;

	return false;
}

// peek():
//		Look at the "top" of the stack without changing the
//		Stack itself.
//
template<typename Type>
Type Stack<Type>::peek() const {

	/* TODO */

	Type item = m_list.rear();

	return item;
}

// printStack()
//		Print to console the elements.
//		Used for debugging.
//
template<typename Type>
void Stack<Type>::print() const {

	m_list.print();

}
#endif//STACK_H_