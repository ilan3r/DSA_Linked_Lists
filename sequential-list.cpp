#include "sequential-list.h"
#include <iostream>

using namespace std;



SequentialList::SequentialList(unsigned int cap) {
    capacity_ = cap;
    data_ = new DataType[capacity_];
    size_ = 0;

}


SequentialList::~SequentialList() {
    delete [] data_;
    data_ = nullptr;

}

unsigned int SequentialList::size() const {
    return size_;

}


unsigned int SequentialList::capacity() const {
    return capacity_;

}


bool SequentialList::empty() const {
    if (size_ == 0)
        return true;

    else
        return false;

}


bool SequentialList::full() const{
    if (size_ == capacity_)
        return true;

    else
        return false;

}


SequentialList::DataType SequentialList::select(unsigned int index) const {
    //if list is empty
    if (empty())
        return NULL;

    //if index is out of range or negative, select value of list in the highest index
    else if (index > size_-1 || index < 0) {
        return data_[size_-1];
    }
        //if index is valid
    else
        return data_[index];

}


unsigned int SequentialList::search(DataType val) const {
    for (int i = 0; i < size_; i++) {
        if (data_[i] == val) {
            //return index of value if found
            return i;
        }
    }
    //return size of list if not found
    return size_;

}


void SequentialList::print() const {
    for (int i = 0; i < size_; i++)
        cout << "===" <<data_[i];
}


bool SequentialList::insert(DataType val, unsigned int index) {
    //first check if index is valid
    if (index > size_ || index < 0 || size_ == capacity_)
        return false;

    //if list is empty or user wants to insert in the back of the list
    else if(size_ == 0)
        return insert_front(val);

    else if(index == size_)
        return insert_back(val);

    else {
        //shift everything to the right of the index (including the value at the index) to the right
        for (int i = size_; i > index; i--)
            data_[i] = data_[i - 1];
        data_[index] = val;
        size_++;
        return true;
    }

}


bool SequentialList::insert_front(DataType val) {
    if (empty()) {
        //if list is empty, insert value in the front
        data_[0] = val;
        size_++;
        return true;
    }
    else if(size_ == capacity_)
        return false;

    else {
        //shift every value one to the right if the list is not empty
        for (int i = size_; i >= 1; i--)
            data_[i] = data_[i - 1];

        data_[0] = val;
        size_++;
        return true;
    }

}


bool SequentialList::insert_back(DataType val) {

    //if list is empty, insert value in the front
    if (empty()) {
        //if list is empty, insert value in the front
        data_[0] = val;
        size_++;
        return true;
    }
    else if(size_ == capacity_)
        return false;

    //use size_ to insert value at the end of the list
    else {
        data_[size_] = val;
        size_++;
        return true;

    }

}


bool SequentialList::remove(unsigned int index) {
    //first check if index is valid
    if (empty() || index < 0 || index > size_)
        return false;

    //if size is 1, don't need to shift anything
    else if (size_ == 1) {
        data_[0] = NULL;
        return true;
    }
    else if (index == 0)
        return remove_front();

    else if(index == size_-1)
        return remove_back();

    else {
        for (int i = index; i < size_-2; i++)
            data_[i] = data_[i+1];
        size_--;
        data_[size_-1] = NULL;
        return true;
    }

}


bool SequentialList::remove_front() {
    //check if list is empty
    if (empty())
        return false;

        //if size is 1, don't need to shift anything
    else if (size_ == 1)
    {
        data_[0] = NULL;
        size_--;
        return true;
    }
    else
    {
        //shift everything one to the left
        for (int i = 0; i < size_-1; i++)
            data_[i] = data_[i+1];
        //after removing the front, the last element must be NULL
        data_[size_-1] = NULL;
        size_--;
        return true;
    }

}


bool SequentialList::remove_back() {
    //check if list is empty
    if (empty())
        return false;

    else if (size_ == 1) {
        data_[1] = NULL;
        size_--;
        return true;
    }
    else {
        data_[size_ - 1] = NULL;
        size_--;
        return true;
    }
}


bool SequentialList::replace(unsigned int index, DataType val) {
    //check if index is valid, list is empty, or value at given index is empty
    if (empty() || index > size_-1 || index < 0 || data_[index] == NULL)
        return false;

    else {
        data_[index] = val;
        return true;

    }
}

