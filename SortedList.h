#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {
    typedef int T;
    //template <typename T>
    class SortedList {
    private:
        T data;
        int length;
        SortedList* next;
    public:
        void printList();
        /**
         *
         * the class should support the following public interface:
         * if needed, use =defualt / =delete
         *
         * constructors and destructor:
         * 3. operator= - assignment operator
         * 4. ~SortedList() - destructor
         *
         * iterator:
         * 5. class ConstIterator;
         * 6. begin method
         * 7. end method
         *
         * functions:
         * 9. remove - removes an element from the list
         * 10. length - returns the number of elements in the list
         * 11. filter - returns a new list with elements that satisfy a given condition
         * 12. apply - returns a new list with elements that were modified by an operation
         */

         /**
          * Constructor without parameters
          */
         SortedList();

         /**
          * Copy constructor
          * @param SortedList
          */
         SortedList(const SortedList& sortedList);

         /**
          * Adds a new type T element to the list in the right order
          * @param element
          */
         void insert(T element);
    };

    SortedList::SortedList() : data(T()), length(0), next(nullptr) {};

    void SortedList::insert(T element) {
        this->length++;
        if (this->length == 1) {
            this->data = element;
            return;
        }
        SortedList* newNode = new SortedList();
        T temp;
        if (element > this->data) { // If the new element is the new biggest
            temp = this->data;
            this->data = element;
            newNode->data = temp;
            newNode->next = this->next;
            this->next = newNode;
            return;
        }
        newNode->data = element;
        if (length == 2) {
            this->next = newNode;
            return;
        }
        SortedList* previous = this->next;
        if (element > previous->data) { // If the new element is the new biggest
            temp = previous->data;
            previous->data = element;
            newNode->data = temp;
            newNode->next = previous->next;
            previous->next = newNode;
            return;
        }
        SortedList* current = previous->next;
        for (int i = 3; i < this->length; i++) {
            if (current->data < element) {
                temp = current->data;
                current->data = element;
                newNode->data = temp;
                newNode->next = current->next;
                current->next = newNode;
                return;
            }
            previous = previous->next;
            current = current->next;
        }
        previous->next = newNode;
    }

    void SortedList::printList() {
        std::cout << this->data << ' ';
        SortedList* nextNode = this->next;
        for (int i = 2; i <= this->length; i++) {
            std::cout << nextNode->data << ' ';
            nextNode = nextNode->next;
        }
    }

    SortedList::SortedList(const SortedList &sortedList) =default;

    /*
    template <class T>
    class SortedList<T>::ConstIterator {
    /*
     * the class should support the following public interface:
     * if needed, use =defualt / =delete
     *
     * constructors and destructor:
     * 1. a ctor(or ctors) your implementation needs
     * 2. copy constructor
     * 3. operator= - assignment operator
     * 4. ~ConstIterator() - destructor
     *
     * operators:
     * 5. operator* - returns the element the iterator points to
     * 6. operator++ - advances the iterator to the next element
     * 7. operator!= - returns true if the iterator points to a different element
     *
    };
    */
}

