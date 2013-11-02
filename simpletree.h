#ifndef SIMPLETREE_H
#define SIMPLETREE_H

#include <exception>
#include "tree.h"

class SimpleTree : public Tree
{
    public:
        SimpleTree();
        SimpleTree(const Data *array, int size);
        ~SimpleTree();

    private:
        Data &asteriscImpl(void *pointer) const;
        void nextImpl(void *&pointer) const;
        void addElementImpl(const Data &value);
        void *beginImpl() const;
        void clear();

        struct Node
        {
            Data content;
            Node *parent, *left, *right;
            enum Branching {origin, leftBranch, rightBranch} branching;
            Node(const Data &value, Node *parent, Branching branching);
            ~Node();
        } *root;
        static void addElement(Node *&current, Node *parent, Node::Branching branching, const Data &value);
        static void clear(Node *&node);
};

class SimpleTreeException: public std::exception
{
    public:
        const char *what() const throw() {return "trying to access to not existing element";}
};

#endif // SIMPLETREE_H
