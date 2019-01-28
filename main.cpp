#include <iostream>
#include "board.hpp"
using namespace std;

void test01() {
    cout << "Test 01 ----------------------------------------" << endl;
    Board b;
    //b.printBoard(true);
    int binit[][9]={{1,2,3,0,0,0,0,0,0},
    {4,5,6,0,0,0,0,0,0},
    {7,8,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0}};
    b.set(binit);
    b.printBoard(true);
    cout << "END:Test 01 ----------------------------------------" << endl;
}

void test02() {
    cout << "Test 02 ----------------------------------------" << endl;
    Board b;
    //b.printBoard(true);
    int binit[][9]={{1,2,3,4,5,6,7,8,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0}};
    b.set(binit);
    b.printBoard(true);
    cout << "END:Test 02 ----------------------------------------" << endl;
}

void test03() {
    cout << "Test 03 ----------------------------------------" << endl;
    Board b;
    //b.printBoard(true);
    int binit[][9]={
    {1,0,0,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0}};
    b.set(binit);
    b.printBoard(true);
    cout << "END:Test 03 ----------------------------------------" << endl;
}

void test98() {
    cout << "Test 98 ----------------------------------------" << endl;
    Board b;
    //b.printBoard(true);
    int binit[][9]={
    {0,0,6,8,0,7,0,0,0},
    {0,8,0,0,3,0,0,6,0},
    {9,2,3,0,0,0,0,0,7},
    {0,4,7,6,9,0,0,2,5},
    {6,0,0,0,8,0,0,0,3},
    {8,3,0,0,5,1,6,4,0},
    {5,0,0,0,0,0,2,3,1},
    {0,1,0,0,6,0,0,7,0},
    {0,0,0,1,0,9,4,0,0}};
    b.set(binit);
    //b.printBoard(true);
    b.printBoard();
    /*
     * 4 5 6 8 1 7 3 9 2 
     * 7 8 1 9 3 2 5 6 4 
     * 9 2 3 5 4 6 1 8 7 
     * 1 4 7 6 9 3 8 2 5 
     * 6 9 5 2 8 4 7 1 3 
     * 8 3 2 7 5 1 6 4 9 
     * 5 6 9 4 7 8 2 3 1 
     * 2 1 4 3 6 5 9 7 8 
     * 3 7 8 1 2 9 4 5 6 
     * END:Test 98 ----------------------------------------
     *
     */
    cout << "END:Test 98 ----------------------------------------" << endl;
}

void test99() {
    cout << "Test 99 ----------------------------------------" << endl;
    Board b;
    //b.printBoard(true);
    int binit[][9]={
    {0,9,0,0,3,0,8,6,0},
    {0,6,0,0,7,0,4,0,3},
    {0,8,1,0,0,0,0,0,2},
    {0,5,7,8,1,0,0,2,0},
    {0,3,0,4,0,9,0,1,0},
    {0,1,0,0,5,3,6,4,0},
    {8,0,0,0,0,0,2,5,0},
    {9,0,6,0,8,0,0,3,0},
    {0,4,5,0,6,0,0,8,0}};
    b.set(binit);
    //b.printBoard(true);
    /*
    7 9 4 2 3 5 8 6 1 
    5 6 2 1 7 8 4 9 3 
    3 8 1 6 9 4 5 7 2 
    4 5 7 8 1 6 3 2 9 
    6 3 8 4 2 9 7 1 5 
    2 1 9 7 5 3 6 4 8 
    8 7 3 9 4 1 2 5 6 
    9 2 6 5 8 7 1 3 4 
    1 4 5 3 6 2 9 8 7 
    */
    b.printBoard();
    cout << "END:Test 99 ----------------------------------------" << endl;
}

void test04() {
    cout << "Test 04 ----------------------------------------" << endl;
    Board b;
    //b.printBoard(true);
    int binit[][9]={
    {0,8,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,8,0},
    {0,0,0,0,0,0,0,0,0},
    {8,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,8,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,1,0,0,0,0,0,0}};
    b.set(binit);
    b.printBoard(true);
    b.printBoard();
    cout << "END:Test 04 ----------------------------------------" << endl;
}

int main() {
    //test01();
    //test02();
    //test03();
    //test04();
    //test98();
    test99();

/*
    for(int i=0;i<9;++i) {
        for(int j=0;j<9;++j) {
            int v;
            cin >> v;
            b.setValue(i,j,v);
        }
    }
    cout << "set vals" << endl;
    b.printBoard();
    int r=0,c=0;
    cin.clear();
    cin.ignore(INT_MAX);
    cout << "r & c:" ;
    cin >> r >> c;
    do {
        b.print_neigh(r, c);
        cout << "r & c:" ;
        cin >> r >> c;
    } while(r >=0 and c >= 0);
*/
    return 0;
}
