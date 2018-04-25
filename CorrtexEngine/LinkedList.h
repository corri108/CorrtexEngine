#pragma once

//custom LinkedList class. made for fun
template<typename T>
struct Node
{
	T data;
	Node<T>* next;
};

template<class T>
class LinkedList
{
public:
	LinkedList();
	~LinkedList();
	void Add(T d);
	void Display();
	void Insert_First(T d);
	void Insert(int pos, T d);
	void DeleteFirst();
	void DeleteLast();
	void DeletePosition(int pos);
	void BubbleSort();
	int Count();
	T Get(int i);
private:
	Node<T>* head;
	Node<T>* tail;
};

//ctor / dtor
template<class T>
LinkedList<T>::LinkedList()
{
	head = NULL;
	tail = NULL;
}

template<class T>
LinkedList<T>::~LinkedList()
{

}

//adding / inserting
template<class T>
void LinkedList<T>::Add(T d)
{
	Node<T> *newNode = new Node<T>;
	newNode->data = d;
	newNode->next = NULL;

	if (this->head == NULL)//its the first element added
	{
		this->head = newNode;
		this->tail = newNode;
	}
	else//append to end of the list
	{
		this->tail->next = newNode;
		this->tail = newNode;
	}
}

template<class T>
void LinkedList<T>::Display()
{
	Node<T> *temp = new Node<T>;
	temp = this->head;

	int elementNumber = 0;

	while (temp != NULL)
	{
		printf("element %d: %d\n", elementNumber, temp->data);
		elementNumber++;
		temp = temp->next;
	}
}

template<class T>
void LinkedList<T>::Insert_First(T d)
{
	Node<T> *temp = new Node<T>;
	temp->data = d;
	temp->next = this->head;
	this->head = temp;
}

template<class T>
void LinkedList<T>::Insert(int pos, T d)
{
	Node<T> *newNode = new Node<T>;
	newNode->data = d;

	if (this->head == NULL)
	{
		this->head = newNode;
		this->tail = newNode;
	}
	else if (pos == 0)
	{
		Insert_First(d);
	}
	else
	{
		int cp = 0;
		bool found = false;
		Node<T> *temp = new Node<T>;
		Node<T> *previous = new Node<T>;

		temp = this->head;
		while (temp != NULL)
		{
			if (cp == pos)
			{
				//insert here
				previous->next = newNode;
				newNode->next = temp;
				found = true;
				break;
			}
			previous = temp;
			temp = temp->next;
			cp++;
		}

		if (!found)
		{
			//insert at end
			this->tail->next = newNode;
			this->tail = newNode;
			newNode->next = NULL;
		}
	}
}

//deleting
template<class T>
void LinkedList<T>::DeleteFirst()
{
	Node<T> *temp = this->head;
	this->head = this->head->next;
	delete temp;
	temp = 0;
}

template<class T>
void LinkedList<T>::DeleteLast()
{
	if (this->head == NULL)
		return;

	Node<T> *temp = this->head;
	Node<T> *previous = NULL;

	while (temp->next != NULL)
	{
		previous = temp;
		temp = temp->next;
	}

	if (previous != NULL)//if count is > 1
	{
		previous->next = NULL;
		this->tail = previous;
	}
	else
	{
		this->head = NULL;
	}

	delete temp;
	temp = 0;
}

template<class T>
void LinkedList<T>::DeletePosition(int pos)
{
	if (pos < 0)//dumb
		return;
	else if (pos == 0)//still kind of dumb
	{
		DeleteFirst();
		return;
	}

	Node<T> *current = this->head;
	Node<T> *previous = NULL;
	bool found = false;

	int index = 0;
	while (current != NULL)
	{
		if (pos == index)
		{
			found = true;
			break;
		}
		previous = current;
		current = current->next;
		index++;
	}

	if (found)
	{
		//delete current
		Node<T> *temp = current;
		previous->next = current->next;
		delete temp;
		temp = NULL;
	}
	else
	{
		DeleteLast();
	}
}

//sorting
template<class T>
void LinkedList<T>::BubbleSort()
{
	int c = this->Count();
	//Node<T> *temp = new Node<T>;
	Node<T> *current = this->head;
	Node<T> *prev = this->head;
	Node<T> *temp;

	for (int i = 0; i < c; ++i)
	{
		current = prev = this->head;

		while (current->next != NULL)
		{
			if (current->data > current->next->data)
			{
				temp = current->next;
				current->next = current->next->next;
				temp->next = current;

				if (current == this->head) //this is the case of the first element swapping to preserve the head pointer
					this->head = prev = temp;
				else //setup trail correctly
					prev->next = temp;
				current = temp; //update curr to be temp since the positions changed
			}
			//advance pointers
			prev = current;
			current = current->next;
		}
	}
}

//access / helper
template<class T>
int LinkedList<T>::Count()
{
	int c = 0;
	Node<T> *current = this->head;

	if (current == NULL)
		return c;

	while (current != NULL)
	{
		c++;
		current = current->next;
	}

	return c;
}

template <class T>
T LinkedList<T>::Get(int i)
{
	Node<T> *current = this->head;
	int cur = 0;

	while (current != NULL)
	{
		if (cur == i)
		{
			return current->data;
		}
		cur++;
		current = current->next;
	}

	return NULL;
}