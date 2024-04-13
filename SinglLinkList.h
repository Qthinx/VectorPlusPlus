#pragma once
class SinglLinkList
{
public:
	SinglLinkList() = default;
	SinglLinkList(SinglLinkList& right);
	SinglLinkList(SinglLinkList&& right);
	void push_front(size_t val);
	void pop_front();
	void print();
	void copy(SinglLinkList& right);
	void move(SinglLinkList&& right);
private:
	struct Node
	{
		size_t data;
		Node* next = nullptr;
	};

	Node* head = nullptr;
	size_t size = 0;
	Node* end = nullptr;
};

