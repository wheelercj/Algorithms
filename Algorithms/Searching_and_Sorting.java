import java.util.*;

public class Searching_and_Sorting {

    public static void main(String[] args) {
        final int SIZE = 10;
        final int MIN_VALUE = 1;
        final int MAX_VALUE = 100;
        int[] numbers = create_random_array(SIZE, MIN_VALUE, MAX_VALUE);

        System.out.print("Unsorted array: ");
        print(numbers);
        System.out.println();

        sort_array(numbers);

        System.out.print("Sorted array: ");
        print(numbers);
        System.out.println();

        System.out.print("What value are you looking for? ");
        Scanner scanner = new Scanner(System.in);
        int value = scanner.nextInt();

        int result = search_array(numbers, value);

        if (result == -1)
            System.out.println("Error: number not found");
        else
            System.out.println("The value is in element " + result);
    }

    public static void print(int[] numbers) {
        for (int number : numbers) {
            System.out.print(number);
            System.out.print(" ");
        }
    }

    public static int[] create_random_array(final int SIZE, final int MIN_VALUE, final int MAX_VALUE) {
        int[] numbers = new int[SIZE];
        for (int i = 0; i < numbers.length; i++)
            numbers[i] = (int) (MIN_VALUE + Math.random() * (MAX_VALUE - MIN_VALUE + 1));
        return numbers;
    }

    public static void sort_array(int[] numbers) {
        boolean invalid_input = true;
        while (invalid_input) {
            invalid_input = false;
            switch (print_sort_menu()) {
                case 1 -> bubble_sort(numbers);
                case 2 -> selection_sort(numbers);
                case 3 -> insertion_sort(numbers);
                case 4 -> quicksort(numbers, 0, numbers.length - 1);
                case 5 -> merge_sort(numbers, 0, numbers.length - 1);
                case 6 -> heap_sort(numbers);
                default -> {
                    System.out.println("Error");
                    invalid_input = true;
                }
            }
        }
    }

    public static int print_sort_menu() {
        System.out.println("Which sorting algorithm do you want to use?");
        System.out.println("1. bubble sort");
        System.out.println("2. selection sort");
        System.out.println("3. insertion sort");
        System.out.println("4. quicksort");
        System.out.println("5. merge sort");
        System.out.println("6. heap sort");
        System.out.print("> ");
        Scanner scanner = new Scanner(System.in);
        return scanner.nextInt();
    }

    public static int search_array(int[] numbers, int value) {
        while (true) {
            switch (print_search_menu()) {
                case 1:
                    return linear_search(numbers, value);
                case 2:
                    return binary_search(numbers, value);
                default:
                    System.out.println("Error");
            }
        }
    }

    public static int print_search_menu() {
        System.out.println("Which searching algorithm do you want to use?");
        System.out.println("1. linear search");
        System.out.println("2. binary search");
        System.out.print("> ");
        Scanner scanner = new Scanner(System.in);
        return scanner.nextInt();
    }

    public static void bubble_sort(int[] numbers) {
        boolean swapped = true;
        while (swapped) {
            swapped = false;
            for (int i = 0; i < numbers.length - 1; i++) {
                if (numbers[i] > numbers[i + 1]) {
                    swapped = true;
                    int temp = numbers[i];
                    numbers[i] = numbers[i + 1];
                    numbers[i + 1] = temp;
                }
            }
        }
    }

    public static void selection_sort(int[] numbers) {
        if (numbers.length == 0)
            return;
        for (int i = 0; i < numbers.length - 1; i++) {
            int min_index = i;
            for (int j = i + 1; j < numbers.length; j++) {
                if (numbers[min_index] > numbers[j])
                    min_index = j;
            }
            int temp = numbers[i];
            numbers[i] = numbers[min_index];
            numbers[min_index] = temp;
        }
    }

    public static void insertion_sort(int[] numbers) {
        for (int i = 1; i < numbers.length; i++) {
            int key = numbers[i];
            int j = i - 1;
            for (; j >= 0 && key < numbers[j]; j--)
                numbers[j + 1] = numbers[j];
            numbers[j + 1] = key;
        }
    }

