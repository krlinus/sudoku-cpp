#ifndef BOARD_HPP
#define BOARD_HPP
#include <unordered_set>
#include <functional>
#include <map>
using namespace std;

class Board {
    struct Cell {
        Cell();
        int value=0;
        int possible[9]={1,2,3,4,5,6,7,8,9};
        int box_exclusive[9]={0};
        int row_exclusive[9]={0};
        int col_exclusive[9]={0};
    };

    enum class Context {NONE, ERASE_POSSIBILITY, REFRESH, EXCL_TEST_SET, SET,
        increment_box_exclusivity_score, increment_col_exclusivity_score, increment_row_exclusivity_score,
        PRINT_NEIGH};
    Context erase_value_possibility (int r, int c, int val);
    Context refresh (int r, int c, int val);
    Context excl_set(int r, int c, int val, int excl_list[]);
    Context excl_test_set(int x, int y, int val);
    Context increment_box_exclusivity_score(int r, int c, int val);
    Context increment_row_exclusivity_score(int r, int c, int val);
    Context increment_col_exclusivity_score(int r, int c, int val);
    Context do_nothing(int r, int c, int val);
    Context print_cell(int r, int c, int val);

    Cell grid[9][9];
    void runHorizHair(int r, int c, int val,
        Board::Context (Board::*)(int,int,int));
    void runVertHair(int r, int c, int val,
        Board::Context (Board::*)(int,int,int));
    void runCrosshair(int r, int c, int val,
        Board::Context (Board::*)(int,int,int));
    void runCrossbrush(int r, int c, int val,
        Board::Context (Board::*)(int,int,int));
    void runHorizBrush(int r, int c, int val,
        Board::Context (Board::*)(int,int,int));
    void runVertBrush(int r, int c, int val,
        Board::Context (Board::*)(int,int,int));
    void run3x3(int r, int c, int val,
        Board::Context (Board::*)(int,int,int));
    void runFuncAll(int r, int c, int val,
        Board::Context (Board::*)(int,int,int));
    static map<Board::Context, Board::Context (Board::*)(
        int, int, int)> action;
    public:
    Board();
    Context set (int g[9][9]);
    void setValue(int r, int c, int v) ;
    void printBoard(bool = false);
    void print_neigh(int r, int c);
};

#endif
