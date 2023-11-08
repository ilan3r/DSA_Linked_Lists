# DSA_Linked_Lists
Data Structures and Algorithms (MTE 140) Assignment 
Professor Charbel Azzi

Implementing a sequential linked list and doubly linked list. 
Sequentially linked list is implemented using an array whose size is dynamically allocated (the size of the array is a parameter for the constructor). The size cannot change, and there cannot be gaps in the list (can only insert after the last element, and can only remove from an occupied position in the list). An element can be inserted in/removed from the beginning or middle of the list, and in this case the list must be shifted. 

Doubly linked list is implementing a list using pointers, where each element of the list is connected to its next and previous element. The list has no limits on its size (other than heap constraints). Each element of the list is represetned by a node object, which has members next, previous, and value. the head pointer points to the beginning of the list and the tail points to the end, and the list can be traversed in both directions (head to tail or tail to head).
