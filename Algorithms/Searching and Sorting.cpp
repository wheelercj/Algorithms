#include <iostream>
#include <ctime>
using namespace std;

// Big-O Cheat Sheet: https://www.bigocheatsheet.com/
// Why quicksort is better than other sorting algorithms in practice: https://cs.stackexchange.com/questions/3/why-is-quicksort-better-than-other-sorting-algorithms-in-practice

void print(int[], int);
void swap(int&, int&);
void randomize(int[], int);

void sort_array(int[], int);
int print_sort_menu();
int search_array(int[], int, int);
int print_search_menu();

void bubble_sort(int[], int);
void selection_sort(int[], int);
void insertion_sort(int[], int);
void quicksort(int[], int, int);
int partition(int[], int, int);
void merge_sort(int[], int, int);
void merge(int[], int, int, int);

int linear_search(int[], int, int);
int binary_search(int[], int, int);

int main()
{
	const int size = 10;
	int numbers[size];
	randomize(numbers, size);

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

	cout << endl;
	system("pause");
	return 0;
}

void print(int numbers[], int size)
{
	for (int i = 0; i < size; i++)
		cout << " " << numbers[i];
}

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

// fill the array with random numbers
void randomize(int numbers[], int size)
{
	srand((unsigned)time(0));
	const int min = 1, max = 100;
	for (int i = 0; i < size; i++)
		numbers[i] = min + rand() % (max - min + 1);
}

void sort_array(int numbers[], int size)
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
		quicksort(numbers, 0, size - 1);
		break;
	case 5:
		merge_sort(numbers, 0, size - 1);
		break;
	default:
		cout << "\n Error";
	}
}

int print_sort_menu()
{
	int choice;
	cout << "\n Which sorting algorithm do you want to use?"
		"\n 1. Bubble sort"
		"\n 2. Selection sort"
		"\n 3. Insertion sort"
		"\n 4. Quicksort"
		"\n 5. Merge sort"
		"\n> ";
	cin >> choice;
	return choice;
}

int search_array(int numbers[], int size, int value)
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

void bubble_sort(int numbers[], int size)
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
				swap(numbers[i], numbers[i + 1]);
			}
		}
	}
}

void selection_sort(int numbers[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int low = i;

		for (int j = i + 1; j < size; j++)
		{
			if (numbers[j] < numbers[low])
				low = j;
		}

		swap(numbers[low], numbers[i]);
	}
}

void insertion_sort(int numbers[], int size)
{
	for (int i = 1; i < size; i++)
	{
		int key = numbers[i];

		int j = i - 1;
		for (; j >= 0 && key < numbers[j]; j--)
			numbers[j + 1] = numbers[j];

		numbers[j + 1] = key;
	}
}

void quicksort(int numbers[], int first, int last)
{
	if (first < last)
	{
		int pivot = partition(numbers, first, last);
		quicksort(numbers, first, pivot - 1);
		quicksort(numbers, pivot, last);
	}
}

int partition(int numbers[], int first, int last)
{
	int pivot_value = numbers[first + (last - first) / 2];
	// `first+(last-first)/2` is the same as `(first+last)/2`, but cannot overflow

	while (first <= last)
	{
		while (numbers[first] < pivot_value)
			first++;
		while (numbers[last] > pivot_value)
			last--;
		if (first <= last)
		{
			swap(numbers[first], numbers[last]);
			first++;
			last--;
		}
	}

	return first;
}

void merge_sort(int numbers[], int left, int right)
{
	if (left < right)
	{
		int mid = left + (right - left) / 2;

		merge_sort(numbers, left, mid);
		merge_sort(numbers, mid + 1, right);

		merge(numbers, left, mid, right);
	}
}

void merge(int numbers[], int left, int mid, int right)
{
	const int left_size = mid - left + 1,
		right_size = right - mid;
	
	int* temp_left = new int[left_size];
	int* temp_right = new int[right_size];

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

int linear_search(int numbers[], int size, int value)
{
	for (int i = 0; i < size; i++)
	{
		if (numbers[i] == value)
			return i;
	}

	return -1;
}

int binary_search(int numbers[], int size, int value)
{
	int first = 0;

	while (true)
	{
		int mid = first + (size - first) / 2;

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
