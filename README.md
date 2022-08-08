# ft_containers

This [42](https://42.fr/en/homepage/) project aims to make us learn and understand how some [STL](https://en.wikipedia.org/wiki/Standard_Template_Library) containers work and reverse engineer it to make our own implementation alongside their [iterators](https://en.wikipedia.org/wiki/Iterator). We need to stick to C++ 98 only, even if obsolete. See below the list of containers implemented:

- `vector`: sequence containers representing arrays that can change in size
- `map`: associative containers that store elements formed by a combination of a key value and a mapped value, following a specific order
- `stack`: a type of container adaptor, specifically designed to operate in a LIFO context (last-in first-out), where elements are inserted and extracted only from one end of the container

We must to use a [self-balancing binary search tree](https://en.wikipedia.org/wiki/Self-balancing_binary_search_tree) in our `map` implementation. Original `map` container from STL uses a [Red-Black Tree](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree) as its inner data structure. I decided to use an [AVL Tree](https://en.wikipedia.org/wiki/AVL_tree) because it seemed easier to implement at first glance. Using an AVL will reduce speed at both insertion and removal (due to rotations for balancing), but it should find elements quicker.

I also made a [tester](https://github.com/valentinllpz/containers_unit_tests) for this project.

## 🧭 Usage

1. Clone this repo and access it with `cd`
2. `cd container_tests` and use `./run_tests.sh`
3. Feel free to use your own tests

## 📚 Ressources

- [cplusplus.com](https://cplusplus.com/)
- [cppreference](https://en.cppreference.com/)
- [Writing a custom iterator in modern C++](https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp)
- [How to implement our own Vector Class in C++?](https://www.geeksforgeeks.org/how-to-implement-our-own-vector-class-in-c/)
- [AVL Trees](https://cours.etsmtl.ca/SEG/FHenri/inf145/Suppl%C3%A9ments/arbres%20AVL.htm)
- [What is AVL tree Data structure ?](https://simplesnippets.tech/what-is-avl-tree-data-structure-all-avl-operations-with-full-code/)