    public static void quicksort(int[] numbers, int first, int last) {
        if (first < last) {
            int pivot = partition(numbers, first, last);
            quicksort(numbers, first, pivot - 1);
            quicksort(numbers, pivot, last);
        }
    }

    public static int partition(int[] numbers, int first, int last) {
        int pivot_value = numbers[first + (last - first) / 2];
        while (first <= last) {
            while (numbers[first] < pivot_value)
                first++;
            while (numbers[last] > pivot_value)
                last--;
            if (first <= last) {
                int temp = numbers[first];
                numbers[first] = numbers[last];
                numbers[last] = temp;
                first++;
                last--;
            }
        }
        return first;
    }

    public static void merge_sort(int[] numbers, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            merge_sort(numbers, left, mid);
            merge_sort(numbers, mid + 1, right);
            merge(numbers, left, mid, right);
        }
    }

    public static void merge(int[] numbers, int left, int mid, int right) {
        final int LEFT_SIZE = mid - left + 1;
        final int RIGHT_SIZE = right - mid;
        int[] temp_left = new int[LEFT_SIZE];
        int[] temp_right = new int[RIGHT_SIZE];

        // copy the data to the temp arrays
        System.arraycopy(numbers, left, temp_left, 0, LEFT_SIZE);
        for (int i = 0; i < RIGHT_SIZE; i++)
            temp_right[i] = numbers[mid + 1 + i];

        // merge the temp arrays back into the numbers array
        int L = 0;
        int R = 0;
        int i = left;
        while (L < LEFT_SIZE && R < RIGHT_SIZE) {
            if (temp_left[L] <= temp_right[R]) {
                numbers[i] = temp_left[L];
                L++;
            }
            else {
                numbers[i] = temp_right[R];
                R++;
            }
            i++;
        }
        while (L < LEFT_SIZE) {
            numbers[i] = temp_left[L];
            L++;
            i++;
        }
        while (R < RIGHT_SIZE) {
            numbers[i] = temp_right[R];
            R++;
            i++;
        }
    }

    public static void heap_sort(int[] numbers) {
        // turn the array into a max heap
        for (int i = 0; i < numbers.length; i++) {
            int j = i;
            while (numbers[j] > numbers[(j - 1) / 2]) {
                int temp = numbers[j];
                numbers[j] = numbers[(j - 1) / 2];
                numbers[(j - 1) / 2] = temp;
                j = (j - 1) / 2;
            }
        }
        // Sort the array by putting the greatest number at the end, then
        // the second-greatest number in the second to last spot, etc.
        int last = numbers.length - 1;
        int temp = numbers[0];
        numbers[0] = numbers[last];
        numbers[last] = temp;
        last--;

        while (last > 0) {
            // rebuild the heap with the remaining elements
            int parent = 0;
            int left_child = 1;
            int right_child = 2;
            boolean heaping = true;
            while (heaping) {
                // find the greater of the two children
                int max;
                if (right_child > last || numbers[left_child] > numbers[right_child])
                    max = left_child;
                else
                    max = right_child;

                // if the child is greater than the parent
                if (numbers[max] > numbers[parent]) {
                    // swap the child and the parent
                    int temp2 = numbers[max];
                    numbers[max] = numbers[parent];
                    numbers[parent] = temp2;

                    // Prepare to check whether further swapping is needed to finish rebuilding the heap.
                    parent = max;
                    left_child = parent * 2 + 1;
                    right_child = parent * 2 + 2;
                    if (left_child >= last)
                        heaping = false;
                }
                else
                    heaping = false;
            }
            int temp2 = numbers[0];
            numbers[0] = numbers[last];
            numbers[last] = temp2;
            last--;
        }
    }

    public static int linear_search(int[] numbers, int value) {
        for (int i = 0; i < numbers.length; i++) {
            if (numbers[i] == value)
                return i;
        }
        return -1;
    }

    public static int binary_search(int[] numbers, int value) {
        int first = 0;
        int last = numbers.length;
        while (first <= last) {
            int mid = first + (last - first) / 2;
            if (numbers[mid] == value)
                return mid;
            if (numbers[mid] < value)
                first = mid + 1;
            else if (numbers[mid] > value)
                last = mid - 1;
        }
        return -1;
    }
}
