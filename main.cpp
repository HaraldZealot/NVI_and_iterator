#include <iostream>
#include <simpletree.h>

using namespace std;

int main()
{
    try
    {
        int array[7] = {4, 2, 6, 1, 3, 5, 7};
        SimpleTree tree(array, 7);//  насамрэч я думаў тут кшталту палімарфізма Tree *tree = new SimpleTree(array,7);
        //  але так таксама працуе :)

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

        for(SimpleTree::Iterator it = tree.begin(), end = tree.end(); it != end; ++it)
            cout << *it << " ";

        cout << endl;
        int i = 0;

        for(SimpleTree::Iterator it = --(tree.end()), beg = tree.begin(); it != beg && i < 10; --it, ++i)
            cout << *it << " ";

        cout << *tree.begin() << endl;
    }
    catch(exception &e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}
