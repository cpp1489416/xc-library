// This code is written by coopoopoo

#ifndef MAP_H
#define MAP_H

#include "RedBlackTree.h"

namespace Xc
{
    template <typename Key, typename Element>
    class Map
    {
    public:
        class Node;
        typedef RedBlackTree<Node> Tree;

    public:
        class Node
        {
        public:
            Node(const Key *key = nullptr, Element *element = nullptr);
            ~Node();
            bool operator == (const Node &rhs) const { return GetKey() == rhs.GetKey(); }
            bool operator < (const Node &rhs) const { return GetKey() < rhs.GetKey(); }
            bool operator > (const Node &rhs) const { return GetKey() > rhs.GetKey(); }
            const Key &GetKey() const { return *myKey; }
            const Element &GetElement() { return *myElement; }
            
        private:
            void SetElement(Element *element) { myElement = element; }
            void SetKey(Key *key) { myKey = key; }
            Element &ReferenceElement() { return *myElement; }

            const Key *myKey;
            Element *myElement;

            friend class Map<Key, Element>;
            friend class Map<Key, Element>::Iterator;
        };

        // this is the iterator of map
        class Iterator : public Tree::Iterator
        {
        public:
            Iterator() {}
            const Key &GetKey() const { return (*this).GetKey(); }
            const Element &GetElement() const { return (*this).GetElement; }
            void SetElement(const Element &element) { (*this).SetElement(element); }

        private:
            Iterator(typename Tree::Iterator treeIterator);
            
            friend class Map<Key, Element>;
        };

    public:
        Iterator Insert(const Key &key, const Element &element);
        Element &operator [] (const Key &key);
        Iterator GetFirstIterator();
        Iterator GetInvalidIterator();
        Iterator begin() { return GetFirstIterator(); }
        Iterator end() { return GetInvalidIterator(); }
  
    private:
        RedBlackTree<Node> myTree;
    };

    template <typename Key, typename Element>
    Map<Key, Element>::Node::Node(const Key *key, Element *element) :
        myKey(key), myElement(element)
    {
    }
    
    template <typename Key, typename Element>
    Map<Key, Element>::Node::~Node()
    {
        delete myKey;
        delete myElement;
    }

    template <typename Key, typename Element>
    typename Map<Key, Element>::Iterator Map<Key, Element>::Insert(const Key &key, const Element &element)
    {
        Node node(key, nullptr);
        Tree::Iterator itr = myTree.insert(node);
        if (itr->GetTimes() > 1)
        {
            itr->SetTimes(1);
        }
        else
        {
            (*itr).SetKey(new Key(key));
            (*itr).ReferenceElement() = element; // the only difference between operator [] and insert function
        }
        node.SetKey(nullptr); // key must nullptr
        return Iterator(itr);
    }

    template <typename Key, typename Element>
    Element &Map<Key, Element>::operator [] (const Key & key)
    {
        Node node(&key, nullptr);
        Tree::Iterator itr = myTree.insert(node);
        if (itr.GetTimes() > 1)
        {
            itr.SetTimes(1);
        }
        else
        {
            (*itr).SetKey(new Key(key));
            (*itr).SetElement(new Element());
        }
        node.SetKey(nullptr); // why release the last element
        return (*itr).ReferenceElement();
    }

    template<typename Key, typename Element>
    typename Map<Key, Element>::Iterator Map<Key, Element>::GetFirstIterator()
    {
        return Iterator(myTree.begin());
    }

    template<typename Key, typename Element>
    typename Map<Key, Element>::Iterator Map<Key, Element>::GetInvalidIterator()
    {
        return Iterator(myTree.end());
    }

    template <typename Key, typename Element>
    Map<Key, Element>::Iterator::Iterator(typename Tree::Iterator treeIterator) :
        Tree::Iterator(treeIterator)
    {
    }

}

#endif // MAP_H
