// Assignment 1.2, Ilan Rajpar

#include "doubly-linked-list.h"

using namespace std;

DoublyLinkedList::Node::Node(DataType data) {
    value = data;

    //Note - in the pdf it says ext not next, I used next
    next = nullptr;

    //Note - in the pdf it says rev not prev, I used prev
    prev = nullptr;


}


DoublyLinkedList::DoublyLinkedList() {
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
    // Question - do we have to make this unsigned?

}


DoublyLinkedList::~DoublyLinkedList() {

    //if size is zero, don't need to do anything, can delete anyways to be safe
    if (size_ == 0)
    {
        delete head_;
        head_ = nullptr;
        delete tail_;
        tail_ = nullptr;
    }

    //if size is one, delete the node
    else if (size_ == 1)
    {
        delete head_;
        head_ = nullptr;
        tail_ = nullptr;
        //in this case, since head and tail point to same node,
        //we don't need to delete tail as well

    }
    //if the size is more than one
    else
    {
        Node *next_node = head_;
        //make head_ and tail_ nullptr
        // since the nodes that head and tail point to will be deleted below
        head_ = nullptr;
        tail_ = nullptr;
        Node *prev_node = nullptr;

        // traverse through the list and delete all the pointers
        for (int i = 0; i < size_; i++)
        {
            prev_node = next_node;
            next_node = next_node->next;
            delete prev_node;
            prev_node = nullptr;
        }

    }

}


unsigned int DoublyLinkedList::size() const {
    return size_;

}


unsigned int DoublyLinkedList::capacity() const {
    return CAPACITY;

}


bool DoublyLinkedList::empty() const {
    if (size_ == 0)
        return true;
    else
        return false;

}


bool DoublyLinkedList::full() const {
    if (size_ >= CAPACITY)
        return true;
    else
        return false;


}


DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const {
    //if list is empty return null
    if (empty())
        return NULL;

    //if invalid index, return value of the last node
    else if (index < 0 || index > size_-1)
    {
        int i = 0;
        Node *tempNode = head_;
        while (i < size_-1)
        {
            tempNode = tempNode->next;
            i++;
        }
        return tempNode->value;
    }

    //traverse through the list till the element at the desired element is reached and return the value at this element
    else
    {
        int i = 0;
        Node *tempNode = head_;
        while (i < index)
        {
            tempNode = tempNode->next;
            i++;
        }
        return tempNode->value;

    }
}


unsigned int DoublyLinkedList::search(DataType value) const {
    int i = 0;
    Node *tempNode = head_;
    while (i < size_-1)
    {
        if (tempNode->value == value)
            //return the index once value is found the firs ttime
            return i;
        tempNode = tempNode->next;
        i++;
    }
    //return size of the list if nothing is found
    return size_;
}


void DoublyLinkedList::print() const {
    //don't print if list is empty
    if (head_ == nullptr)
        return;

    //starting at beginning of list, print the value at each node
    Node *temp = head_;
    while (temp != nullptr) {
        cout<< temp->value << "->";
        temp = temp->next;
    }
    cout<< endl;

}

//implementing this function is optional - chose not to use
DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const {

}


bool DoublyLinkedList::insert(DataType value, unsigned int index) {
    //if invalid index, or at capacity
    if (index < 0 || index > CAPACITY-1 || size_ >= CAPACITY)
        return false;

    //if list is empty
    else if (index == 0)
        return insert_front(value);

    //if index is greater than the size but within capacity, insert at the back of the list
    else if (index > size_-1 && index < CAPACITY)
        return insert_back(value);

    //if inserting in the middle of the list
    else
    {
        int i = 0;
        Node *newNode = new Node(value);
        Node *next_node = head_;
        Node *prev_node = nullptr;
        while (i < index)
        {
            prev_node = next_node;
            next_node = next_node->next;
            i++;
        }
        prev_node->next = newNode;
        newNode->prev = prev_node;
        next_node->prev = newNode;
        newNode->next = next_node;
        size_++;
        return true;

    }


}

bool DoublyLinkedList::insert_front(DataType value) {
    //if invalid index
    if (size_ >= CAPACITY)
        return false;

    //create the newNode if the index is valid
    Node *newNode = new Node(value);

    if (empty())
    {
        head_ = newNode;
        tail_ = newNode;
        size_++;
        return true;

    }

    else
    {
        newNode->next = head_;
        head_->prev = newNode;
        head_ = newNode;
        size_++;
        return true;
    }
}


bool DoublyLinkedList::insert_back(DataType value) {
    //check if index is valid
    if (size_ >= CAPACITY)
        return false;

    Node *newNode = new Node(value);

    if (empty())
    {
        head_ = newNode;
        tail_ = newNode;
        size_++;
        return true;
    }

    else
    {
        Node *tempNode = tail_;
        tail_ = newNode;
        newNode->prev = tempNode;
        tempNode->next = newNode;
        size_++;
        return true;
    }




}


bool DoublyLinkedList::remove(unsigned int index) {
    //if index is invalid
    if (index < 0 || index > size_-1 || empty())
        return false;

    //use remove_front function if removing node at index 0
    else if (index == 0)
        return remove_front();

    //use remove_back function if removing node at the end of the list
    else if (index == size_-1)
        return remove_back();

    //if removing a node somewhere in the middle of the list
    else
    {
        int i = 0;
        Node *next_node = head_;
        Node *prev_node = nullptr;
        while (i < index) {
            prev_node = next_node;
            next_node = next_node->next;
            i++;
        }
        prev_node->next = next_node->next;
        Node *tempNode = next_node->next;
        tempNode->prev = next_node->prev;
        delete next_node;
        next_node = nullptr;
        size_--;
        return true;
    }

}


bool DoublyLinkedList::remove_front() {
    if (empty())
        return false;

    else if (size_ == 1)
    {
        delete head_;
        head_ = nullptr;
        tail_ = nullptr;
        size_--;
        return true;
    }

    else
    {
        Node *tempNode = head_;
        head_ = head_->next;
        head_->prev = nullptr;
        delete tempNode;
        tempNode = nullptr;
        size_--;
        return true;
    }
}


bool DoublyLinkedList::remove_back() {

    if (empty())
        return false;

    else if (size_ == 1)
    {
        delete head_;
        head_ = nullptr;
        tail_ = nullptr;
        size_--;
        return true;
    }

    else
    {
        Node *tempNode = tail_;
        tail_ = tail_->prev;
        tail_->next = nullptr;
        delete tempNode;
        tempNode = nullptr;
        size_--;
        return true;
    }

}


bool DoublyLinkedList::replace(unsigned int index, DataType value) {
    //if list is empty or index is invalid
    if (empty() || index < 0 | index > size_-1)
        return false;

    else
    {
        int i = 0;
        Node *tempNode = head_;
        while (i < index)
        {
            tempNode = tempNode->next;
            i++;
        }
        tempNode->value = value;
        return true;

    }
}
