#pragma once
#include "ListNode.h"

template <typename NODETYPE>
class Queue
{
private:
	ListNode<NODETYPE> *_head;
	ListNode<NODETYPE> *getNewNode(const NODETYPE &value) { return new ListNode<NODETYPE>(value); }
public:
	Queue();
	bool isEmpty() const { return _head == 0; }
	void enqueue(const NODETYPE &);
	NODETYPE dequeue();
	NODETYPE head();
	~Queue();
};

template <typename NODETYPE>
Queue<NODETYPE>::Queue()
	: _head(0)
{
}

template <typename NODETYPE>
Queue<NODETYPE>::~Queue()
{
	if (!isEmpty()) {
		ListNode<NODETYPE> *current = _head;
		ListNode<NODETYPE> *temp;

		while (current != 0) {
			temp = current;
			current = current->_next;
			delete temp;
		}
	}
}

template <typename NODETYPE>
void Queue<NODETYPE>::enqueue(const NODETYPE &value)
{
	ListNode<NODETYPE> * newNode = getNewNode(value);

	if (isEmpty()) _head = newNode;
	else {
		newNode->_next = _head;
		_head = newNode;
	}
}

template <typename NODETYPE>
NODETYPE Queue<NODETYPE>::dequeue()
{
	if (isEmpty()) return NULL;
	else {
		NODETYPE value;
		ListNode<NODETYPE> * temp = _head;

		if (temp->_next == 0) {
			value = _head->_data;
			_head = 0;
		}
		else {
			ListNode<NODETYPE> * prev = 0;
			while (temp->_next != 0) {
				prev = temp;
				temp = temp->_next;
			}
			value = temp->_data;
			prev->_next = 0;
		}
		delete temp;
		return value;
	}
}

template <typename NODETYPE>
NODETYPE Queue<NODETYPE>::head()
{
	if (isEmpty()) return NULL;
	ListNode<NODETYPE> * temp = _head;
	while (temp->_next != NULL) temp = temp->_next;
	return temp->_data;
}

