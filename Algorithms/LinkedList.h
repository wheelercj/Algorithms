#pragma once
#include "LinkedListNode.h"

void manual_linked_list_test();

// TODO: learn about smart pointers.

template <class T>
class LinkedList
{
public:
	
	LinkedList();

	LinkedList(T data);

	LinkedList(std::initializer_list<T> data_list);

	LinkedList(const LinkedList<T>& other);

	~LinkedList();

	// Adds a value to the end of the list.
	void append(T data);

	// Combines two lists, adding each value in the given list to the end of this list.
	void extend(const LinkedList<T>& other);

	// Adds a value at any index in the list.
	// Throws std::out_of_range if index >= the length of the list.
	void insert(T data, size_t index);

	// Prints the contents of the list, elements separated by commas and spaces.
	void print(std::ostringstream& stream);

	// Deletes and returns the contents of a node at a given index.
	// Throws std::out_of_range if index >= the length of the list.
	T remove(size_t index);

	// Deletes all the nodes in the list.
	void clear();

	// Returns the number of nodes in the list.
	size_t size() const;

	// An alias for the size function.
	size_t length() const;

	// TODO: create iterator

	/*LinkedList<T>::iterator begin();
	
	LinkedList<T>::iterator end();*/

	// Finds a value, returning a 0-based index as if an array.
	std::optional<size_t> find(T data);

	// Calls a given function on each value in the list.
	void map(T(*f)(T data));

	// Creates a new list with only the nodes with values that make a given function return true.
	LinkedList<T> filter(bool(*f)(T data));

	// Returns the combination of all values in the list,
	// combined using a given function.
	T reduce(T(*f)(T data1, T data2));

	// Determines whether two linked lists have the same data and length.
	bool operator==(const LinkedList<T>& other);

	// Determines whether two linked lists do not have the same data and length.
	bool operator!=(const LinkedList<T>& other);

	// Returns a reference to an element of the list as if an array but with O(n) complexity.
	// Throws std::out_of_range if the index >= the length of the list.
	T& operator[](size_t index);

	// Returns a reference to an element of the list as if an array but with O(n) complexity.
	// Throws std::out_of_range if the index >= the length of the list.
	const T& operator[](size_t index) const;

private:
	
	LinkedListNode<T>* head = NULL;

	size_t _size = 0;
};

template<class T>
inline LinkedList<T>::LinkedList()
{
}

template<class T>
inline LinkedList<T>::LinkedList(T data)
{
	this->head = new LinkedListNode(data);
	this->_size = 1;
}

template<class T>
inline LinkedList<T>::LinkedList(std::initializer_list<T> data_list)
{
	LinkedListNode<T>** temp = &this->head;
	for (T element : data_list)
	{
		*temp = new LinkedListNode(element);
		temp = &(*temp)->next;
	}
	this->_size = data_list.size();
}

template<class T>
inline LinkedList<T>::LinkedList(const LinkedList<T>& other)
{
	if (other.head != NULL)
	{
		this->head = new LinkedListNode(*other.head);
		this->_size = other.size();
	}
}

template<class T>
inline LinkedList<T>::~LinkedList()
{
	this->clear();
	this->_size = 0;
}

template <class T>
void LinkedList<T>::append(T data)
{
	if (this->head != NULL)
		this->head->append(data);
	else
		this->head = new LinkedListNode(data);
	this->_size += 1;
}

template <class T>
void LinkedList<T>::extend(const LinkedList<T>& other)
{
	// TODO
	this->_size += other.size();
}

template<class T>
inline void LinkedList<T>::insert(T data, size_t index)
{
	if (index > 0)
		this->head->insert(data, index);
	else
	{
		LinkedListNode<T>* temp = this->head;
		this->head = new LinkedListNode(data);
		this->head->next = temp;
	}
	this->_size += 1;
}

template<class T>
inline void LinkedList<T>::print(std::ostringstream& stream)
{
	if (this->head != NULL)
		this->head->print(stream);
}

template<class T>
inline T LinkedList<T>::remove(size_t index)
{
	if (this->head == NULL)
		throw std::out_of_range("The list is already empty.");
	if (index > 0)
		return this->head->remove(index);
	else
	{
		T temp_data = this->head->data;
		LinkedListNode<T>* temp = this->head;
		this->head = this->head->next;
		delete temp;
		temp = NULL;
		return temp_data;
	}
	this->_size -= 1;
}

template<class T>
inline void LinkedList<T>::clear()
{
	if (this->head == NULL)
		return;
	LinkedListNode<T>* temp = NULL;
	while (this->head != NULL)
	{
		temp = this->head->next;
		delete this->head;
		this->head = temp;
	}
	this->_size = 0;
}

template<class T>
inline size_t LinkedList<T>::size() const
{
	return this->_size;
}

template<class T>
inline size_t LinkedList<T>::length() const
{
	return this->size();
}

template<class T>
inline std::optional<size_t> LinkedList<T>::find(T data)
{
	if (this->head == NULL)
		return {};
	return this->head->find(data, 0);
}

template<class T>
inline void LinkedList<T>::map(T(*f)(T data))
{
	if (this->head != NULL)
		this->head->map(f);
}

template<class T>
inline LinkedList<T> LinkedList<T>::filter(bool(*f)(T data))
{
	LinkedList<T> new_list;
	// TODO

	/*while (this->head != NULL && !f(this->head->data))
		this->remove(0);
	if (this->head != NULL)
		this->head->filter(f);*/
	return new_list;
}

template<class T>
inline T LinkedList<T>::reduce(T(*f)(T data1, T data2))
{
	if (this->head != NULL)
		return this->head->reduce(f);
	return T{};
}

template<class T>
inline bool LinkedList<T>::operator==(const LinkedList<T>& other)
{
	if (other.head == NULL && this->head != NULL
		|| other.head != NULL && this->head == NULL)
		return false;
	return *other.head == *this->head;
}

template<class T>
inline bool LinkedList<T>::operator!=(const LinkedList<T>& other)
{
	return !(*this == other);
}

template <class T>
inline T& LinkedList<T>::operator[](size_t index)
{
	if (this->head == NULL)
		throw std::out_of_range("The list is empty.");
	return (*this->head)[index];
}

template <class T>
inline const T& LinkedList<T>::operator[](size_t index) const
{
	if (this->head == NULL)
		throw std::out_of_range("The list is empty.");
	return (*this->head)[index];
}
