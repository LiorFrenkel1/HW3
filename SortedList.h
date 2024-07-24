#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {

    template <typename T>
    class SortedList {
    private:
        class Node {
        public:
            T data;
            Node* next;

            Node(T data);

            Node(const Node& node);

            Node& operator=(const Node& node);

            ~Node();
        };
        Node* list;

    public:
        //void printList();
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
    SortedList<T>::Node::Node(T data) : data(data), next(nullptr){};

    template<typename T>
    SortedList<T>::Node::Node(const Node& node) : data(node.data) {
        Node* currentOther = &node.next;
        Node* currentThis = &this;
        while(currentOther->next != nullptr) {
            currentThis->next = new Node(currentOther->data);
            currentThis = currentThis->next;
            currentOther = currentOther->next;
        }

    }

    template<typename T>
    typename SortedList<T>::Node& SortedList<T>::Node::operator=(const mtm::SortedList<T>::Node &node) {
        if (this == &node) {
            return *this;
        }
        Node newNode(node);
        this->data = newNode.data;
        this->next = newNode.next;
        return *this;
    }

    template<typename T>
    SortedList<T>::Node::~Node() {
        delete this->next;
    }
	
    template<typename T>
    SortedList<T>::SortedList() : list(nullptr) {}

    template<typename T>
    SortedList<T>::SortedList(const SortedList& sortedList) : list(sortedList.list) {}

    template<typename T>
    SortedList<T>::~SortedList() {
        delete this->list;
    }

    template<typename T>
    SortedList<T>& SortedList<T>::operator=(const SortedList<T>& other) {
        if(this == &other) {
            return *this;
        }
        delete this->list;
        SortedList<T>* newList = new SortedList<T>(other);
        this->list = newList->list;
        return *this;
    }

    template<typename T>
    void SortedList<T>::insert(T element) {
        Node* node = this->list;
        if (node == nullptr) {
            list = new Node(element);
            return;
        }
        if (element > node->data) {
            this->list = new Node(element);
            this->list->next = node;
            return;
        }
        while (node->next != nullptr && node->next->data > element) {
            node = node->next;
        }
        Node* secondPartOfList = node->next;
        node->next = new Node(element);
        node->next->next = secondPartOfList;
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
        toDelete = previous->next;
        for (int i = 1; i < iterator.index; i++) {
            previous = previous->next;
            toDelete = previous->next;
        }
        previous->next = toDelete->next;
        toDelete->next = nullptr;
        delete(toDelete);
    }

    template<typename T>
    int SortedList<T>::length() const {
        int count = 0;
        Node* node = this->list;
        while (node != nullptr) {
            count++;
            node = node->next;
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
    SortedList<T>::ConstIterator::ConstIterator(const mtm::SortedList<T>* sortedList, int index) :
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

