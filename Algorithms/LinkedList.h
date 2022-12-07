#pragma once
#include <exception>
#include <memory>
#include <optional>
#include <vector>

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

	// Creates and returns a list with only the nodes with values that make a given function return true.
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
		std::unique_ptr<Node> next;
		Node() noexcept {};
		Node(T data) : data{data} {};
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
		iterator(const Node*& current) noexcept;
		iterator(std::unique_ptr<Node>& current) noexcept;
		iterator(const std::unique_ptr<Node>& current) noexcept;
		T& operator*() noexcept;
		const T& operator*() const noexcept;
		iterator& operator++() noexcept;
		iterator operator++(int) noexcept;
		bool operator!=(const iterator& other) const noexcept;
	private:
		Node* previous = nullptr;
		Node* current = nullptr;
	};

	iterator begin() noexcept;
	const iterator begin() const noexcept;
	iterator end() noexcept;
	const iterator end() const noexcept;

private:

	std::unique_ptr<Node> head;
	size_t _size = 0;
};

///////////////////
// LinkedList<T> //
///////////////////

template<class T>
inline LinkedList<T>::LinkedList(T data)
{
	head = std::make_unique<Node>(data);
	_size = 1;
}

template<class T>
inline LinkedList<T>::LinkedList(std::initializer_list<T> data_list)
{
	std::unique_ptr<Node>* temp = &head;
	for (T e : data_list)
	{
		*temp = std::make_unique<Node>(e);
		temp = &(*temp)->next;
	}
	_size = data_list.size();
}

template<class T>
inline LinkedList<T>::LinkedList(const LinkedList<T>& other)
{
	if (other.head != nullptr)
	{
		head = std::make_unique<Node>(other.head->data);
		_size = other.size();
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
	clear();
}

template<class T>
inline LinkedList<T>& LinkedList<T>::operator=(std::initializer_list<T> data_list)
{
	clear();
	Node** temp = &head;
	for (T e : data_list)
	{
		*temp = std::make_unique<Node>(e);
		temp = &(*temp)->next;
	}
	_size = data_list.size();
	return *this;
}

template<class T>
inline LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
{
	clear();
	if (other.head != nullptr)
		head = std::make_unique<Node>(*other.head);
	_size = other.size();
	return *this;
}

template<class T>
inline LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) noexcept
{
	if (this != &other)
	{
		clear();
		head = std::move(other.head);
		_size = std::move(other._size);
		other.head = nullptr;
		other._size = 0;
	}
	return *this;
}

template <class T>
inline void LinkedList<T>::append(T data)
{
	if (head != nullptr)
		head->append(data);
	else
		head = std::make_unique<Node>(data);
	_size += 1;
}

template <class T>
inline void LinkedList<T>::extend(const LinkedList<T>& other)
{
	std::unique_ptr<Node>* ptr = &head;
	while (*ptr != nullptr)
		ptr = &(*ptr)->next;
	for (T e : other)
	{
		*ptr = std::make_unique<Node>(e);
		ptr = &(*ptr)->next;
	}
	_size += other.size();
}

template<class T>
inline void LinkedList<T>::extend(std::initializer_list<T> data_list)
{
	std::unique_ptr<Node>* ptr = &head;
	while (*ptr != nullptr)
		ptr = &(*ptr)->next;
	for (T e : data_list)
	{
		*ptr = std::make_unique<Node>(e);
		ptr = &(*ptr)->next;
	}
	_size += data_list.size();
}

template<class T>
inline void LinkedList<T>::insert(T data, size_t index)
{
	if (index > 0)
	{
		if (head == nullptr)
			throw std::out_of_range("The insertion index must be < the length of the list.");
		head->insert(data, index);
	}
	else
	{
		std::unique_ptr<Node> temp = std::move(head);
		head = std::make_unique<Node>(data);
		head->next = std::move(temp);
	}
	_size += 1;
}

template<class T>
inline void LinkedList<T>::insert_multiple(std::initializer_list<T> data_list, size_t index)
{
	if (index > 0)
	{
		if (head == nullptr)
			throw std::out_of_range("The insertion index must be < the length of the list.");
		head->insert_multiple(data_list, index);
	}
	else
	{
		for (auto it = std::rbegin(data_list); it != std::rend(data_list); it++)
		{
			std::unique_ptr<Node> temp = std::move(head);
			head = std::make_unique<Node>(*it);
			head->next = std::move(temp);
		}
	}
	_size += data_list.size();
}

template<class T>
inline void LinkedList<T>::print(std::ostream& stream) const
{
	if (head != nullptr)
		head->print(stream);
}

