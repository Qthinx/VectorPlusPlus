#include "SinglLinkList.h"
#include <iostream>

SinglLinkList::SinglLinkList(SinglLinkList& right)
{
	printf("d");
}

SinglLinkList::SinglLinkList(SinglLinkList&& right)
{
	printf("d");
}

void SinglLinkList::push_front(size_t val)
{
	if (head == nullptr) 
	{
		head = new Node{ val, nullptr };
	}
	else if(head->next == nullptr)
	{
		head = new Node{ val, head };
	}
	else
	{
		head = new Node{ val, head };
	}
}

void SinglLinkList::pop_front()
{
	if (head == nullptr){}
	else
	{
		Node* tmp = head->next;
		
		if (head->next == nullptr){ delete head; }
		else
		{
			delete head;
			head = tmp;
		}
	}
}

void SinglLinkList::print()
{
	Node* current = head;
	while (current != nullptr)
	{
		std::cout << current->data << " ";
		current = current->next;
	}
	std::cout << "\n";
}

void SinglLinkList::copy(SinglLinkList& right)
{
	Node* current = head;
	while (current == nullptr)
	{
		// current->data = right->data;
	}
}

void SinglLinkList::move(SinglLinkList&& right)
{
	Node* current = head;
	while (current == nullptr)
	{
		// current->data = std::move(right->data);
	}
}
