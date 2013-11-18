#ifndef SET_H
#define SET_H

#include <exception>
#include "simpletree.h"

class DoubleInitializedSet: public std::exception
{
        const char *what() const throw() {return "trying for reinitialisation";}
};

class Set
{
    public:

        Set(): tree(0) {} // bugable :(, all are going dangerous if tree isn't rvalue
        Set(const Set &original);

        template <typename SomeTreeChild>//in c++11 we can write <typename SomeTreeChild=SimpleTree>
        void init();
        template <typename SomeTreeChild>
        void init(Data *array, int n);

        Set unite(const Set &rhs) const;
        Set intersect(const Set &rhs) const;
        Set substract(const Set &rhs) const;
        Set symmetricSubstract(const Set &rhs) const;

        bool has(const Data &element) const;
        bool has(const Set &otherSet) const;
    protected:
        const Tree *getTreePointer() const throw() {return tree;}
    private:
        Tree *tree;
};

template <typename SomeTreeChild>
void Set::init()
{
    if(!tree)
        tree = new SomeTreeChild();
    else
        throw DoubleInitializedSet();
}

template <typename SomeTreeChild>
void Set::init(Data *array, int n)
{
    if(!tree)
    {
        tree = new SomeTreeChild();

        for(int i = 0; i < n; ++i)
            tree->insert(array[i]);
    }
    else
        throw DoubleInitializedSet();
}

#endif // SET_H
