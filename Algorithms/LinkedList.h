#pragma once
#include <exception>
#include <optional>
#include <vector>

// TODO: learn about smart pointers.

template <class T>
class LinkedList
{
public:
	LinkedList() noexcept {};
	LinkedList(T data);
	LinkedList(std::initializer_list<T> data_list);
	LinkedList(const LinkedList<T>& other);
	LinkedList(LinkedList<T>&& other) noexcept;
	~LinkedList();
	LinkedList<T>& operator=(std::initializer_list<T> data_list);
	LinkedList<T>& operator=(const LinkedList<T>& other);
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;

	// Adds a node with the given value to the end of the list.
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
	void print(std::ostream& stream) const;

	// Deletes a node at a given index and returns its contents.
	// Throws std::out_of_range if index >= the length of the list.
	T remove(size_t index);

	// Deletes nodes inclusively between two given indexes.
	// Throws std::out_of_range if index1 >= the length of the list.
	void remove(size_t index1, size_t index2);

	// Deletes all the nodes in the list.
	void clear();

	// Returns the number of nodes in the list.
	size_t size() const noexcept;

	// An alias for the size function.
	size_t length() const noexcept;

	// Returns true if the list is empty, false otherwise.
	bool empty() const noexcept;

	// Finds a value, returning a 0-based index as if an array.
	std::optional<size_t> find(T data) const;

	// Reverses the entire list.
	void reverse();

	// Swaps two linked lists.
	void swap(LinkedList<T>& other);

	// Calls a given function on each value in the list.
	void map(T(*f)(T data));

	// Creates a new list with only the nodes with values that make a given function return true.
	LinkedList<T> filter(bool(*f)(T data)) const;

	// Returns the combination of all values in the list, combined using a given function.
	T reduce(T(*f)(T data1, T data2)) const;

	// Collects the data from all nodes into a vector and returns it.
	std::vector<T> vector() const;

	// Determines whether two linked lists have the same data and length.
	bool operator==(const LinkedList<T>& other) const;

	// Determines whether two linked lists do not have the same data and length.
	bool operator!=(const LinkedList<T>& other) const;

	// Returns a reference to an element of the list as if an array but with O(n) complexity.
	// Throws std::out_of_range if the index is out of bounds.
	T& operator[](size_t index);

	// Returns a reference to an element of the list as if an array but with O(n) complexity.
	// Throws std::out_of_range if the index is out of bounds.
	const T& operator[](size_t index) const;

private:

	class Node
	{
	public:
		T data{};
		Node* next = nullptr;
		Node() noexcept {};
		Node(T data);
		Node(const Node& node);

		// Adds a value to the end of the list.
		void append(T data);

		// Adds a value at any index > 0 in the list. The index is relative.
		// Throws std::out_of_range if index >= the length of the list.
		void insert(T data, size_t index);

		// Adds values starting at any index > 0 in the list. The index is relative.
		// Throws std::out_of_range if index >= the length of the list.
		void insert_multiple(std::initializer_list<T> data_list, size_t index);

		// Prints the contents of the list, elements separated by commas and spaces.
		void print(std::ostream& stream) const;

		// Deletes and returns the contents of a node at a given index > 0. The index is relative.
		// Throws std::out_of_range if index >= the length of the list.
		T remove(size_t index);

		// Deletes nodes inclusively between two given indexes.
		// The indexes are relative.
		// Returns the number of nodes removed.
		// Throws std::out_of_range if index1 >= the length of the list.
		size_t remove(size_t index1, size_t index2);

		// Finds a value, returning its relative index based on the given starting index.
		std::optional<size_t> find(T data, size_t index = 0) const;

		// Reverses the entire list.
		Node* reverse(Node* previous);

		// Calls a given function on each value in the list.
		void map(T(*f)(T data));

		// Returns the combination of all values in the list, combined using a given function.
		T reduce(T(*f)(T data1, T data2)) const;

		// Determines whether two linked lists have the same data and length.
		bool operator==(const Node& other) const;

		// Returns a reference to an element of the list as if an array but with O(n) complexity.
		// The index is relative.
		// Throws std::out_of_range if the index is out of bounds.
		T& operator[](size_t index);

		// Returns a reference to an element of the list as if an array but with O(n) complexity.
		// The index is relative.
		// Throws std::out_of_range if the index is out of bounds.
		const T& operator[](size_t index) const;
	};

public:

	class iterator
	{
	public:
		friend class LinkedList;
		iterator() noexcept;
		iterator(Node*& current) noexcept;
		T& operator*() const noexcept;
		iterator& operator++() noexcept;
		iterator operator++(int) noexcept;
		bool operator!=(const iterator& other) const noexcept;
	private:
		Node* previous = nullptr;
		Node* current = nullptr;
	};

