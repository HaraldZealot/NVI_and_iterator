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
        void previousImpl(void *&pointer) const;
        void *beginImpl() const;
        void findImpl(const Data &value, void *&pointer) const;
        void insertImpl(const Data &value, void *&pointer);
        void eraseImpl(void *&pointer);
        void clear();

        struct Node
        {
            Data content;
            Node *parent, *left, *right;
            enum Branching {origin, leftBranch, rightBranch} branching;
            Node(const Data &value, Node *parent, Branching branching);
            ~Node();
        } *root;
        void eraseLeaf(Node *&node);
        void eraseInChain(Node *&node);
        void eraseFork(Node *&node);
        static void clear(Node *&node);
};

class SimpleTreeException: public std::exception
{
    public:
        const char *what() const throw() {return "trying to access to not existing element";}
};

#endif // SIMPLETREE_H
