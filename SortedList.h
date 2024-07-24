#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {

    template <typename T>
    class SortedList {
    private:
        class Node {
        private:
            T data;
            Node* next;

            Node(T data);

            Node(const Node& node);

            Node& operator=(const Node& node);

            ~Node();
        };
        Node* list;

    public:
        void printList();

         /**
          * Constructor without parameters
          */
         SortedList();

         /**
          * Copy constructor
          * @param SortedList
          */
         SortedList(const SortedList& sortedList);

         ~SortedList();

         /**
          * assignment
          * @param list to assign from
          * @return this for farther assignments
          */
         SortedList& operator=(const SortedList& other);

         /**
          * Adds a new type T element to the list in the right order
          * @param element
          */
         void insert(T element);

         /**
          * Returns the amount of items of the list
          * @return
          */
         int length() const;

        /**
         * Iterator for iterate over the class
         */
        class ConstIterator {
        private:
            const SortedList* sortedList;
            int index;

            ConstIterator(const SortedList* sortedList, int index);

        public:
            void operator++();
            bool operator!=(const SortedList::ConstIterator& other) const;
            const T& operator*() const;

            friend SortedList;
        };

        void remove(const ConstIterator& iterator);

        ConstIterator begin() const;
        ConstIterator end() const;

        SortedList apply(T (*operation)(T)) const;
        SortedList filter(bool (*function)(T)) const;
    };
	
    template<typename T>
    SortedList<T>::SortedList() : data(T()), isEmpty(true), next(nullptr) {};

    template<typename T>
    SortedList<T>::SortedList(const SortedList& sortedList) {
        this->insert(sortedList.list.data);
        Node* nextNode = sortedList.list;
        while(nextNode != nullptr) {
            this->insert(nextNode->data);
            nextNode = nextNode->next;
        }
    }

    template<typename T>
    SortedList<T>::~SortedList() {
        delete this->next;
    }

    template<typename T>
    SortedList<T>& SortedList<T>::operator=(const SortedList<T>& other) {
        if(this == &other) {
            return *this;
        }
        delete this->list;
        this->list = new Node(other.list);
        return *this;
    }

    template<typename T>
    void SortedList<T>::insert(T element) {
        if (this->isEmpty) {
            this->isEmpty = false;
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
            newNode->isEmpty = this->isEmpty;
            this->next = newNode;
            return;
        }
        newNode->data = element;
        newNode->isEmpty = false;
        if (this->length() == 1) {
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
        for (int i = 3; i < this->length()+1; i++) {
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

    template<typename T>
    void SortedList<T>::remove(const ConstIterator& iterator) {
        Node* toDelete = list;
        if (iterator.index == 0) {
            list = toDelete->next;
            toDelete->next = nullptr;
            delete(toDelete);
        }
        Node* previous = list;
        toDelete* = previous->next;
        for (int i = 1; i < iterator.index; i++) {
            previous = previous->next;
            toDelete = previous->next;
        }
        previous->next = toDelete.next;
        toDelete.next = nullptr;
        delete(toDelete);
    }

    template<typename T>
    void SortedList<T>::printList() {
        if(isEmpty) {
            return;
        }
        std::cout << this->data << std::endl;
        SortedList* nextNode = this->next;
        while(nextNode != nullptr) {
            std::cout << nextNode->data << std::endl;
            nextNode = nextNode->next;
        }
    }

    template<typename T>
    int SortedList<T>::length() const {
        if(isEmpty) {
            return 0;
        }
        int count = 1;
        SortedList* nextNode = this->next;
        while(nextNode != nullptr) {
            nextNode = nextNode->next;
            count++;
        }
        return count;
    }

    template<typename T>
    SortedList<T> SortedList<T>::apply(T (*operation)(T)) const {
        SortedList<T> appliedList;
        for(T n: (*this)) {
            appliedList.insert(operation(n));
        }
        return appliedList;
	}

    template<typename T>
    SortedList<T> SortedList<T>::filter(bool (*function)(T)) const {
        SortedList<T> FilteredList;
        for(T n: (*this)) {
            if(function(n)) {
                FilteredList.insert(n);
            }
        }
        return FilteredList;
    }

    template<typename T>
    typename SortedList<T>::ConstIterator SortedList<T>::begin() const {
        ConstIterator begin(this,0);
        return begin;
    }

    template<typename T>
    typename SortedList<T>::ConstIterator SortedList<T>::end() const {
        ConstIterator end(this, this->length());
        return end;
    }

    //---------------------------------Iterator Implementations---------------------------------
    template<typename T>
    SortedList<T>::ConstIterator::ConstIterator(const mtm::SortedList<T>* list, int index) :
    sortedList(sortedList), index(index) {}

    template<typename T>
    void SortedList<T>::ConstIterator::operator++() {
        index++;
        if (index == sortedList->length()+1) {
            throw std::out_of_range("Bad index");
        }
    }

    template<typename T>
    bool SortedList<T>::ConstIterator::operator!=(const SortedList::ConstIterator& other) const{
        return (this->index != other.index);
    }

    template<typename T>
    const T& SortedList<T>::ConstIterator::operator*() const {
        Node* current;
        current = sortedList->list;
        int count = 0;
        while (count < index) {
            current = current->next;
            count++;
        }
        return current->data;
    }
}