	iterator begin() noexcept;
	iterator end() noexcept;

private:

	Node* head = NULL;
	size_t _size = 0;
};

///////////////////
// LinkedList<T> //
///////////////////

template<class T>
inline LinkedList<T>::LinkedList(T data)
{
	this->head = new Node(data);
	this->_size = 1;
}

template<class T>
inline LinkedList<T>::LinkedList(std::initializer_list<T> data_list)
{
	Node** temp = &this->head;
	for (T element : data_list)
	{
		*temp = new Node(element);
		temp = &(*temp)->next;
	}
	this->_size = data_list.size();
}

template<class T>
inline LinkedList<T>::LinkedList(const LinkedList<T>& other)
{
	if (other.head != nullptr)
	{
		this->head = new Node(*other.head);
		this->_size = other.size();
	}
}

template<class T>
inline LinkedList<T>::LinkedList(LinkedList<T>&& other) noexcept
{
	*this = std::move(other);
}

template<class T>
inline LinkedList<T>::~LinkedList()
{
	this->clear();
}

template<class T>
inline LinkedList<T>& LinkedList<T>::operator=(std::initializer_list<T> data_list)
{
	this->clear();
	Node** temp = &this->head;
	for (T element : data_list)
	{
		*temp = new Node(element);
		temp = &(*temp)->next;
	}
	this->_size = data_list.size();
	return *this;
}

template<class T>
inline LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
{
	this->clear();
	if (other.head != nullptr)
		this->head = new Node(*other.head);
	this->_size = other.size();
	return *this;
}

template<class T>
inline LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) noexcept
{
	if (this != &other)
	{
		this->clear();
		this->head = other.head;
		this->_size = other._size;
		other.head = nullptr;
		other._size = 0;
	}
	return *this;
}

template <class T>
inline void LinkedList<T>::append(T data)
{
	if (this->head != nullptr)
		this->head->append(data);
	else
		this->head = new Node(data);
	this->_size += 1;
}

template <class T>
inline void LinkedList<T>::extend(const LinkedList<T>& other)
{
	Node** ptr = &this->head;
	while (*ptr != nullptr)
		ptr = &(*ptr)->next;
	Node* other_ptr = other.head;
	while (other_ptr != nullptr)
	{
		*ptr = new Node(other_ptr->data);
		ptr = &(*ptr)->next;
		other_ptr = other_ptr->next;
	}
	this->_size += other.size();
}

template<class T>
inline void LinkedList<T>::extend(std::initializer_list<T> data_list)
{
	Node** ptr = &this->head;
	while (*ptr != nullptr)
		ptr = &(*ptr)->next;
	for (T element : data_list)
	{
		*ptr = new Node(element);
		ptr = &(*ptr)->next;
	}
	this->_size += data_list.size();
}

template<class T>
inline void LinkedList<T>::insert(T data, size_t index)
{
	if (index > 0)
	{
		if (this->head == nullptr)
			throw std::out_of_range("The insertion index must be < the length of the list.");
		this->head->insert(data, index);
	}
	else
	{
		Node* temp = this->head;
		this->head = new Node(data);
		this->head->next = temp;
	}
	this->_size += 1;
}

template<class T>
inline void LinkedList<T>::insert_multiple(std::initializer_list<T> data_list, size_t index)
{
	if (index > 0)
	{
		if (this->head == nullptr)
			throw std::out_of_range("The insertion index must be < the length of the list.");
		this->head->insert_multiple(data_list, index);
	}
	else
	{
		Node* temp = nullptr;
		for (auto it = std::rbegin(data_list); it != std::rend(data_list); it++)
		{
			temp = this->head;
			this->head = new Node(*it);
			this->head->next = temp;
		}
	}
	this->_size += data_list.size();
}

template<class T>
inline void LinkedList<T>::print(std::ostream& stream) const
{
	if (this->head != nullptr)
		this->head->print(stream);
}

template<class T>
inline T LinkedList<T>::remove(size_t index)
{
	if (this->head == nullptr)
		throw std::out_of_range("The list is already empty.");
	if (index > 0)
	{
		T temp = this->head->remove(index);
		this->_size -= 1;
		return temp;
	}
	this->_size -= 1;
	T temp_data = this->head->data;
	Node* temp = this->head;
	this->head = this->head->next;
	delete temp;
	temp = nullptr;
	return temp_data;
}

