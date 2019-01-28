#include <iostream>
#include <map>
#include <utility>
#include <string>
#include "board.hpp"
using namespace std;

Board::Context Board::erase_value_possibility (
    int x, int y, int val) {
    if(val <=0) {
        return Board::Context::NONE;
    }
    cout << "setting impossibility of val " << val<< " at "<<x<<", "<<y<<endl;
	auto &c = grid[x][y];
    if(c.possible[val-1] > 0) {
        c.possible[val-1] = -val;
        refresh(x, y, val);
    }
    return Board::Context::NONE;
}


Board::Context Board::refresh (int x, int y, int val) {
    if(val <=0 or grid[x][y].value != 0) {
        return Board::Context::NONE;
    }
	auto &c = grid[x][y];
    int nposs=0;
    int pval=0;
    for(int i=0;i<9;++i) {
        if(c.possible[i] > 0) {
            nposs++;
            pval = i+1;
        }
    }
    if(nposs == 1 && c.value == 0) {
        setValue(x,y,pval);
    }
    return Context::NONE;
}

Board::Context Board::set (int g[9][9]) {
    for(int i=0;i<9;++i) {
        for(int j=0;j<9;++j) {
            setValue(i,j,g[i][j]);
        }
    }
    return Context::NONE;
}

Board::Context Board::excl_set(int x, int y, int val, int excl_list[]) {
    if(val <=0 or grid[x][y].value != 0) {
        return Board::Context::NONE;
    }
	auto &c = grid[x][y];

    if(++excl_list[val-1] >= 8) { // signifies that 8 neighboring cells
                                // have ruled out having val as a value
        setValue(x, y, val);
    }
    return Context::NONE;
}

Board::Context Board::excl_test_set(int x, int y, int val) {
    if(val <=0) {
        return Board::Context::NONE;
    }
    excl_set(x, y, val, grid[x][y].row_exclusive);;
    excl_set(x, y, val, grid[x][y].col_exclusive);
    excl_set(x, y, val, grid[x][y].box_exclusive);
    return Context::NONE;
}

Board::Context Board::do_nothing(int x, int y, int val) {
    if(val <=0) {
        return Board::Context::NONE;
    }
	auto &c = grid[x][y];
    return Context::NONE;
}

Board::Context Board::print_cell(int x, int y, int val) {
	auto &c = grid[x][y];
    cout << "r=" << x << ", c=" << y << endl;
    if(c.value != 0) {
        cout << "val=" << c.value << endl;
    } else {
        auto vlist = {c.possible, c.box_exclusive, c.col_exclusive, c.row_exclusive};
        cout << "Possible, box_excl, col_excl, row_excl vals: ";
        for(auto &arr : vlist) {
            for(int i=0;i< sizeof(arr)/sizeof(*arr); ++i) {
                cout << arr[i] << ", ";
            };
            cout << endl;
        }
    }
    return Context::NONE;
}

// tbd - do I even need this? pruning candidate
map<Board::Context, Board::Context (Board::*)(int, int, int)> Board::action = {
    make_pair<Context, Context (Board::*)(int,int,int)>(
    		Context::ERASE_POSSIBILITY, Board::erase_value_possibility),
    make_pair<Context, Context (Board::*)(int,int,int)>(
    		Context::REFRESH, Board::refresh),
    make_pair<Context, Context (Board::*)(int,int,int)>(
    		Context::increment_row_exclusivity_score,
            Board::increment_row_exclusivity_score),
    make_pair<Context, Context (Board::*)(int,int,int)>(
    		Context::increment_col_exclusivity_score,
            Board::increment_col_exclusivity_score),
    make_pair<Context, Context (Board::*)(int,int,int)>(
    		Context::increment_box_exclusivity_score,
            Board::increment_box_exclusivity_score),
    make_pair<Context, Context (Board::*)(int,int,int)>(
    		Context::PRINT_NEIGH, Board::print_cell)
};

Board::Board() {
}

Board::Cell::Cell() {
    cout << "cell ctr" << endl;
    for(int i=1;i<=9;++i) {
        possible[i-1]=i;
    }
    value=0;
}

void Board::print_neigh(int r, int c) {
    cout << "Crosshair" << endl;
    runCrosshair(r, c, 0, print_cell);
    cout << "\ncrossbrush" << endl;
    runCrossbrush(r, c, 0, print_cell);
    cout << "\nCell box" << endl;
    run3x3(r, c, 0, print_cell);
}

void Board::runVertHair(int r, int c, int val,
        Board::Context (Board::*func)(int,int,int)) {
   for(int i=0;i<9;++i) {
    	if(i != r) {
            cout << "runVertHair @ic " << i << ", " << c << endl;
        	Board::Context tmpctx = (this->*func)(i, c, val);
            if(tmpctx != Context::NONE)
                runVertHair(i, c, val, action[tmpctx]);
            if(i<r or i > r+2) {
                increment_box_exclusivity_score(i,c,val);
            }
        }
   }
}

void Board::runHorizHair(int r, int c, int val,
        Board::Context (Board::*func)(int,int,int)) {
   for(int i=0;i<9;++i) {
        if(i != c) {
            cout << "runHorizHair @ri " << r << ", " << i << endl;
        	Board::Context tmpctx = (this->*func)(r, i, val);
            if(tmpctx != Context::NONE)
                runHorizHair(r, i, val, action[tmpctx]);
            if(i<c or i > c+2) {
                increment_box_exclusivity_score(r,i,val);
            }
        }
    }
}

void Board::runCrosshair(int r, int c, int val,
        Board::Context (Board::*func)(int,int,int)) {
    cout << "runCrosshair @ val " << val << endl;
    runHorizHair(r, c, val, func);
    runVertHair(r, c, val, func);
/*
    for(int i=0;i<9;++i) {
        if(i != r) {
            runVertHair(r, i, val, action[Context::increment_col_exclusivity_score]);
        }
        if(i != c) {
            runHorizHair(i, c, val, action[Context::increment_row_exclusivity_score]);
        }
    }
*/    
}

