#ifndef SET_H
#define SET_H

#include "tree.h"

class Set
{
    public:
        Set(Tree *tree = 0);// bugable :(, all are going dangerous if tree isn't rvalue
        Set(Data *array, int n, Tree *tree = 0);
        Set(const Set &original);

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

#endif // SET_H