template<class T>
inline T LinkedList<T>::remove(size_t index)
{
	if (head == nullptr)
		throw std::out_of_range("The list is already empty.");
	if (index > 0)
	{
		T temp = head->remove(index);
		_size -= 1;
		return temp;
	}
	_size -= 1;
	T temp_data = head->data;
	head = std::move(head->next);
	return temp_data;
}

template<class T>
inline void LinkedList<T>::remove(size_t index1, size_t index2)
{
	if (head == nullptr)
		throw std::out_of_range("The list is already empty.");
	if (index1 > index2)
	{
		size_t temp = std::move(index1);
		index1 = std::move(index2);
		index2 = std::move(temp);
	}
	if (index1 > 0)
	{
		_size -= head->remove(index1, index2);
		return;
	}
	for (size_t i = 0; i <= index2 - index1; i++)
	{
		if (head == nullptr)
		{
			_size -= i;
			return;
		}
		head = std::move(head->next);
	}
	_size -= index2 - index1 + 1;
}

template<class T>
inline void LinkedList<T>::clear()
{
	head.reset();
	_size = 0;
}

template<class T>
inline size_t LinkedList<T>::size() const noexcept
{
	return _size;
}

template<class T>
inline size_t LinkedList<T>::length() const noexcept
{
	return size();
}

template<class T>
inline bool LinkedList<T>::empty() const noexcept
{
	return _size == 0;
}

template<class T>
inline std::optional<size_t> LinkedList<T>::find(T data) const
{
	if (head == nullptr)
		return {};
	return head->find(data, 0);
}

template<class T>
inline void LinkedList<T>::reverse()
{
	std::unique_ptr<Node> current = std::move(head);
	std::unique_ptr<Node> previous = nullptr;
	std::unique_ptr<Node> temp = nullptr;
	while (current != nullptr)
	{
		temp = std::move(current->next);
		current->next = std::move(previous);
		previous = std::move(current);
		current = std::move(temp);
	}
	head = std::move(previous);
}

template<class T>
inline void LinkedList<T>::swap(LinkedList<T>& other)
{
	std::unique_ptr<Node> temp_head = std::move(head);
	head = std::move(other.head);
	other.head = std::move(temp_head);
	size_t temp_size = std::move(_size);
	_size = std::move(other._size);
	other._size = std::move(temp_size);
}

template<class T>
inline void LinkedList<T>::map(T(*f)(T data))
{
	if (head != nullptr)
		head->map(f);
}

template<class T>
inline LinkedList<T> LinkedList<T>::filter(bool(*f)(T data)) const
{
	LinkedList<T> other;
	std::unique_ptr<Node>* other_ptr = &other.head;
	for (T& e : *this)
	{
		if (f(e))
		{
			*other_ptr = std::make_unique<Node>(e);
			other_ptr = &(*other_ptr)->next;
			other._size += 1;
		}
	}
	return other;
}

template<class T>
inline T LinkedList<T>::reduce(T(*f)(T data1, T data2)) const
{
	if (head != nullptr)
		return head->reduce(f);
	return T{};
}

template<class T>
inline std::vector<T> LinkedList<T>::vector() const
{
	std::vector<T> v;
	for (T& e : *this)
		v.push_back(e);
	return v;
}

template<class T>
inline bool LinkedList<T>::operator==(const LinkedList<T>& other) const
{
	if (other.head == nullptr && head == nullptr)
		return true;
	if (other.head == nullptr || head == nullptr)
		return false;
	return *other.head == *head;
}

template<class T>
inline bool LinkedList<T>::operator!=(const LinkedList<T>& other) const
{
	return !(*this == other);
}

template <class T>
inline T& LinkedList<T>::operator[](size_t index)
{
	if (head == nullptr)
		throw std::out_of_range("The list is empty.");
	return (*head)[index];
}

template <class T>
inline const T& LinkedList<T>::operator[](size_t index) const
{
	if (head == nullptr)
		throw std::out_of_range("The list is empty.");
	return (*head)[index];
}

/////////////////////////////
// LinkedList<T>::iterator //
/////////////////////////////

template <class T>
inline LinkedList<T>::iterator::iterator() noexcept
{
	current = nullptr;
}

template <class T>
inline LinkedList<T>::iterator::iterator(Node*& current) noexcept
{
	this->current = current;
}

template <class T>
inline LinkedList<T>::iterator::iterator(const Node*& current) noexcept
{
	this->current = current;
}

template <class T>
inline LinkedList<T>::iterator::iterator(std::unique_ptr<Node>& current) noexcept
{
	this->current = current.get();
}

template <class T>
inline LinkedList<T>::iterator::iterator(const std::unique_ptr<Node>& current) noexcept
{
	this->current = current.get();
}

template <class T>
inline T& LinkedList<T>::iterator::operator*() noexcept
{
	return current->data;
}

