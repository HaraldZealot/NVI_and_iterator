#include "tree.h"

//------- TreeIterator -------//

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

TreeIterator TreeIterator::operator--()
{
    if(owner)
        owner->previous(current);

    return *this;
}

TreeIterator TreeIterator::operator--(int)
{
    TreeIterator result(*this);
    --(*this);
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


//------- Tree -------//

Tree::~Tree()
{
    clear();
}

Tree::Iterator Tree::find(const Data &value) const
{
    void *pointer = 0;
    findImpl(value, pointer);
    return Iterator(this, pointer);
}

Tree::Iterator Tree::insert(const Data &value)
{
    void *pointer = 0;
    insertImpl(value, pointer);
    return Iterator(this, pointer);
}

Tree::Iterator Tree::erase(const Iterator &position)
{
    if(this != position.owner)
        throw TreeIteratorException();

    void *pointer = position.current;
    eraseImpl(pointer);
    return TreeIterator(this, pointer);
}

int Tree::erase(const Data &value)
{
    int counter = 0;
    void *pointer = 0;
    findImpl(value, pointer);

    while(pointer)
    {
        ++counter;
        eraseImpl(pointer);
        findImpl(value, pointer);
    }

    return counter;
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

void Tree::previous(void *&pointer) const
{
    previousImpl(pointer);
}
