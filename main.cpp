#include <iostream>
#include <simpletree.h>

using namespace std;

int main()
{
    int array[7] = {4, 2, 6, 1, 3, 5, 7};
    SimpleTree tree(array, 7);//  насамрэч я думаў тут кшталту палімарфізма Tree *tree = new SimpleTree(array,7);
    //  але так таксама працуе :)

    for(Tree::Iterator it = tree.begin(), end = tree.end(); it != end; ++it)
        cout << *it << " ";

    cout << endl;
    return 0;
}

