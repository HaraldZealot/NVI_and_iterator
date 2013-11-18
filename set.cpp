#include "set.h"
#include <cassert>

Set::Set(const Set &original):
    tree(new SimpleTree(original.tree)) //ugly hack
{
}

Set Set::unite(const Set &rhs) const
{
    assert(tree && rhs.tree);//both sets have to initialised
    Set result;
    result.init<SimpleTree>();

    for(Tree::Iterator it = tree->begin(), end = tree->end(); it != end; ++it)
        result.tree->insert(*it);

    for(Tree::Iterator it = rhs.tree->begin(), end = rhs.tree->end(); it != end; ++it)
        if(result.tree->find(*it) == result.tree->end())
            result.tree->insert(*it);

    return result;
}

Set Set::intersect(const Set &rhs) const
{
    assert(tree && rhs.tree);//both sets have to initialised
    Set result;
    result.init<SimpleTree>();

    for(Tree::Iterator it = tree->begin(), end = tree->end(); it != end; ++it)
        if(rhs.tree->find(*it) != rhs.tree->end())
            result.tree->insert(*it);

    return result;
}

Set Set::substract(const Set &rhs) const
{
    assert(tree && rhs.tree);//both sets have to initialised
    Set result;
    result.init<SimpleTree>();

    for(Tree::Iterator it = tree->begin(), end = tree->end(); it != end; ++it)
        if(rhs.tree->find(*it) == rhs.tree->end())
            result.tree->insert(*it);

    return result;
}

Set Set::symmetricSubstract(const Set &rhs) const
{
    assert(tree && rhs.tree);//both sets have to initialised
    Set result;
    result.init<SimpleTree>();

    for(Tree::Iterator it = tree->begin(), end = tree->end(); it != end; ++it)
        if(rhs.tree->find(*it) == rhs.tree->end())
            result.tree->insert(*it);

    for(Tree::Iterator it = rhs.tree->begin(), end = rhs.tree->end(); it != end; ++it)
        if(tree->find(*it) == tree->end())
            result.tree->insert(*it);

    return result;
}
