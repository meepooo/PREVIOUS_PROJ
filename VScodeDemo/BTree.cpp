#include <iostream>

using namespace std;

struct BTnode
{
    int data;
    BTnode* left;
    BTnode* right;
};

int main()
{
    BTnode* root=new BTnode();
    root->data=8;

    cout << root->data << endl;
    return 0;
}