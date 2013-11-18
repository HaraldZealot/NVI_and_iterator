#include <iostream>
#include "simpletree.h"
#include "set.h"

using namespace std;

class ConsoleSet: public Set
{
    public:
        ConsoleSet(): Set() {}
        ConsoleSet(const Set &original): Set(original) {}
        ConsoleSet &operator=(const ConsoleSet &rhs) {Set::operator=(rhs); return *this;}
        void output(ostream &out) const;
};

ostream &operator<<(ostream &out, const ConsoleSet &set);

using namespace std;

int main()
{
    try
    {
        cout << "SimpleTree demonstartion:\n";
        const int n = 7;
        int array[n] = {4, 2, 6, 1, 3, 5, 7};
        SimpleTree tree(array, n);

        for(SimpleTree::Iterator it = tree.begin(), end = tree.end(); it != end; ++it)
            cout << *it << " ";

        cout << endl;
        SimpleTree::Iterator jt = tree.begin();
        ++jt;
        ++jt;
        ++jt;
        cout << *jt << endl;
        jt = tree.erase(jt);
        cout << *jt << endl;
        cout << *(--tree.find(8)) << endl;

        for(SimpleTree::Iterator it = tree.begin(), end = tree.end(); it != end; ++it)
            cout << *it << " ";

        cout << endl;
        int i = 0;

        for(SimpleTree::Iterator it = --(tree.end()), beg = tree.begin(); it != beg && i < 10; --it, ++i)
            cout << *it << " ";

        cout << *tree.begin() << endl;
        cout << "\n\n\nSet demonstartion:\n";
        ConsoleSet setA, setB;
        setA.init<SimpleTree>(array, n);
        int brray[3] = {4, 8, 10};
        setB.init<SimpleTree>(brray, 3);
        cout << setA << " U " << setB << " = " << setA.unite(setB) << endl;
        cout << setA << " X " << setB << " = " << setA.intersect(setB) << endl;
        cout << setA << " / " << setB << " = " << setA.substract(setB) << endl;
        cout << setB << " / " << setA << " = " << setB.substract(setA) << endl;
        cout << setA << " A " << setB << " = " << setA.symmetricSubstract(setB) << endl;
    }
    catch(exception &e)
    {
        cout << e.what() << endl;
    }

    return 0;
}

ostream &operator<<(ostream &out, const ConsoleSet &set)
{
    set.output(out);
    return out;
}

void ConsoleSet::output(ostream &out) const
{
    const Tree *tree = this->getTreePointer();
    out << "{";

    for(Tree::Iterator it = tree->begin(), end = tree->end(); it != end;)
    {
        out << *it;
        out << (++it == end ? "}" : ", ");
    }
}
