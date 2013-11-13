#include "set.h"
#include "simpletree.h"

Set::Set(Tree *tree):
    tree(tree)
{
    if(!this->tree)
    {
        this->tree = new SimpleTree();
    }
}

Set::Set(Data *array, int n, Tree *tree):
    tree(tree)
{
    if(!this->tree)
    {
        this->tree = new SimpleTree();
    }

    for(int i = 0; i < n; ++i)
        this->tree->insert(array[i]);
}

Set::Set(const Set &original):
    tree(new SimpleTree(original.tree)) //ugly hack
{
}

Set Set::unite(const Set &rhs) const
{
    Set result;

    for(Tree::Iterator it = tree->begin(), end = tree->end(); it != end; ++it)
        result.tree->insert(*it);

    for(Tree::Iterator it = rhs.tree->begin(), end = rhs.tree->end(); it != end; ++it)
        if(result.tree->find(*it) == result.tree->end())
            result.tree->insert(*it);

    return result;
}

Set Set::intersect(const Set &rhs) const
{
    Set result;

    for(Tree::Iterator it = tree->begin(), end = tree->end(); it != end; ++it)
        if(rhs.tree->find(*it) != rhs.tree->end())
            result.tree->insert(*it);

    return result;
}

Set Set::substract(const Set &rhs) const
{
    Set result;

    for(Tree::Iterator it = tree->begin(), end = tree->end(); it != end; ++it)
        if(rhs.tree->find(*it) == rhs.tree->end())
            result.tree->insert(*it);

    return result;
}

Set Set::symmetricSubstract(const Set &rhs) const
{
    Set result;

    for(Tree::Iterator it = tree->begin(), end = tree->end(); it != end; ++it)
        if(rhs.tree->find(*it) == rhs.tree->end())
            result.tree->insert(*it);

    for(Tree::Iterator it = rhs.tree->begin(), end = rhs.tree->end(); it != end; ++it)
        if(tree->find(*it) == tree->end())
            result.tree->insert(*it);

    return result;
}