void Board::runHorizBrush(int r, int c, int val,
        Board::Context (Board::*func)(int,int,int)) {
    int horiz = r-(r%3), vert = c-(c%3);
    for(int i=0;i<9;++i) {
        if(i < vert || i > vert+2) {
            if(horiz != r) (this->*func)(horiz, i, val);
            if(horiz+1 != r) (this->*func)(horiz+1, i, val);
            if(horiz+2 != r) (this->*func)(horiz+2, i, val);
        }
        
    }
}
void Board::runVertBrush(int r, int c, int val,
        Board::Context (Board::*func)(int,int,int)) {
    int horiz = r-(r%3), vert = c-(c%3);
    for(int i=0;i<9;++i) {
        if(i < horiz || i > horiz+2) {
            if(vert != c) (this->*func)(i, vert, val);
            if(vert+1 != c) (this->*func)(i, vert+1, val);
            if(vert+2 != c) (this->*func)(i, vert+2, val);
        }
        
    }
}

void Board::runCrossbrush(int r, int c, int val,
        Board::Context (Board::*func)(int,int,int)) {
    runHorizBrush(r, c, val, func);
    runVertBrush(r, c, val, func);
}

void Board::run3x3(int r, int c, int val,
        Board::Context (Board::*func)(int,int,int)) {
    const int box_x = r-(r%3), box_y=c-(c%3); // by box I mean 3x3 portion of grid
                                              // aligned to a corner or center
    for(int i=0;i<9;++i) {
        if(box_x+(i/3) != r or box_y+(i%3) != c) {
            Board::Context tmpctx = (this->*func)(box_x+(i/3), box_y+(i%3), val);
            if(tmpctx != Context::NONE)
                run3x3(r, i, val, action[tmpctx]);
        }
    }
}

void Board::runFuncAll(int r, int c, int val,
        Board::Context (Board::*func)(int,int,int)) {
 }

void Board::setValue(int r, int c, int val) {
    if(val <= 0 or val > 9) {
        cout << "not setting val " << val << endl;
        return;
    }
    auto &cell = grid[r][c];
    cell.value = val;
    for(int i=0;i<9;++i) {
        if(i != val-1) {
            cell.possible[i] = -(i+1); // set all vals to impossible 
        } else {
            cell.possible[i] = i+1;
        }
    }
    cout << "Calling runCrosshair for rc " <<r<<","<<c << endl;
    runCrosshair(r, c, val,action[Context::ERASE_POSSIBILITY]);

    cout << "Calling run3x3 for rc " <<r<<","<<c << endl;
    run3x3(r, c, val,action[Context::ERASE_POSSIBILITY]);

    cout << "Calling runVertBrush for rc col " <<r<<","<<c << endl;
    runVertBrush(r, c, val, action[Context::increment_col_exclusivity_score]);

    cout << "Calling runHorizBrush for rc row " <<r<<","<<c << endl;
    runHorizBrush(r, c, val, action[Context::increment_row_exclusivity_score]);

    cout << "Calling runVertBrush for rc box " <<r<<","<<c << endl;
    runVertBrush(r, c, val, action[Context::increment_box_exclusivity_score]);

    cout << "Calling runHorizBrush for rc box " <<r<<","<<c << endl;
    runHorizBrush(r, c, val, action[Context::increment_box_exclusivity_score]);
}

void Board::printBoard(bool pp) {
    for(int i=0;i<9;i++) {
        for(int j=0;j<9;j++) {
            cout << grid[i][j].value<< " ";
            if(pp) {
                cout << "possible at " << i << "," << j << ": [";
                for(auto & c : grid[i][j].possible) {
                    cout << c << ", ";
                }
                cout << "]" << endl;
                cout << "row excl at " << i << "," << j << ": [";
                for(auto & c : grid[i][j].row_exclusive) {
                    cout << c << ", ";
                }
                cout << "]" << endl;
                cout << "col excl at " << i << "," << j << ": [";
                for(auto & c : grid[i][j].col_exclusive) {
                    cout << c << ", ";
                }
                cout << "]" << endl;
                cout << "box excl at " << i << "," << j << ": [";
                for(auto & c : grid[i][j].box_exclusive) {
                    cout << c << ", ";
                }
                cout << "]" << endl;
            }
        }
        cout << endl;
    }
}

// consider removing these functions at some time
Board::Context Board::increment_row_exclusivity_score(
    int x, int y, int val) {
    if(val <=0 or grid[x][y].possible[val-1] < 0) {
        return Board::Context::NONE;
    }
    cout << "Setting row excl for val " << val << " at " << x << ", " << y << endl;
    excl_set(x, y, val, grid[x][y].row_exclusive);
    return Context::NONE;
}

Board::Context Board::increment_box_exclusivity_score(
    int x, int y, int val) {
    if(val <=0 or grid[x][y].possible[val-1] < 0) {
        return Board::Context::NONE;
    }
    cout << "Setting box excl for val " << val << " at " << x << ", " << y << endl;
	auto &c = grid[x][y];
    excl_set(x, y, val, c.box_exclusive);
    return Context::NONE;
}

Board::Context Board::increment_col_exclusivity_score(
    int x, int y, int val) {
    if(val <=0 or grid[x][y].possible[val-1] < 0) {
        return Board::Context::NONE;
    }
    cout << "Setting col excl for val " << val << " at " << x << ", " << y << endl;
	auto &c = grid[x][y];
    excl_set(x, y, val, c.col_exclusive);
    
    return Context::NONE;
}
