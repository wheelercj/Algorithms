#include <iostream>
#include <ctime>
#include "sorting.h"
using namespace std;


void manual_test()
{
	const int size = 10;
	int numbers[size];
	const int max_value = 100;
	randomize(numbers, size, max_value);

	cout << "\n Unsorted array: ";
	print(numbers, size);

	sort_array(numbers, size);

	cout << "\n Sorted array: ";
	print(numbers, size);

	cout << "\n What value are you looking for? ";
	int value;
	cin >> value;

	int result = search_array(numbers, size, value);

	if (result == -1)
		cout << "\n Error: number not found.";
	else
		cout << "\n The value is in element " << result;
}

void automatic_test()
{
	const int size = 10;
	int numbers[size];
	const int max_value = 100;
	cout << "\n Repetitions: ";
	int reps;
	cin >> reps;
	int reps_copy = reps;
	try
	{
		switch (print_sort_menu())
		{
		case 1:
			for (; reps_copy > 0; reps_copy--)
			{
				randomize(numbers, size, max_value);
				bubble_sort(numbers, size);
				assert_sorted(numbers, size);
			}
			break;
		case 2:
			for (; reps_copy > 0; reps_copy--)
			{
				randomize(numbers, size, max_value);
				selection_sort(numbers, size);
				assert_sorted(numbers, size);
			}
			break;
		case 3:
			for (; reps_copy > 0; reps_copy--)
			{
				randomize(numbers, size, max_value);
				insertion_sort(numbers, size);
				assert_sorted(numbers, size);
			}
			break;
		case 4:
			for (; reps_copy > 0; reps_copy--)
			{
				randomize(numbers, size, max_value);
				shell_sort(numbers, size);
				assert_sorted(numbers, size);
			}
			break;
		case 5:
			for (; reps_copy > 0; reps_copy--)
			{
				randomize(numbers, size, max_value);
				quicksort(numbers, 0, size - 1);
				assert_sorted(numbers, size);
			}
			break;
		case 6:
			for (; reps_copy > 0; reps_copy--)
			{
				randomize(numbers, size, max_value);
				merge_sort(numbers, 0, size - 1);
				assert_sorted(numbers, size);
			}
			break;
		case 7:
			for (; reps_copy > 0; reps_copy--)
			{
				randomize(numbers, size, max_value);
				heap_sort(numbers, size);
				assert_sorted(numbers, size);
			}
			break;
		default:
			cout << "\n Error: invalid sorting algorithm choice.";
		}
		cout << "\n Sorted " << reps << " times successfully.";
	}
	catch (std::invalid_argument e)
	{
		cout << "\n Error: the numbers did not sort successfully.";
	}
}

template <class T>
void print(T numbers[], int size)
{
	for (int i = 0; i < size; i++)
		cout << " " << numbers[i];
}

/* Throws std::invalid_argument if the given array is not sorted. */
template<class T>
void assert_sorted(T numbers[], int size)
{
	for (int i = 1; i < size; i++)
	{
		if (numbers[i - 1] > numbers[i])
			throw std::invalid_argument("The numbers are not sorted.");
	}
}

