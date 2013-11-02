#ifndef TREE_H
#define TREE_H

#include <exception>

typedef int Data;

class TreeIterator;

class Tree
{
    public:
        friend TreeIterator;
        typedef TreeIterator Iterator;
        Tree() {}
        ~Tree();
        void addElement(const Data &value);
        Iterator begin() const;
        Iterator end() const;

    private:
        //Interface for Iterator
        Data &asterisc(void *pointer) const;
        void next(void *&pointer) const;

        //Implementation
        virtual Data &asteriscImpl(void *pointer) const = 0;
        virtual void nextImpl(void *&pointer) const = 0;
        virtual void addElementImpl(const Data &value) = 0;
        virtual void *beginImpl() const = 0;
        virtual void clear() {};
};

class TreeIterator
{
    public:
        friend Tree;
        TreeIterator();
        //default copy constructor
        //default assign operator
        ~TreeIterator();

        Data &operator*() const;
        TreeIterator operator++();
        TreeIterator operator++(int);
        bool operator==(const TreeIterator &other) const;
        bool operator!=(const TreeIterator &other) const {return !(*this == other);}
    private:
        const Tree *owner;
        void *current;

        TreeIterator(const Tree *owner, void *current);
};

class TreeIteratorException: public std::exception
{
        const char *what() const throw() {return "trying to access iterator, that isn't binded with container";}
};

#endif // TREE_H