template<class T>
inline void LinkedList<T>::remove(size_t index1, size_t index2)
{
	if (this->head == nullptr)
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
	Node* temp = nullptr;
	for (size_t i = 0; i <= index2 - index1; i++)
	{
		if (this->head == nullptr)
		{
			this->_size -= i;
			return;
		}
		temp = this->head;
		this->head = this->head->next;
		delete temp;
		temp = nullptr;
	}
	this->_size -= index2 - index1 + 1;
}

template<class T>
inline void LinkedList<T>::clear()
{
	if (this->head == nullptr)
		return;
	Node* temp = nullptr;
	while (this->head != nullptr)
	{
		temp = this->head->next;
		delete this->head;
		this->head = temp;
	}
	this->_size = 0;
}

template<class T>
inline size_t LinkedList<T>::size() const noexcept
{
	return this->_size;
}

template<class T>
inline size_t LinkedList<T>::length() const noexcept
{
	return this->size();
}

template<class T>
inline bool LinkedList<T>::empty() const noexcept
{
	return this->_size == 0;
}

template<class T>
inline std::optional<size_t> LinkedList<T>::find(T data) const
{
	if (this->head == nullptr)
		return {};
	return this->head->find(data, 0);
}

template<class T>
inline void LinkedList<T>::reverse()
{
	if (this->head != nullptr)
		this->head = this->head->reverse(nullptr);
}

template<class T>
inline void LinkedList<T>::swap(LinkedList<T>& other)
{
	Node* temp_head = this->head;
	this->head = other.head;
	other.head = temp_head;
	size_t temp_size = this->_size;
	this->_size = other._size;
	other._size = temp_size;
}

template<class T>
inline void LinkedList<T>::map(T(*f)(T data))
{
	if (this->head != nullptr)
		this->head->map(f);
}

template<class T>
inline LinkedList<T> LinkedList<T>::filter(bool(*f)(T data)) const
{
	LinkedList<T> other;
	Node** other_ptr = &other.head;
	for (Node* ptr = this->head; ptr != nullptr; ptr = ptr->next)
	{
		if (f(ptr->data))
		{
			*other_ptr = new Node(ptr->data);
			other_ptr = &(*other_ptr)->next;
			other._size += 1;
		}
	}
	return other;
}

template<class T>
inline T LinkedList<T>::reduce(T(*f)(T data1, T data2)) const
{
	if (this->head != nullptr)
		return this->head->reduce(f);
	return T{};
}

template<class T>
inline std::vector<T> LinkedList<T>::vector() const
{
	std::vector<T> v;
	for (Node* ptr = this->head; ptr != nullptr; ptr = ptr->next)
		v.push_back(ptr->data);
	return v;
}

template<class T>
inline bool LinkedList<T>::operator==(const LinkedList<T>& other) const
{
	if (other.head == nullptr && this->head == nullptr)
		return true;
	if (other.head == nullptr || this->head == nullptr)
		return false;
	return *other.head == *this->head;
}

template<class T>
inline bool LinkedList<T>::operator!=(const LinkedList<T>& other) const
{
	return !(*this == other);
}

template <class T>
inline T& LinkedList<T>::operator[](size_t index)
{
	if (this->head == nullptr)
		throw std::out_of_range("The list is empty.");
	return (*this->head)[index];
}

template <class T>
inline const T& LinkedList<T>::operator[](size_t index) const
{
	if (this->head == nullptr)
		throw std::out_of_range("The list is empty.");
	return (*this->head)[index];
}

/////////////////////////////
// LinkedList<T>::iterator //
/////////////////////////////

template <class T>
inline LinkedList<T>::iterator::iterator() noexcept
{
	this->current = nullptr;
}

template <class T>
inline LinkedList<T>::iterator::iterator(Node*& current) noexcept
{
	this->current = current;
}

template <class T>
inline T& LinkedList<T>::iterator::operator*() const noexcept
{
	return this->current->data;
}

template <class T>
inline typename LinkedList<T>::iterator& LinkedList<T>::iterator::operator++() noexcept
{
	if (this->current != nullptr)
	{
		this->previous = this->current;
		this->current = this->current->next;
	}
	return *this;
}

template <class T>
inline typename LinkedList<T>::iterator LinkedList<T>::iterator::operator++(int) noexcept
{
	iterator temp = *this;
	++* this;
	return temp;
}

template <class T>
inline bool LinkedList<T>::iterator::operator!=(typename const iterator& other) const noexcept
{
	return this->current != other.current;
}

template <class T>
inline typename LinkedList<T>::iterator LinkedList<T>::begin() noexcept
{
	return iterator(this->head);
}

