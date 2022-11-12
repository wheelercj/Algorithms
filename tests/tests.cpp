#include "pch.h"
#include "CppUnitTest.h"
#include "../Algorithms/LinkedList.h"
#include "../Algorithms/LinkedListNode.h"
#include "../Algorithms/sorting.h"
#include "../Algorithms/sorting.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

int square(int number)
{
	return number * number;
}

bool is_even(int number)
{
	return number % 2 == 0;
}

int add(int a, int b)
{
	return a + b;
}

namespace tests
{

	TEST_CLASS(sorting)
	{
	public:

		wstring format_int_array(int arr[], int size)
		{
			wstring s = L"";
			for (int i = 0; i < size; i++)
			{
				s += std::to_wstring(arr[i]);
				if (i < size - 1)
					s += L", ";
			}
			s += L".";
			return s;
		}

		template<class T>
		void assert_sorted(T arr[], int size)
		{
			for (int i = 1; i < size; i++)
				Assert::IsTrue(
					arr[i - 1] <= arr[i],
					(
						L"\n" + std::to_wstring(arr[i - 1]) + L" and " + std::to_wstring(arr[i]) + L" should be swapped."
						L"\n entire array: " + format_int_array(arr, size)
					).c_str()
				);
		}

		// Throws std::logic_error if the array is not sorted.
		// Does nothing otherwise.
		template<class T>
		void require_sorted(T arr[], const int size)
		{
			for (int i = 1; i < size; i++)
			{
				if (arr[i - 1] > arr[i])
					throw std::logic_error("The array is not sorted");
			}
		}

		void fail_sort()
		{
			const int size = 10;
			int numbers[size];
			const int max_value = 10;
			while (true)
			{
				randomize(numbers, size, max_value);
				bubble_sort(numbers, size);
				if (numbers[0] == numbers[9])
					continue;
				swap_(numbers[0], numbers[9]);
				require_sorted(numbers, size);
			}
		}

		TEST_METHOD(test_failing_sort)
		{
			auto f = [&] { fail_sort(); };
			Assert::ExpectException<std::logic_error>(f);
		}

		TEST_METHOD(test_bubble_sort)
		{
			const int size = 100;
			int numbers[size];
			const int max_value = 100;
			for (int i = 0; i < 100; i++)
			{
				randomize(numbers, size, max_value);
				bubble_sort(numbers, size);
				assert_sorted(numbers, size);
			}
		}

		TEST_METHOD(test_selection_sort)
		{
			const int size = 100;
			int numbers[size];
			const int max_value = 100;
			for (int i = 0; i < 100; i++)
			{
				randomize(numbers, size, max_value);
				selection_sort(numbers, size);
				assert_sorted(numbers, size);
			}
		}

		TEST_METHOD(test_insertion_sort)
		{
			const int size = 100;
			int numbers[size];
			const int max_value = 100;
			for (int i = 0; i < 100; i++)
			{
				randomize(numbers, size, max_value);
				insertion_sort(numbers, size);
				assert_sorted(numbers, size);
			}
		}

		TEST_METHOD(test_shell_sort)
		{
			const int size = 100;
			int numbers[size];
			const int max_value = 100;
			for (int i = 0; i < 100; i++)
			{
				randomize(numbers, size, max_value);
				shell_sort(numbers, size);
				assert_sorted(numbers, size);
			}
		}

		TEST_METHOD(test_quicksort)
		{
			const int size = 100;
			int numbers[size];
			const int max_value = 100;
			for (int i = 0; i < 100; i++)
			{
				randomize(numbers, size, max_value);
				quicksort(numbers, 0, size - 1);
				assert_sorted(numbers, size);
			}
		}

		TEST_METHOD(test_merge_sort)
		{
			const int size = 100;
			int numbers[size];
			const int max_value = 100;
			for (int i = 0; i < 100; i++)
			{
				randomize(numbers, size, max_value);
				merge_sort(numbers, 0, size - 1);
				assert_sorted(numbers, size);
			}
		}

		TEST_METHOD(test_heap_sort)
		{
			const int size = 100;
			int numbers[size];
			const int max_value = 100;
			for (int i = 0; i < 100; i++)
			{
				randomize(numbers, size, max_value);
				heap_sort(numbers, size);
				assert_sorted(numbers, size);
			}
		}

	};

