#include "AVLTree.h"
#include "RedBlackTree.h"
#include <time.h>
#include <fstream>
#include <sstream>
#include <vector>

void testInsert1(){
    RedBlackTree<int> RedBlacktree;
    RedBlacktree.insert(1);
    RedBlacktree.insert(4);
    RedBlacktree.insert(6);
    RedBlacktree.insert(3);
    RedBlacktree.insert(5);
    RedBlacktree.insert(7);
    RedBlacktree.insert(8);
    RedBlacktree.insert(2);
    RedBlacktree.display();
}
void testInsert2(){
    srand(time(NULL)); int a[20];
    RedBlackTree<int> RedBlacktree;
    for (int i = 0; i<20; i++){
        a[i] = rand()%20 + 1;
        RedBlacktree.insert(a[i]);
        cout<<a[i]<<" ";
    }
    cout<<endl;
    RedBlacktree.display();
}
void testRemove1(){
    RedBlackTree<int> RedBlacktree;
    RedBlacktree.insert(1);
    RedBlacktree.insert(4);
    RedBlacktree.insert(6);
    RedBlacktree.insert(3);
    RedBlacktree.insert(5);
    RedBlacktree.insert(7);
    RedBlacktree.insert(8);
    RedBlacktree.insert(2);
    RedBlacktree.display();
    cout<<"---------"<<endl;
    cout<<"After delete value 5: "<<endl; cout<<endl;
    RedBlacktree.remove(5);
    RedBlacktree.display();
    cout<<"---------"<<endl;
    cout<<"After delete value 1: "<<endl; cout<<endl;
    RedBlacktree.remove(1);
    RedBlacktree.display();
}
void testRemove2(){
    srand(time(NULL)); int a[20];
    RedBlackTree<int> RedBlacktree;
    for (int i = 0; i<20; i++){
        a[i] = rand()%20 + 1;
        RedBlacktree.insert(a[i]);
        cout<<a[i]<<" ";
    }
    cout<<endl;
    RedBlacktree.display();
    cout<<"---------"<<endl;
    cout<<"After delete value: "<<a[5]<<endl; cout<<endl;
    RedBlacktree.remove(a[5]);
    RedBlacktree.display();
    cout<<"---------"<<endl;
    cout<<"After delete value: "<<a[7]<<endl; cout<<endl;
    RedBlacktree.remove(a[7]); 
    RedBlacktree.display();   
}
void timeCount(void (*test)()){
    auto start = clock();
    // Begin test
    //...
    test();
    //...
    // End test
    auto end = clock();
    cout<<"Thoi gian chay chuong trinh: "<<(double)(end-start)/CLOCKS_PER_SEC<<"(s)\n";
}
void testCompare1AVL(){
    AVLTree<int> AVLtree;
    AVLtree.insert(1);
    AVLtree.insert(4);
    AVLtree.insert(6);
    AVLtree.insert(3);
    AVLtree.insert(5);
    AVLtree.insert(7);
    AVLtree.insert(8);
    AVLtree.insert(2);
    AVLtree.remove(5);
    AVLtree.remove(1);
    AVLtree.remove(7);
    AVLtree.remove(4);
    AVLtree.remove(6);
    AVLtree.remove(8);
    AVLtree.remove(3);
    AVLtree.remove(2);
}
void testCompare1RedBlackTree(){
    RedBlackTree<int> RedBlacktree;
    RedBlacktree.insert(1);
    RedBlacktree.insert(4);
    RedBlacktree.insert(6);
    RedBlacktree.insert(3);
    RedBlacktree.insert(5);
    RedBlacktree.insert(7);
    RedBlacktree.insert(8);
    RedBlacktree.insert(2);
    RedBlacktree.remove(5);
    RedBlacktree.remove(1);
    RedBlacktree.remove(7);
    RedBlacktree.remove(4);
    RedBlacktree.remove(6);
    RedBlacktree.remove(8);
    RedBlacktree.remove(3);
    RedBlacktree.remove(2);
}
void testCompare1(){
    timeCount(testCompare1AVL);
    timeCount(testCompare1RedBlackTree);
}
void testCompare2(){
    fstream input("data.txt");
    string s; getline(input, s);
    stringstream ss; ss<<s;
    int output;
    vector<int>v;
    while (ss>>output){
        v.push_back(output);
    }
    int n = v.size(); // n = 500000
    AVLTree<int> AVLtree;
    RedBlackTree<int>RedBlacktree;
    auto start_1 = clock();
    for (int i = 0; i<n; i++) AVLtree.insert(v[i]);
    for (int i = 1234; i<67890; i++) AVLtree.remove(v[i]);
    auto end_1 = clock();
    cout<<"Thoi gian chay chuong trinh 1: "<<(double)(end_1-start_1)/CLOCKS_PER_SEC<<"(s)\n";;
    auto start_2 = clock();
    for (int i = 0; i<n; i++) RedBlacktree.insert(v[i]);
    for (int i = 1234; i<67890; i++) RedBlacktree.remove(v[i]);
    auto end_2 = clock();
    cout<<"Thoi gian chay chuong trinh 2: "<<(double)(end_2-start_2)/CLOCKS_PER_SEC<<"(s)\n";;
}
void testCompare3(){
    AVLTree <int> AVLtree;
    RedBlackTree<int>RedBlacktree;
    for (int i = 0; i<7; i++){
        RedBlacktree.insert(i);
        AVLtree.insert(i);
    }
    RedBlacktree.display(); cout<<endl;
    AVLtree.display();
}
void testCompare4AVLTree(){
    AVLTree <int> AVLtree;
    for (int i = 1; i<=7; i++){
        AVLtree.insert(i);
    }
    for (int i = 0; i<20; i++){
        AVLtree.search(i);
    }
}
void testCompare4RedBlackTree(){
    RedBlackTree <int> RedBlacktree;
    for (int i = 1; i<=7; i++){
        RedBlacktree.insert(i);
    }
    for (int i = 0; i<20; i++){
        RedBlacktree.search(i);
    }
}
void testCompare4(){
    timeCount(testCompare4AVLTree);
    timeCount(testCompare4RedBlackTree);
}

int main(){
    testCompare4();
    return 0;
}