#include "tree.h"

TreeIterator::TreeIterator():
    owner(0),
    current(0)
{}

TreeIterator::~TreeIterator()
{
    owner = 0;
    current = 0;
}

Data &TreeIterator::operator*() const
{
    if(owner)
        return owner->asterisc(current);
    else
        throw TreeIteratorException();
}

TreeIterator TreeIterator::operator++()
{
    if(owner)
        owner->next(current);

    return *this;
}

TreeIterator TreeIterator::operator++(int)
{
    TreeIterator result(*this);
    ++(*this);
    return result;
}

bool TreeIterator::operator==(const TreeIterator &other) const
{
    return owner == other.owner && current == other.current;
}

TreeIterator::TreeIterator(const Tree *owner, void *current):
    owner(owner),
    current(current)
{}


Tree::~Tree()
{
    clear();
}

void Tree::addElement(const Data &value)
{
    addElementImpl(value);
}

Tree::Iterator Tree::begin() const
{
    return Iterator(this, beginImpl());
}

Tree::Iterator Tree::end() const
{
    return Iterator(this, 0);
}

Data &Tree::asterisc(void *pointer) const
{
    return asteriscImpl(pointer);
}

void Tree::next(void *&pointer) const
{
    nextImpl(pointer);
}
