#pragma once
#include <stddef.h>

template <typename> class Queue;
template <typename> class Stack;

template <typename NODETYPE>
class ListNode
{
	friend class Queue<NODETYPE>;
	friend class Stack<NODETYPE>;
private:
	NODETYPE _data;
	ListNode<NODETYPE> *_next;
public:
	ListNode(const NODETYPE &data);
	NODETYPE getData() const;
};

template <typename NODETYPE>
ListNode<NODETYPE>::ListNode(const NODETYPE &data)
	: _data(data), _next(0)
{

}

template <typename NODETYPE>
NODETYPE ListNode<NODETYPE>::getData() const
{
	return _data;
}