template <class T>
inline typename LinkedList<T>::iterator LinkedList<T>::end() noexcept
{
	return iterator();
}

/////////////////////////
// LinkedList<T>::Node //
/////////////////////////

template<class T>
inline LinkedList<T>::Node::Node(T data)
{
	this->data = data;
}

template<class T>
inline LinkedList<T>::Node::Node(const Node& node)
{
	this->data = node.data;
	if (node.next != nullptr)
		this->next = new Node(*node.next);
}

template<class T>
inline void LinkedList<T>::Node::append(T data)
{
	if (this->next != nullptr)
		this->next->append(data);
	else
		this->next = new Node(data);
}

template<class T>
inline void LinkedList<T>::Node::insert(T data, size_t index)
{
	if (index == 0)
		throw std::logic_error("The index should never be 0 in this function.");
	if (index == 1)
	{
		Node* new_node = new Node(data);
		new_node->next = this->next;
		this->next = new_node;
		return;
	}
	if (this->next == nullptr)
		throw std::out_of_range("The insertion index must be < the length of the list.");
	this->next->insert(data, index - 1);
}

template<class T>
inline void LinkedList<T>::Node::insert_multiple(std::initializer_list<T> data_list, size_t index)
{
	if (index == 0)
		throw std::logic_error("The index should never be 0 in this function.");
	if (index == 1)
	{
		Node* temp = nullptr;
		for (auto it = std::rbegin(data_list); it != std::rend(data_list); it++)
		{
			temp = this->next;
			this->next = new Node(*it);
			this->next->next = temp;
		}
		return;
	}
	else if (this->next == nullptr)
		throw std::out_of_range("The insertion index must be < the length of the list.");
	this->next->insert_multiple(data_list, index - 1);
}

template<class T>
inline void LinkedList<T>::Node::print(std::ostream& stream) const
{
	stream << this->data;
	if (this->next != nullptr)
	{
		stream << ", ";
		this->next->print(stream);
	}
}

template<class T>
inline T LinkedList<T>::Node::remove(size_t index)
{
	if (this->next == nullptr)
		throw std::out_of_range("Index out of bounds.");
	if (index > 1)
		return this->next->remove(index - 1);
	T temp_data = this->next->data;
	Node* temp = this->next;
	this->next = this->next->next;
	delete temp;
	temp = nullptr;
	return temp_data;
}

template<class T>
inline size_t LinkedList<T>::Node::remove(size_t index1, size_t index2)
{
	if (this->next == nullptr)
		throw std::out_of_range("Index out of bounds.");
	if (index1 > 1)
		return this->next->remove(index1 - 1, index2 - 1);
	Node* temp = nullptr;
	for (size_t i = 0; i <= index2 - index1; i++)
	{
		if (this->next == nullptr)
			return i;
		temp = this->next;
		this->next = this->next->next;
		delete temp;
		temp = nullptr;
	}
	return index2 - index1 + 1;
}

template<class T>
inline std::optional<size_t> LinkedList<T>::Node::find(T data, size_t index) const
{
	if (this->data == data)
		return index;
	if (this->next == nullptr)
		return {};
	return this->next->find(data, index + 1);
}

template<class T>
inline typename LinkedList<T>::Node* LinkedList<T>::Node::reverse(Node* previous)
{
	if (this->next != nullptr)
	{
		Node* new_head = this->next->reverse(this);
		this->next = previous;
		return new_head;
	}
	this->next = previous;
	return this;
}

template<class T>
inline void LinkedList<T>::Node::map(T(*f)(T data))
{
	this->data = f(this->data);
	if (this->next != nullptr)
		this->next->map(f);
}

template<class T>
inline T LinkedList<T>::Node::reduce(T(*f)(T data1, T data2)) const
{
	if (this->next == nullptr)
		return this->data;
	return f(this->data, this->next->reduce(f));
}

template<class T>
inline bool LinkedList<T>::Node::operator==(const LinkedList<T>::Node& other) const
{
	if (other.next == nullptr && this->next == nullptr)
		return true;
	if (other.data != this->data || other.next == nullptr || this->next == nullptr)
		return false;
	return *other.next == *this->next;
}

template <class T>
inline T& LinkedList<T>::Node::operator[](size_t index)
{
	if (index == 0)
		return this->data;
	if (this->next == nullptr)
		throw std::out_of_range("Index out of bounds.");
	return (*this->next)[index - 1];
}

template <class T>
inline const T& LinkedList<T>::Node::operator[](size_t index) const
{
	if (index == 0)
		return this->data;
	if (this->next == nullptr)
		throw std::out_of_range("Index out of bounds.");
	return (*this->next)[index - 1];
}