template <class T>
inline void swap_(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

// fill the array with random numbers
template <class T>
void randomize(T numbers[], int size, T max)
{
	srand((unsigned)time(0));
	for (int i = 0; i < size; i++)
		numbers[i] = 1 + rand() % max;
}

template <class T>
void sort_array(T numbers[], int size)
{
	switch (print_sort_menu())
	{
	case 1:
		bubble_sort(numbers, size);
		break;
	case 2:
		selection_sort(numbers, size);
		break;
	case 3:
		insertion_sort(numbers, size);
		break;
	case 4:
		shell_sort(numbers, size);
		break;
	case 5:
		quicksort(numbers, 0, size - 1);
		break;
	case 6:
		merge_sort(numbers, 0, size - 1);
		break;
	case 7:
		heap_sort(numbers, size);
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

template <class T>
int search_array(T numbers[], int size, T value)
{
	switch (print_search_menu())
	{
	case 1:
		return linear_search(numbers, size, value);
	case 2:
		return binary_search(numbers, size, value);
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

template <class T>
void bubble_sort(T numbers[], int size)
{
	bool swapped = true;

	while (swapped)
	{
		swapped = false;

		for (int i = 0; i < size - 1; i++)
		{
			if (numbers[i] > numbers[i + 1])
			{
				swapped = true;
				swap_(numbers[i], numbers[i + 1]);
			}
		}
	}
}

template <class T>
void selection_sort(T numbers[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int low = i;

		for (int j = i + 1; j < size; j++)
		{
			if (numbers[j] < numbers[low])
				low = j;
		}

		swap_(numbers[low], numbers[i]);
	}
}

template <class T>
void insertion_sort(T numbers[], int size)
{
	for (int i = 1; i < size; i++)
	{
		T key = numbers[i];

		int j = i - 1;
		for (; j >= 0 && key < numbers[j]; j--)
			numbers[j + 1] = numbers[j];

		numbers[j + 1] = key;
	}
}

template<class T>
void shell_sort(T numbers[], int size)
{
	for (int gap = size / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < size; i++)
		{
			T temp = numbers[i];
			int j = i;
			for (; j >= gap && numbers[j - gap] > temp; j -= gap)
				numbers[j] = numbers[j - gap];
			numbers[j] = temp;
		}
	}
}

template <class T>
void quicksort(T numbers[], int first, int last)
{
	if (first < last)
	{
		int pivot = partition(numbers, first, last);
		quicksort(numbers, first, pivot - 1);
		quicksort(numbers, pivot, last);
	}
}

template <class T>
int partition(T numbers[], int first, int last)
{
	T pivot_value = numbers[first + (last - first) / 2];
	// `first+(last-first)/2` is the same as `(first+last)/2`, but cannot overflow

	while (first <= last)
	{
		while (numbers[first] < pivot_value)
			first++;
		while (numbers[last] > pivot_value)
			last--;
		if (first <= last)
		{
			swap_(numbers[first], numbers[last]);
			first++;
			last--;
		}
	}

	return first;
}

template <class T>
void merge_sort(T numbers[], int left, int right)
{
	if (left < right)
	{
		int mid = left + (right - left) / 2;

		merge_sort(numbers, left, mid);
		merge_sort(numbers, mid + 1, right);

		merge(numbers, left, mid, right);
	}
}

template <class T>
void merge(T numbers[], int left, int mid, int right)
{
	const int left_size = mid - left + 1,
		right_size = right - mid;
	
	T* temp_left = new int[left_size];
	T* temp_right = new int[right_size];

	// copy the data to the temp arrays
	for (int i = 0; i < left_size; i++)
		temp_left[i] = numbers[left + i];
	for (int j = 0; j < right_size; j++)
		temp_right[j] = numbers[mid + 1 + j];

	// merge the temp arrays back into the numbers array
	int L = 0,
		R = 0,
		i = left;
	while (L < left_size && R < right_size)
	{
		if (temp_left[L] <= temp_right[R])
		{
			numbers[i] = temp_left[L];
			L++;
		}
		else
		{
			numbers[i] = temp_right[R];
			R++;
		}

		i++;
	}

	// copy the remaining elements of temp_left[], if there are any
	while (L < left_size)
	{
		numbers[i] = temp_left[L];
		L++;
		i++;
	}

	// copy the remaining elements of temp_right[], if there are any
	while (R < right_size)
	{
		numbers[i] = temp_right[R];
		R++;
		i++;
	}

	delete[] temp_left;
	delete[] temp_right;
}

template<class T>
void heap_sort(T numbers[], int size)
{
	// turn the array into a max heap
	for (int i = 0; i < size; i++)
	{
		int j = i;
		while (numbers[j] > numbers[(j - 1) / 2])
		{
			swap_(numbers[j], numbers[(j - 1) / 2]);
			j = (j - 1) / 2;
		}
	}

	// Sort the array by putting the greatest number at the end, then
	// the second greatest number in the second to last spot, etc.
	int last = size - 1;
	swap_(numbers[0], numbers[last]);
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
			if (right_child > last || numbers[left_child] > numbers[right_child])
				max = left_child;
			else
				max = right_child;
			
			// if the child is greater than the parent
			if (numbers[max] > numbers[parent])
			{
				// swap the child and the parent
				swap_(numbers[max], numbers[parent]);

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

		swap_(numbers[0], numbers[last]);
		last--;
	}
}

template <class T>
int linear_search(T numbers[], int size, T value)
{
	for (int i = 0; i < size; i++)
	{
		if (numbers[i] == value)
			return i;
	}

	return -1;
}

template <class T>
int binary_search(T numbers[], int size, T value)
{
	int first = 0;

	while (true)
	{
		int mid = first + (size - first) / 2;
		// `first+(size-first)/2` is the same as `(first+size)/2`, but cannot overflow

		if (numbers[mid] > value)
			size = mid - 1;
		else if (numbers[mid] < value)
			first = mid + 1;
		else
			return mid;
		if (first > size)
			return -1;
	}
}
