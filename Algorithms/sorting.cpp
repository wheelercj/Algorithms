#include <iostream>
#include <ctime>
#include "sorting.h"
using namespace std;

// Fills the array with random numbers.
void randomize(int numbers[], int size, int max)
{
	srand((unsigned)time(0));
	for (int i = 0; i < size; i++)
		numbers[i] = 1 + rand() % max;
}

void manual_sorting_test()
{
	const int size = 10;
	int numbers[size];
	const int max_value = 100;
	randomize(numbers, size, max_value);

	cout << "\n Unsorted array: ";
	print(numbers, size);

	struct is_greater
	{
		bool operator()(const int& left, const int& right)
		{
			return left > right;
		}
	};

	struct are_equal
	{
		bool operator()(const int& left, const int& right)
		{
			return left == right;
		}
	};

	prompt_and_sort_array<int, is_greater>(numbers, size);

	cout << "\n Sorted array: ";
	print(numbers, size);

	cout << "\n What value are you looking for? ";
	int value;
	cin >> value;

	int result = search_array<int, is_greater, are_equal>(numbers, size, value);

	if (result == -1)
		cout << "\n Error: number not found.";
	else
		cout << "\n The value is in element " << result;
}

template <class T>
void print(T items[], int size)
{
	for (int i = 0; i < size; i++)
		cout << " " << items[i];
}

template <class T>
inline void swap_(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

template <class T, class is_greater>
void prompt_and_sort_array(T items[], int size)
{
	switch (print_sort_menu())
	{
	case 1:
		bubble_sort<T, is_greater>(items, size);
		break;
	case 2:
		selection_sort<T, is_greater>(items, size);
		break;
	case 3:
		insertion_sort<T, is_greater>(items, size);
		break;
	case 4:
		shell_sort<T, is_greater>(items, size);
		break;
	case 5:
		quicksort<T, is_greater>(items, 0, size - 1);
		break;
	case 6:
		merge_sort<T, is_greater>(items, 0, size - 1);
		break;
	case 7:
		heap_sort<T, is_greater>(items, size);
		break;
	default:
		cout << "\n Error: invalid sorting algorithm choice.";
	}
}

int print_sort_menu()
{
	int choice;
	cout << "\n Which sorting algorithm do you want to use?"
		"\n 1. Bubble sort"
		"\n 2. Selection sort"
		"\n 3. Insertion sort"
		"\n 4. Shell sort"
		"\n 5. Quicksort"
		"\n 6. Merge sort"
		"\n 7. Heap sort"
		"\n> ";
	cin >> choice;
	return choice;
}

template <class T, class is_greater, class are_equal>
int search_array(T items[], int size, T value)
{
	switch (print_search_menu())
	{
	case 1:
		return linear_search<T, are_equal>(items, size, value);
	case 2:
		return binary_search<T, is_greater, are_equal>(items, size, value);
	default:
		return -1;
	}
}

int print_search_menu()
{
	int choice;
	cout << "\n Which searching algorithm do you want to use?"
		"\n 1. Linear search"
		"\n 2. Binary search"
		"\n> ";
	cin >> choice;
	return choice;
}

template <class T, class is_greater>
void bubble_sort(T items[], int size)
{
	bool swapped = true;
	while (swapped)
	{
		swapped = false;
		for (int i = 0; i < size - 1; i++)
		{
			if (is_greater()(items[i], items[i + 1]))
			{
				swap_(items[i], items[i + 1]);
				swapped = true;
			}
		}
	}
}

template <class T, class is_greater>
void selection_sort(T items[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int low = i;
		for (int j = i + 1; j < size; j++)
		{
			if (is_greater()(items[low], items[j]))
				low = j;
		}
		swap_(items[low], items[i]);
	}
}

template <class T, class is_greater>
void insertion_sort(T items[], int size)
{
	for (int i = 1; i < size; i++)
	{
		T key = items[i];
		int j = i - 1;
		for (; j >= 0 && is_greater()(items[j], key); j--)
			items[j + 1] = items[j];
		items[j + 1] = key;
	}
}

template <class T, class is_greater>
void shell_sort(T items[], int size)
{
	for (int gap = size / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < size; i++)
		{
			T temp = items[i];
			int j = i;
			for (; j >= gap && is_greater()(items[j - gap], temp); j -= gap)
				items[j] = items[j - gap];
			items[j] = temp;
		}
	}
}

