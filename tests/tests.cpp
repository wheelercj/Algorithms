#include "pch.h"
#include "CppUnitTest.h"
#include "../Algorithms/sorting.h"
#include "../Algorithms/sorting.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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

		// Raises std::logic_error if the array is not sorted.
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
}