template <class T>
inline const T& LinkedList<T>::iterator::operator*() const noexcept
{
	return current->data;
}

template <class T>
inline typename LinkedList<T>::iterator& LinkedList<T>::iterator::operator++() noexcept
{
	if (current != nullptr)
	{
		previous = current;
		current = current->next.get();
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
	return current != other.current;
}

template <class T>
inline typename LinkedList<T>::iterator LinkedList<T>::begin() noexcept
{
	return iterator(head);
}

template <class T>
inline const typename LinkedList<T>::iterator LinkedList<T>::begin() const noexcept
{
	return iterator(head);
}

template <class T>
inline typename LinkedList<T>::iterator LinkedList<T>::end() noexcept
{
	return iterator();
}

template <class T>
inline const typename LinkedList<T>::iterator LinkedList<T>::end() const noexcept
{
	return iterator();
}

/////////////////////////
// LinkedList<T>::Node //
/////////////////////////

template<class T>
inline LinkedList<T>::Node::Node(const Node& node)
{
	data = node.data;
	if (node.next != nullptr)
		next = std::make_unique<Node>(*node.next);
}

template<class T>
inline void LinkedList<T>::Node::append(T data)
{
	if (next != nullptr)
		next->append(data);
	else
		next = std::make_unique<Node>(data);
}

template<class T>
inline void LinkedList<T>::Node::insert(T data, size_t index)
{
	if (index == 0)
		throw std::logic_error("The index should never be 0 in this function.");
	if (index == 1)
	{
		std::unique_ptr<Node> node = std::make_unique<Node>(data);
		node->next = std::move(next);
		next = std::move(node);
		return;
	}
	if (next == nullptr)
		throw std::out_of_range("The insertion index must be < the length of the list.");
	next->insert(data, index - 1);
}

template<class T>
inline void LinkedList<T>::Node::insert_multiple(std::initializer_list<T> data_list, size_t index)
{
	if (index == 0)
		throw std::logic_error("The index should never be 0 in this function.");
	if (index == 1)
	{
		for (auto it = std::rbegin(data_list); it != std::rend(data_list); it++)
		{
			std::unique_ptr<Node> temp = std::move(next);
			next = std::make_unique<Node>(*it);
			next->next = std::move(temp);
		}
		return;
	}
	else if (next == nullptr)
		throw std::out_of_range("The insertion index must be < the length of the list.");
	next->insert_multiple(data_list, index - 1);
}

template<class T>
inline void LinkedList<T>::Node::print(std::ostream& stream) const
{
	stream << data;
	if (next != nullptr)
	{
		stream << ", ";
		next->print(stream);
	}
}

template<class T>
inline T LinkedList<T>::Node::remove(size_t index)
{
	if (next == nullptr)
		throw std::out_of_range("Index out of bounds.");
	if (index > 1)
		return next->remove(index - 1);
	T temp_data = next->data;
	next = std::move(next->next);
	return temp_data;
}

template<class T>
inline size_t LinkedList<T>::Node::remove(size_t index1, size_t index2)
{
	if (next == nullptr)
		throw std::out_of_range("Index out of bounds.");
	if (index1 > 1)
		return next->remove(index1 - 1, index2 - 1);
	for (size_t i = 0; i <= index2 - index1; i++)
	{
		if (next == nullptr)
			return i;
		next = std::move(next->next);
	}
	return index2 - index1 + 1;
}

template<class T>
inline std::optional<size_t> LinkedList<T>::Node::find(T data, size_t index) const
{
	if (this->data == data)
		return index;
	if (next == nullptr)
		return {};
	return next->find(data, index + 1);
}

template<class T>
inline void LinkedList<T>::Node::map(T(*f)(T data))
{
	data = f(data);
	if (next != nullptr)
		next->map(f);
}

template<class T>
inline T LinkedList<T>::Node::reduce(T(*f)(T data1, T data2)) const
{
	if (next == nullptr)
		return data;
	return f(data, next->reduce(f));
}

template<class T>
inline bool LinkedList<T>::Node::operator==(const LinkedList<T>::Node& other) const
{
	if (other.next == nullptr && next == nullptr)
		return true;
	if (other.data != data || other.next == nullptr || next == nullptr)
		return false;
	return *other.next == *next;
}

template <class T>
inline T& LinkedList<T>::Node::operator[](size_t index)
{
	if (index == 0)
		return data;
	if (next == nullptr)
		throw std::out_of_range("Index out of bounds.");
	return (*next)[index - 1];
}

template <class T>
inline const T& LinkedList<T>::Node::operator[](size_t index) const
{
	if (index == 0)
		return data;
	if (next == nullptr)
		throw std::out_of_range("Index out of bounds.");
	return (*next)[index - 1];
}