template <class T, class is_greater>
void quicksort(T items[], int first, int last)
{
	if (first < last)
	{
		int pivot = partition<T, is_greater>(items, first, last);
		quicksort<T, is_greater>(items, first, pivot - 1);
		quicksort<T, is_greater>(items, pivot, last);
	}
}

template <class T, class is_greater>
int partition(T items[], int first, int last)
{
	int mid = first + (last - first) / 2;
	T pivot_value = items[mid];
	while (first <= last)
	{
		while (is_greater()(pivot_value, items[first]))
			first++;
		while (is_greater()(items[last], pivot_value))
			last--;
		if (first <= last)
		{
			swap_(items[first], items[last]);
			first++;
			last--;
		}
	}
	return first;
}

template <class T, class is_greater>
void merge_sort(T items[], int left, int right)
{
	if (left < right)
	{
		int mid = left + (right - left) / 2;
		merge_sort<T, is_greater>(items, left, mid);
		merge_sort<T, is_greater>(items, mid + 1, right);
		merge<T, is_greater>(items, left, mid, right);
	}
}

template <class T, class is_greater>
void merge(T items[], int left, int mid, int right)
{
	const int left_size = mid - left + 1;
	const int right_size = right - mid;
	T* temp_left = new int[left_size];
	T* temp_right = new int[right_size];

	// copy the data to the temp arrays
	for (int i = 0; i < left_size; i++)
		temp_left[i] = items[left + i];
	for (int j = 0; j < right_size; j++)
		temp_right[j] = items[mid + 1 + j];

	// merge the temp arrays back into the items array
	int L = 0,
		R = 0,
		i = left;
	while (L < left_size && R < right_size)
	{
		if (!is_greater()(temp_left[L], temp_right[R]))
		{
			items[i] = temp_left[L];
			L++;
		}
		else
		{
			items[i] = temp_right[R];
			R++;
		}

		i++;
	}

	// copy the remaining elements of temp_left[], if there are any
	while (L < left_size)
	{
		items[i] = temp_left[L];
		L++;
		i++;
	}

	// copy the remaining elements of temp_right[], if there are any
	while (R < right_size)
	{
		items[i] = temp_right[R];
		R++;
		i++;
	}

	delete[] temp_left;
	delete[] temp_right;
}

template <class T, class is_greater>
void heap_sort(T items[], int size)
{
	// turn the array into a max heap
	for (int i = 0; i < size; i++)
	{
		int j = i;
		while (is_greater()(items[j], items[(j - 1) / 2]))
		{
			swap_(items[j], items[(j - 1) / 2]);
			j = (j - 1) / 2;
		}
	}

	// Sort the array by putting the greatest number at the end, then
	// the second greatest number in the second to last spot, etc.
	int last = size - 1;
	swap_(items[0], items[last]);
	last--;
	while (last > 0)
	{
		// rebuild the heap within the remaining elements
		int parent = 0,
			left_child = 1,
			right_child = 2;
		bool heaping = true;
		while (heaping)
		{
			// find the greater of the two children
			int max;
			if (right_child > last || is_greater()(items[left_child], items[right_child]))
				max = left_child;
			else
				max = right_child;
			if (is_greater()(items[max], items[parent]))
			{
				swap_(items[max], items[parent]);

				// Prepare to check whether further swapping is needed to
				// finish rebuilding the heap.
				parent = max;
				left_child = parent * 2 + 1;
				right_child = parent * 2 + 2;
				if (left_child >= last)
					heaping = false;
			}
			else
				heaping = false;
		}
		swap_(items[0], items[last]);
		last--;
	}
}

template <class T, class are_equal>
int linear_search(T items[], int size, T value)
{
	for (int i = 0; i < size; i++)
	{
		if (are_equal()(items[i], value))
			return i;
	}
	return -1;
}

template <class T, class is_greater, class are_equal>
int binary_search(T items[], int size, T value)
{
	int first = 0;
	while (true)
	{
		int mid = first + (size - first) / 2;
		if (is_greater()(items[mid], value))
			size = mid - 1;
		else if (are_equal()(items[mid], value))
			return mid;
		else
			first = mid + 1;
		if (first > size)
			return -1;
	}
}
