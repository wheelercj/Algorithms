// LinkedListNode isn't intended to be used outside the LinkedList class.
// Some of its operations force use of a dummy head node while others expect
// there to be no dummy head node, and the class uses the new operator but
// not the delete operator.
#pragma once
#include <exception>
#include <optional>


template <class T>
class LinkedListNode
{

public:

	T data{};

	LinkedListNode<T>* next = NULL;

	LinkedListNode();

	LinkedListNode(T data);

	LinkedListNode(const LinkedListNode<T>& node);

	// Adds a value to the end of the list.
	void append(T data);
	
	// Adds a value at any index > 0 in the list. The index is relative.
	// Throws std::out_of_range if index >= the length of the list.
	void insert(T data, size_t index);
	
	// Prints the contents of the list, elements separated by commas and spaces.
	void print(std::ostream& stream);

	// Deletes and returns the contents of a node at a given index > 0. The index is relative.
	// Throws std::out_of_range if index >= the length of the list.
	T remove(size_t index);

	// Finds a value, returning its relative index based on the
	// given starting index.
	std::optional <size_t> find(T data, size_t index = 0);

	// Calls a given function on each value in the list.
	void map(T(*f)(T data));

	// Creates a new list with only the nodes with values that make a given function return true.
	LinkedListNode<T> filter(bool(*f)(T data));

	// Returns the combination of all values in the list,
	// combined using a given function.
	T reduce(T(*f)(T data1, T data2));

	// Determines whether two linked lists have the same data and length.
	bool operator==(const LinkedListNode<T>& other);

	// Returns a reference to an element of the list as if an array but with O(n) complexity.
	// The index is relative.
	// Throws std::out_of_range if the index >= the length of the list.
	T& operator[](size_t index);

	// Returns a reference to an element of the list as if an array but with O(n) complexity.
	// The index is relative.
	// Throws std::out_of_range if the index >= the length of the list.
	const T& operator[](size_t index) const;

};

template<class T>
inline LinkedListNode<T>::LinkedListNode()
{
}

template<class T>
inline LinkedListNode<T>::LinkedListNode(T data)
{
	this->data = data;
}

template<class T>
inline LinkedListNode<T>::LinkedListNode(const LinkedListNode<T>& node)
{
	this->data = node.data;
	if (node.next != NULL)
		this->next = new LinkedListNode(*node.next);
}

template<class T>
inline void LinkedListNode<T>::append(T data)
{
	if (this->next != NULL)
		this->next->append(data);
	else
		this->next = new LinkedListNode(data);
}

template<class T>
inline void LinkedListNode<T>::insert(T data, size_t index)
{
	if (index == 0)
		throw std::logic_error("The index should never be 0 in this function.");
	if (index == 1)
	{
		LinkedListNode<T>* new_node = new LinkedListNode(data);
		new_node->next = this->next;
		this->next = new_node;
		return;
	}
	if (this->next == NULL)
		throw std::out_of_range("The insertion index must be < the length of the list.");
	this->next->insert(data, index - 1);
}

template<class T>
inline void LinkedListNode<T>::print(std::ostream& stream)
{
	stream << this->data;
	if (this->next != NULL)
	{
		stream << ", ";
		this->next->print(stream);
	}
}

template<class T>
inline T LinkedListNode<T>::remove(size_t index)
{
	if (this->next == NULL)
		throw std::out_of_range("Index out of bounds.");
	if (index > 1)
		return this->next->remove(index - 1);
	else
	{
		T temp_data = this->next->data;
		LinkedListNode* temp = this->next;
		this->next = this->next->next;
		delete temp;
		temp = NULL;
		return temp_data;
	}
}

template<class T>
inline std::optional<size_t> LinkedListNode<T>::find(T data, size_t index)
{
	if (this->data == data)
		return index;
	if (this->next == NULL)
		return {};
	return this->next->find(data, index + 1);
}

template<class T>
inline void LinkedListNode<T>::map(T(*f)(T data))
{
	this->data = f(this->data);
	if (this->next != NULL)
		this->next->map(f);
}

template<class T>
inline LinkedListNode<T> LinkedListNode<T>::filter(bool(*f)(T data))
{
	// TODO

	/*while (this->next != NULL && !f(this->next->data))
		this->remove(1);
	if (this->next != NULL)
		this->next->filter(f);*/
}

template<class T>
inline T LinkedListNode<T>::reduce(T(*f)(T data1, T data2))
{
	if (this->next == NULL)
		return this->data;
	return f(this->data, this->next->reduce(f));
}

template<class T>
inline bool LinkedListNode<T>::operator==(const LinkedListNode<T>& other)
{
	if (other.data != this->data
		|| other.next == NULL && this->next != NULL
		|| other.next != NULL && this->next == NULL)
		return false;
	if (other.next == NULL && this->next == NULL)
		return true;
	return *other.next == *this->next;
}

template <class T>
inline T& LinkedListNode<T>::operator[](size_t index)
{
	if (index == 0)
		return this->data;
	if (this->next == NULL)
		throw std::out_of_range("Index out of bounds.");
	return (*this->next)[index - 1];
}

template <class T>
inline const T& LinkedListNode<T>::operator[](size_t index) const
{
	if (index == 0)
		return this->data;
	if (this->next == NULL)
		throw std::out_of_range("Index out of bounds.");
	return (*this->next)[index - 1];
}
