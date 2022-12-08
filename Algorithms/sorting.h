#pragma once

void manual_sorting_test();
template <class T> void print(T[], int);
template <class T> inline void swap_(T&, T&);
void randomize(int[], int, int);
template <class T, class is_greater> void prompt_and_sort_array(T[], int);
int print_sort_menu();
template <class T, class is_greater, class are_equal> int search_array(T[], int, T);
int print_search_menu();

template <class T, class is_greater> void bubble_sort(T[], int);
template <class T, class is_greater> void selection_sort(T[], int);
template <class T, class is_greater> void insertion_sort(T[], int);
template <class T, class is_greater> void shell_sort(T[], int);
template <class T, class is_greater> void quicksort(T[], int, int);
template <class T, class is_greater> int partition(T[], int, int);
template <class T, class is_greater> void merge_sort(T[], int, int);
template <class T, class is_greater> void merge(T[], int, int, int);
template <class T, class is_greater> void heap_sort(T[], int);

template <class T, class are_equal> int linear_search(T[], int, T);
template <class T, class is_greater, class are_equal> int binary_search(T[], int, T);
