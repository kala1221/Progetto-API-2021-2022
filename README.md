# API Project 2021-2022
Final Exam of Algorithms and Principles of Computer Science  
**Grade: 30/30 with honors**

## Overview
This project implements a word-guessing game designed to be both time-efficient and space-efficient. By carefully selecting and optimizing data structures and algorithms, the program delivers fast execution and minimal memory usage.

**Key Features:**
- Efficient vocabulary management using a Binary Search Tree (BST).
- Dynamic filtering of word candidates using a Doubly Linked List.
- Optimized for operations like search, insertion, and filtering.

## Data Structures
### Binary Search Tree (BST)
**Purpose:** Efficiently store and manage the vocabulary of allowable words.

**Advantages:**
- Fast insertion and search operations (`O(log n)` on average).
- Maintains a relatively balanced structure when built from sorted input.

**Implementation Details:**
- Nodes store words and are arranged lexicographically.
- Allows for efficient vocabulary searches during gameplay.

---

### Doubly Linked List
**Purpose:** Narrow down word candidates dynamically based on user clues.

**Advantages:**
- Fast addition and removal of nodes.
- Maintains an ordered sequence of possible words.

**Implementation Details:**
- Nodes in the BST are shared with the linked list to reduce memory usage.
- Includes pointers to the next (`listainternasucc`) and previous (`listainternaprec`) nodes.

---

## Algorithm Optimization
### Time Complexity
- Most operations are designed to run in `O(n log n)` or better.
- Filtering operations utilize the doubly linked list for efficient traversal and updates.

### Space Complexity
- Memory usage is minimized by sharing nodes between data structures.
- Avoided unnecessary fields like parent pointers or balancing information.

---

## Design Decisions
### Why Not Red-Black Trees?
- Additional memory requirements for balancing information were unnecessary.
- The BST built from sorted input was already balanced enough for this project.

### Why Avoid Parent Pointers?
- Parent pointers increase memory usage.
- No upward traversal was needed in the algorithms.

---

## Efficiency Goals
### Fast Execution
- Optimized search and filtering algorithms ensure quick responses to user input.
- Lightweight data structures reduce computational overhead.

### Space Efficiency
- Node sharing between BST and linked list minimizes memory usage.
- Avoided redundant pointers and unnecessary data fields.

---

## Conclusion
This project successfully implements a time- and space-efficient word-guessing game by leveraging a Binary Search Tree and Doubly Linked List. The careful selection of data structures and optimizations allowed me to meet the objectives and constraints, resulting in a robust and high-performing application.

