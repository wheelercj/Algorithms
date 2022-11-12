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

	LinkedList<T>& operator=(const LinkedList<T>& other);

	LinkedList<T>& operator=(LinkedList<T>&& other);

	LinkedList<T>& operator=(std::initializer_list<T> data_list);

	// Adds a value to the end of the list.
	void append(T data);

	// Combines two lists, adding each value in the given list to the end of this list.
	void extend(const LinkedList<T>& other);

	// Combines two lists, adding each value in the given initializer list to the end of this linked list.
	void extend(std::initializer_list<T> data_list);

	// Adds a node with the given value at any index in the list.
	// Throws std::out_of_range if index >= the length of the list.
	void insert(T data, size_t index);

	// Adds nodes with the given values starting at any index in the list.
	// Throws std::out_of_range if index >= the length of the list.
	void insert_multiple(std::initializer_list<T> data_list, size_t index);

	// Prints the contents of the list, elements separated by commas and spaces.
	void print(std::ostream& stream);

	// Deletes a node at a given index and returns its contents.
	// Throws std::out_of_range if index >= the length of the list.
	T remove(size_t index);

	// Deletes nodes inclusively between two given indexes.
	// Throws std::out_of_range index1 >= the length of the list.
	void remove(size_t index1, size_t index2);

	// Deletes all the nodes in the list.
	void clear();

	// Returns the number of nodes in the list.
	size_t size() const;

	// An alias for the size function.
	size_t length() const;

	// Returns true if the list is empty, false otherwise.
	bool empty() const;

	// TODO: create iterator

	/*LinkedList<T>::iterator begin();
	
	LinkedList<T>::iterator end();*/

	// Finds a value, returning a 0-based index as if an array.
	std::optional<size_t> find(T data);

	// Reverses the entire list.
	void reverse();

	// Swaps two linked lists.
	void swap(LinkedList<T>& other);

	// Calls a given function on each value in the list.
	void map(T(*f)(T data));

	// Creates a new list with only the nodes with values that make a given function return true.
	LinkedList<T> filter(bool(*f)(T data));

	// Returns the combination of all values in the list, combined using a given function.
	T reduce(T(*f)(T data1, T data2));

	// Determines whether two linked lists have the same data and length.
	bool operator==(const LinkedList<T>& other);

	// Determines whether two linked lists do not have the same data and length.
	bool operator!=(const LinkedList<T>& other);

	// Returns a reference to an element of the list as if an array but with O(n) complexity.
	// Throws std::out_of_range if the index is out of bounds.
	T& operator[](size_t index);

	// Returns a reference to an element of the list as if an array but with O(n) complexity.
	// Throws std::out_of_range if the index is out of bounds.
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
}


template<class T>
inline LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
{
	// TODO
}

template<class T>
inline LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other)
{
	// TODO
}

template<class T>
inline LinkedList<T>& LinkedList<T>::operator=(std::initializer_list<T> data_list)
{
	// TODO
}

template <class T>
inline void LinkedList<T>::append(T data)
{
	if (this->head != NULL)
		this->head->append(data);
	else
		this->head = new LinkedListNode(data);
	this->_size += 1;
}

template <class T>
inline void LinkedList<T>::extend(const LinkedList<T>& other)
{
	LinkedListNode<T>** ptr = &this->head;
	while (*ptr != NULL)
		ptr = &(*ptr)->next;
	LinkedListNode<T>* other_ptr = other.head;
	while (other_ptr != NULL)
	{
		*ptr = new LinkedListNode(other_ptr->data);
		ptr = &(*ptr)->next;
		other_ptr = other_ptr->next;
	}
	this->_size += other.size();
}

template<class T>
inline void LinkedList<T>::extend(std::initializer_list<T> data_list)
{
	LinkedListNode<T>** ptr = &this->head;
	while (*ptr != NULL)
		ptr = &(*ptr)->next;
	for (T element : data_list)
	{
		*ptr = new LinkedListNode(element);
		ptr = &(*ptr)->next;
	}
	this->_size += data_list.size();
}

template<class T>
inline void LinkedList<T>::insert(T data, size_t index)
{
	if (index > 0)
	{
		if (this->head == NULL)
			throw std::out_of_range("The insertion index must be < the length of the list.");
		this->head->insert(data, index);
	}
	else
	{
		LinkedListNode<T>* temp = this->head;
		this->head = new LinkedListNode(data);
		this->head->next = temp;
	}
	this->_size += 1;
}

template<class T>
inline void LinkedList<T>::insert_multiple(std::initializer_list<T> data_list, size_t index)
{
	if (index > 0)
	{
		if (this->head == NULL)
			throw std::out_of_range("The insertion index must be < the length of the list.");
		this->head->insert_multiple(data_list, index);
	}
	else
	{
		LinkedListNode<T>* temp = NULL;
		for (auto it = std::rbegin(data_list); it != std::rend(data_list); it++)
		{
			temp = this->head;
			this->head = new LinkedListNode<T>(*it);
			this->head->next = temp;
		}
	}
	this->_size += data_list.size();
}

template<class T>
inline void LinkedList<T>::print(std::ostream& stream)
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
	{
		T temp = this->head->remove(index);
		this->_size -= 1;
		return temp;
	}
	this->_size -= 1;
	T temp_data = this->head->data;
	LinkedListNode<T>* temp = this->head;
	this->head = this->head->next;
	delete temp;
	temp = NULL;
	return temp_data;
}

template<class T>
inline void LinkedList<T>::remove(size_t index1, size_t index2)
{
	if (this->head == NULL)
		throw std::out_of_range("The list is already empty.");
	if (index1 > index2)
	{
		size_t temp = index1;
		index1 = index2;
		index2 = temp;
	}
	if (index1 > 0)
	{
		this->_size -= this->head->remove(index1, index2);
		return;
	}
	LinkedListNode<T>* temp = NULL;
	for (size_t i = 0; i <= index2 - index1; i++)
	{
		if (this->head == NULL)
		{
			this->_size -= i;
			return;
		}
		temp = this->head;
		this->head = this->head->next;
		delete temp;
		temp = NULL;
	}
	this->_size -= index2 - index1 + 1;
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
inline bool LinkedList<T>::empty() const
{
	return this->_size == 0;
}

template<class T>
inline std::optional<size_t> LinkedList<T>::find(T data)
{
	if (this->head == NULL)
		return {};
	return this->head->find(data, 0);
}

template<class T>
inline void LinkedList<T>::reverse()
{
	if (this->head != NULL)
		this->head = this->head->reverse(NULL);
}

template<class T>
inline void LinkedList<T>::swap(LinkedList<T>& other)
{
	LinkedListNode<T>* temp_head = this->head;
	this->head = other.head;
	other.head = temp_head;
	size_t temp_size = this->_size;
	this->_size = other._size;
	other._size = temp_size;
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