	TEST_CLASS(linked_list)
	{
	public:

		TEST_METHOD(test_default_constructor)
		{
			LinkedList<int> list;
		}

		TEST_METHOD(test_size_of_empty_list)
		{
			LinkedList<int> list;
			Assert::AreEqual(size_t(0), list.size());
		}

		TEST_METHOD(test_initializion)
		{
			LinkedList<int> list(8);
		}

		TEST_METHOD(test_single_equality_comparison)
		{
			LinkedList<int> list1(8);
			LinkedList<int> list2(8);
			Assert::IsTrue(list1 == list2);
		}

		TEST_METHOD(test_inequality_comparison)
		{
			LinkedList<int> list1(8);
			LinkedList<int> list2(8);
			list2.append(9);
			Assert::IsTrue(list1 != list2);
		}

		TEST_METHOD(test_single_equality_comparison_with_strings)
		{
			LinkedList<std::string> list1("hello");
			LinkedList<std::string> list2("hello");
			Assert::IsTrue(list1 == list2);
		}

		TEST_METHOD(test_multi_equality_comparison)
		{
			LinkedList<int> list1(8);
			list1.append(9);
			LinkedList<int> list2(8);
			list2.append(9);
			Assert::IsTrue(list1 == list2);
		}

		TEST_METHOD(test_copy_constructor_and_equality_comparison)
		{
			LinkedList<int> list1(8);
			LinkedList<int> list2(list1);
			Assert::IsTrue(list1 == list2);
		}

		TEST_METHOD(test_append_and_square_brackets)
		{
			LinkedList<int> list;
			list.append(1);
			list.append(2);
			list.append(3);
			list.append(4);
			Assert::AreEqual(2, list[1]);
			Assert::AreEqual(4, list[3]);
			list[3] = 5;
			Assert::AreEqual(2, list[1]);
			Assert::AreEqual(5, list[3]);
		}

		TEST_METHOD(test_square_brackets_out_of_range)
		{
			LinkedList<int> list(2);
			auto f = [&] { list[83]; };
			Assert::ExpectException<std::out_of_range>(f);
		}

		TEST_METHOD(test_square_brackets_negative_index)
		{
			LinkedList<int> list(2);
			auto f = [&] { list[-10]; };
			Assert::ExpectException<std::out_of_range>(f);
		}
		
		TEST_METHOD(test_insert_out_of_range)
		{
			LinkedList<std::string> list;
			auto f = [&] { list.insert("hi", 3); };
			Assert::ExpectException<std::out_of_range>(f);
		}

		TEST_METHOD(test_insert_at_negative_index)
		{
			LinkedList<std::string> list;
			auto f = [&] { list.insert("hi", -3); };
			Assert::ExpectException<std::out_of_range>(f);
		}

		TEST_METHOD(test_append_and_insert)
		{
			LinkedList<int> list;
			list.append(1);
			list.append(2);
			list.append(3);
			list.append(4);
			Assert::AreEqual(2, list[1]);
			Assert::AreEqual(3, list[2]);
			Assert::AreEqual(4, list[3]);
			list.insert(10, 2);
			Assert::AreEqual(2, list[1]);
			Assert::AreEqual(10, list[2]);
			Assert::AreEqual(4, list[4]);
		}

		TEST_METHOD(test_remove_out_of_range)
		{
			LinkedList<std::string> list;
			auto f = [&] { list.remove(3); };
			Assert::ExpectException<std::out_of_range>(f);
		}

		TEST_METHOD(test_remove_at_negative_index)
		{
			LinkedList<std::string> list;
			auto f = [&] { list.remove(-3); };
			Assert::ExpectException<std::out_of_range>(f);
		}

		TEST_METHOD(test_append_and_remove)
		{
			LinkedList<int> list;
			list.append(1);
			list.append(2);
			list.append(3);
			list.append(4);
			Assert::AreEqual(3, list[2]);
			Assert::AreEqual(3, list.remove(2));
			Assert::AreEqual(4, list[2]);
			Assert::AreEqual(2, list[1]);
		}

		TEST_METHOD(test_append_and_size)
		{
			LinkedList<int> list;
			list.append(1);
			list.append(2);
			list.append(3);
			list.append(4);
			Assert::AreEqual(size_t(4), list.size());
			Assert::AreEqual(size_t(4), list.length());
		}

		TEST_METHOD(test_append_clear_and_size)
		{
			LinkedList<int> list;
			list.append(1);
			list.append(2);
			list.append(3);
			list.append(4);
			Assert::AreEqual(size_t(4), list.size());
			list.clear();
			Assert::AreEqual(size_t(0), list.size());
			list.clear();
			Assert::AreEqual(size_t(0), list.size());
		}

		/*TEST_METHOD(test_append_and_iterator)
		{
			LinkedList<int> list;
			list.append(1);
			list.append(2);
			list.append(3);
			list.append(4);
			LinkedList<int>::iterator it;
			for (it = list.begin(); it != list.end(); it++)
			{
				*it += 3;
			}
			Assert::AreEqual(4, list[0]);
			Assert::AreEqual(5, list[1]);
			Assert::AreEqual(6, list[2]);
			Assert::AreEqual(7, list[3]);
		}*/

		TEST_METHOD(test_append_and_find)
		{
			LinkedList<int> list;
			list.append(1);
			list.append(2);
			list.append(3);
			list.append(4);
			Assert::AreEqual(size_t(2), *list.find(3));
			Assert::AreEqual(size_t(0), *list.find(1));
			Assert::IsFalse(bool(list.find(5)));
		}

		TEST_METHOD(test_append_map_and_square_brackets)
		{
			LinkedList<int> list;
			list.append(1);
			list.append(2);
			list.append(3);
			list.append(4);
			list.map(square);
			Assert::AreEqual(4, list[1]);
			Assert::AreEqual(16, list[3]);
		}

		TEST_METHOD(test_append_filter_and_size)
		{
			LinkedList<int> list;
			list.append(1);
			list.append(2);
			list.append(3);
			list.append(4);
			list.append(5);
			Assert::AreEqual(size_t(5), list.size());
			list.filter(is_even);
			Assert::AreEqual(size_t(2), list.size());
		}

		TEST_METHOD(test_append_and_reduce)
		{
			LinkedList<int> list;
			list.append(1);
			list.append(2);
			list.append(3);
			list.append(4);
			list.append(5);
			Assert::AreEqual(15, list.reduce(add));
			Assert::AreEqual(size_t(5), list.size());
		}

	};
}