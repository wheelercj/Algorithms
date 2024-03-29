# Algorithms

Examples of various algorithms and data structures implemented and [thoroughly tested](https://github.com/wheelercj/Algorithms/tree/main/tests) in various languages. [Here](https://wheelercj.github.io/notes/pages/20210620152751.html) are other resources that helped me learn about algorithms.

## searching and sorting algorithms ([C++](https://github.com/wheelercj/Algorithms/blob/main/Algorithms/sorting.cpp) and [Java](https://github.com/wheelercj/Algorithms/blob/main/Algorithms/sorting.java))

* bubble sort
* selection sort
* insertion sort
* shell sort
* quicksort
* merge sort
* heap sort
* linear search
* binary search
* [2D binary search](https://github.com/wheelercj/Algorithms/blob/main/Algorithms/2d_search.java)

## data structures

* a generic **[linked list](https://github.com/wheelercj/Algorithms/tree/main/Algorithms/LinkedList.h)** class implemented in C++
    * uses unique pointers and `std::make_unique` to make memory leaks nearly impossible
    * upholds [The Rule of 5](https://www.codementor.io/@sandesh87/the-rule-of-five-in-c-1pdgpzb04f) and [RAII principles](https://en.cppreference.com/w/cpp/language/raii)
    * follows much of the [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) by Bjarne Stroustrup & Herb Sutter
    * has all the methods one would expect as well as `reverse`, `map`, `filter`, and `reduce`.
    * requires C++17 or newer
* [**trees**](https://github.com/wheelercj/Algorithms/blob/main/Algorithms/go/main.go) implemented in Go
    * random binary tree generation
    * random binary search tree (BST) generation
    * tree traversals (inorder, preorder, postorder, BFS, DFS)
* **graphs**
    * Dijkstra's Shortest Path implemented in [Python](https://github.com/wheelercj/Algorithms/tree/main/Algorithms/dijkstra.py) and [C++](https://github.com/wheelercj/Algorithms/tree/main/Algorithms/dijkstra.h)
