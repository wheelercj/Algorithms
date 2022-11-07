#pragma once

void manual_test();
void automatic_test();
template <class T> void print(T[], int);
template <class T> void assert_sorted(T[], int);
template <class T> inline void swap_(T&, T&);
template <class T> void randomize(T[], int, T);
template <class T> void sort_array(T[], int);
int print_sort_menu();
template <class T> int search_array(T[], int, T);
int print_search_menu();

template <class T> void bubble_sort(T[], int);
template <class T> void selection_sort(T[], int);
template <class T> void insertion_sort(T[], int);
template <class T> void shell_sort(T[], int);
template <class T> void quicksort(T[], int, int);
template <class T> int partition(T[], int, int);
template <class T> void merge_sort(T[], int, int);
template <class T> void merge(T[], int, int, int);
template <class T> void heap_sort(T[], int);

template <class T> int linear_search(T[], int, T);
template <class T> int binary_search(T[], int, T);
