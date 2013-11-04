#include "simpletree.h"
#include <cassert>

SimpleTree::SimpleTree():
    Tree(),
    root(0)
{}

SimpleTree::SimpleTree(const Data *array, int size):
    Tree(),
    root(0)
{
    for(int i = 0; i < size; ++i)
        ((Tree *)this)->addElement(array[i]);// гэта хіба вычварэнства, але тут можна выклікаць і чатырох аргументны варыянт
}

SimpleTree::~SimpleTree()
{
    clear();
}

Data &SimpleTree::asteriscImpl(void *pointer) const
{
    if(pointer)
        return ((Node *)pointer)->content;
    else
        throw SimpleTreeException();
}

void SimpleTree::nextImpl(void *&pointer) const
{
    Node *current = (Node *)pointer;

    if(current)
    {
        if(current->right)
        {
            current = current->right;

            while(current->left)
                current = current->left;
        }
        else
        {
            while(current->parent && current->branching == Node::rightBranch)
                current = current->parent;

            if(!current->parent)
                current = 0;
            else
                current = current->parent;
        }

        pointer = (void *)current;
    }
}

void *SimpleTree::beginImpl() const
{
    Node *current = root;

    if(current)
        while(current->left)
            current = current->left;

    return (void *)current;
}

void SimpleTree::addElementImpl(const Data &value)
{
    addElement(root, 0, Node::origin, value);
}

void SimpleTree::eraseImpl(void *&pointer)
{
    if(pointer)
    {
        Node *current = (Node *) pointer;

        if(current->left && current->right)
        {
            eraseFork(current);
        }
        else
        {
            nextImpl(pointer);
            bool rootErasing = root == current;
            eraseInChain(current);

            if(rootErasing)
                root = current;
        }
    }
}

void SimpleTree::addElement(SimpleTree::Node *&current, SimpleTree::Node *parent, SimpleTree::Node::Branching branching, const Data &value)
{
    if(!current)
        current = new Node(value, parent, branching);
    else if(value < current->content)
        addElement(current->left, current, Node::leftBranch, value);
    else if(value > current->content)
        addElement(current->right, current, Node::rightBranch, value);
}

void SimpleTree::eraseLeaf(SimpleTree::Node *&node)
{
    assert(node);
    assert(!node->left && !node->right);

    if(node->branching == Node::leftBranch)
        node->parent->left = 0;
    else if(node->branching == Node::rightBranch)
        node->parent->right = 0;

    delete node;
    node = 0;
    assert(!node);
}

void SimpleTree::eraseInChain(SimpleTree::Node *&node)
{
    assert(node);
    assert(!node->left || !node->right);

    if(!node->left && !node->right)
    {
        eraseLeaf(node);
    }
    else
    {
        assert((!node->left && node->right) || (node->left && !node->right));
        Node *&child = node->left ? node->left : node->right;
        Node *&parent = node->parent;
        child->branching = node->branching;
        child->parent = parent;

        if(parent)
        {
            if(node->branching == Node::leftBranch)
                parent->left = child;
            else if(node->branching == Node::rightBranch)
                parent->right = child;
            else
                assert(0);
        }

        assert(child->parent == parent && (parent->left == child || parent->right == child));
        assert((child->branching == Node::leftBranch && parent->left == child) || (child->branching == Node::rightBranch && parent->right == child));
        delete node;
        node = 0;
        assert(!node);
        node = child;
    }
}

void SimpleTree::eraseFork(SimpleTree::Node *&node)
{
    assert(node);
    assert(node->left && node->right);
    Node *replacement = node;
    replacement = replacement->right;

    while(replacement->left)
        replacement = replacement->left;

    node->content = replacement->content;
    eraseInChain(replacement);
}

void SimpleTree::clear()
{
    clear(root);
}

void SimpleTree::clear(SimpleTree::Node *&node)
{
    if(node)
    {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

//------- Node -------//

SimpleTree::Node::Node(const Data &value, SimpleTree::Node *parent, SimpleTree::Node::Branching branching):
    content(value),
    parent(parent),
    left(0),
    right(0),
    branching(branching)
{
}

SimpleTree::Node::~Node()
{
    content.~Data();
    parent = 0;
    left = 0;
    right = 0;
    branching = Node::origin;
}
