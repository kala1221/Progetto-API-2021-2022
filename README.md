# API Project 2021-2022
Final Exam of Algorithms and Principles of Computer Science - Academic Year 2021-2022
Grade: 30/30 with honors

In this project, the main objective was to implement a word-guessing game that is both time-efficient and space-efficient. To achieve this, I carefully selected the appropriate data structures and optimized the algorithms.

## Data Structures Used:
Binary Search Tree (BST):

## Purpose: The BST is used to store and manage the vocabulary of allowable words efficiently.
##Advantages:
Allows for quick insertion and search operations, typically O(log n) on average.
Since the vocabulary can be large, using a BST helps in keeping these operations fast.
Implementation Details:
Each node in the BST contains a word from the vocabulary.
Nodes are arranged lexicographically to facilitate quick searches.
Doubly Linked List:

## Purpose: The nodes of the BST are also part of a doubly linked list, which maintains the list of words that have passed the filtering based on the clues provided so far in the game.
##Advantages:
Efficient addition and removal of nodes from the list.
Maintains an ordered sequence of possible words that can be quickly traversed and updated.
Implementation Details:
Each node contains pointers to the next and previous nodes in the list (listainternasucc and listainternaprec).
This list helps in narrowing down the possible words after each guess without having to traverse the entire BST.
## Algorithm Optimization:
### Time Complexity:

All functions are designed to have time complexities that do not exceed O(n²).
Key operations such as insertion, search, and filtering are optimized to run efficiently, often in O(n log n) or O(n) time.
For example, filtering the list of possible words after each guess is done efficiently by traversing the doubly linked list and removing nodes that do not match the clues.
### Space Complexity:

Memory usage is optimized by avoiding unnecessary data duplication.
By combining the BST and the doubly linked list, nodes are shared between the two structures, reducing the overall memory footprint.
Avoided using data structures that require additional space per node, such as parent pointers or extra balancing information.
Reasons for Not Using Certain Data Structures:
### Red-Black Tree (R&B Tree):

While R&B trees offer balanced search times, they require additional memory per node to store the color and possibly parent pointers.
The overhead of maintaining balance in an R&B tree was not justified given the memory constraints and the specific needs of the project.
Since the primary operations are insertion and search, and the BST is built from sorted input, the BST remains relatively balanced without the need for a self-balancing tree.
### Parent Pointers:

Adding a parent pointer to each node would increase the memory usage per node.
Since the algorithms did not require upward traversal of the tree, parent pointers were unnecessary.
Excluding parent pointers helped in keeping the memory usage within the required limits.
Achieving Efficiency Goals:
### Fast Execution:

Efficient algorithms for searching and filtering ensure that the game responds quickly to user input.
The use of efficient data structures reduces the computational overhead.
## Space Efficiency:

Careful consideration was given to the memory used by each data structure.
Sharing nodes between the BST and the doubly linked list minimizes redundant data.
Avoidance of unnecessary pointers or data fields in the structures.
## Conclusion:
By carefully selecting and optimizing the data structures and algorithms, the program achieves both high speed and low memory usage. The combination of a BST and a doubly linked list provides a balance between efficient data management and minimal memory overhead. This approach allowed me to meet the project's objectives and constraints, resulting in a successful implementation of the word-guessing game.
