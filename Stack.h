#pragma once
#include "ListNode.h"

template <typename NODETYPE>
class Stack
{
private:
	char _count;
	ListNode<NODETYPE> *_top;
	ListNode<NODETYPE> *getNewNode(const NODETYPE &value) { return new ListNode<NODETYPE>(value); }
public:
	Stack();
	bool isEmpty() const { return _top == 0; }
	void push(const NODETYPE &);
	NODETYPE pop();
	const char Length() { return _count; }
	~Stack();
};

template <typename NODETYPE>
Stack<NODETYPE>::Stack()
	: _top(0), _count(0)
{
}

template <typename NODETYPE>
Stack<NODETYPE>::~Stack()
{
	if (!isEmpty()) {
		ListNode<NODETYPE> *current = _top;
		ListNode<NODETYPE> *temp;

		while (current != 0) {
			temp = current;
			current = current->_next;
			delete temp;
		}
	}
}

template <typename NODETYPE>
void Stack<NODETYPE>::push(const NODETYPE &value)
{
	ListNode<NODETYPE> * newNode = getNewNode(value);

	if (isEmpty()) _top = newNode;
	else {
		newNode->_next = _top;
		_top = newNode;
	}
	++_count;
}

template <typename NODETYPE>
NODETYPE Stack<NODETYPE>::pop()
{
	--_count;
	if (isEmpty()) return NULL;
	else {
		ListNode<NODETYPE> * temp = _top;
		NODETYPE value = temp->_data;

		_top = _top->_next;

		delete temp;
		return value;
	}
}

