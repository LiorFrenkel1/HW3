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
    private:
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
         SortedList& operator=(const SortedList& list);

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
            const SortedList* list;
            int index;

            ConstIterator(const SortedList* list, int index);

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
    SortedList<T>::SortedList(const SortedList& sortedList) : data(T()), isEmpty(true),
    next(nullptr){
        if(!sortedList.isEmpty) {
            this->insert(sortedList.data);
            SortedList* nextNode = sortedList.next;
            while(nextNode != nullptr) {
                this->insert(nextNode->data);
                nextNode = nextNode->next;
            }
        }
    }

    template<typename T>
    SortedList<T>::~SortedList() {
        delete this->next;
    }

    template<typename T>
    //Todo: need to check for empty lists
    SortedList<T>& SortedList<T>::operator=(const SortedList<T>& list) {
        if(this == &list) {
            return *this;
        }
        delete this->next;
        if(list.next != nullptr) {
            SortedList* newList = new SortedList(*list.next);
            this->next = newList;
        } else {
            this->next = nullptr;
        }
        this->isEmpty = list.isEmpty;
        this->data = list.data;
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
        int removeIndex = iterator.index;
        SortedList* sortedList = iterator.list;
        if(sortedList->length() == 1) {
            sortedList->isEmpty = true;
            return;
        }
        for (int i = 0; i < removeIndex;i++) {
            sortedList = sortedList->next;
        }
        if (sortedList->next == nullptr) {
            delete sortedList;
            return;
        }
        while (sortedList->next->next != nullptr) {
            sortedList->data = sortedList->next->data;
            sortedList = sortedList->next;
        }
        sortedList->data = sortedList->next->data;
        delete sortedList->next;
        sortedList->next = nullptr;
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
    list(list), index(index) {}

    template<typename T>
    void SortedList<T>::ConstIterator::operator++() {
        index++;
        if (index == list->length()+1) {
            throw std::out_of_range("Bad index");
        }
    }

    template<typename T>
    bool SortedList<T>::ConstIterator::operator!=(const SortedList::ConstIterator& other) const{
        return (this->index != other.index);
        //Todo: check if needed: (this->list != other.list);
    }

    template<typename T>
    const T& SortedList<T>::ConstIterator::operator*() const {
        SortedList* current;
        current = list;
        int count = 0;
        while (count < index) {
            current = current->next;
            count++;
        }
        return current->data;
    }
}

