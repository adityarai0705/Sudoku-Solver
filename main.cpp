//
//  main.cpp
//  Sudoku Solver
//
//  Created by Aditya Rai on 28/11/21.
//

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int getGrid( int i, int j){
    int row, col;
    if( i <= 2) row = 1;
    else if( i >= 3 && i <= 5) row = 2;
    else row = 3;
    
    if( j <= 2) col = 1;
    else if( j >= 3 && j <= 5) col = 2;
    else col = 3;
    
    if( row == 1 && col == 1) return 0;
    else if( row == 1 && col == 2) return 1;
    else if( row == 1 && col == 3) return 2;
    else if( row == 2 && col == 1) return 3;
    else if( row == 2 && col == 2) return 4;
    else if( row == 2 && col == 3) return 5;
    else if( row == 3 && col == 1) return 6;
    else if( row == 3 && col == 2) return 7;
    else return 8;
}


bool solveSudoku(int** board, vector< pair< int, int>> solve, int itr, vector< unordered_set< int>> rows, vector< unordered_set< int>> cols, vector< unordered_set< int>> grids){
    
    if( itr >= solve.size())
        return true;
    
    int row = solve[ itr].first, col = solve[ itr].second;
    int griditr = getGrid( row, col);
    for( int value = 1; value <= 9; value++){
        if( rows[ row].find( value) == rows[ row].end() && cols[ col].find( value) == cols[ col].end() && grids[ griditr].find( value) == grids[ griditr].end()){
            rows[ row].insert( value);
            cols[ col].insert( value);
            grids[ griditr].insert( value);
            board[ row][ col] = value;
            if( solveSudoku(board, solve, itr + 1, rows, cols, grids)){
                return true;
            }
            rows[ row].erase( value);
            cols[ col].erase( value);
            grids[ griditr].erase( value);
            board[ row][ col] = 0;
        }
    }
    
    return false;
}


int main(int argc, const char * argv[]) {
        
    int** board = new int*[ 9];
    for( int i = 0; i < 9; i++)
        board[ i] = new int[ 9];
    vector< unordered_set< int>> rows( 9), cols( 9), grids( 9);
    
    vector< pair< int, int>> solve;
    
    cout<< "Enter elements of board, [ Replace empty elements by '_'] : "<< endl;
    cout<< "Do not Enter any space.\n";
    
    for( int i = 0; i < 9; i++){
        cout<< "Enter Row ( "<< i + 1<< " ) : ";
        string s; cin>> s;
        if( s.length() > 9 || s.length() < 9){
            cout<< "Invalid Input!\nProgram Terminated.\n";
            return 0;
        }
        for( int j = 0; j < 9; j++){
            if( s[ j] == '_'){
                solve.push_back( make_pair( i, j));
                board[ i][ j] = 0;
            }else if( s[ j] >= '1' && s[ j] <= '9'){
                board[ i][ j] = s[ j] - '0';
                rows[ i].insert( board[ i][ j]);
                cols[ j].insert( board[ i][ j]);
                grids[ getGrid( i, j)].insert( board[ i][ j]);
            }else{
                cout<< "Invalid Input!\nProgram Terminated.\n";
            }
        }
    }
    
    cout<< "Solving...\nPlease Wait...\n";
    
    if( solveSudoku( board, solve, 0, rows, cols, grids) ){
        cout<< "\n\n";
        for( int i = 0; i < 9; i++){
            for( int j = 0; j < 9; j++){
                cout<< board[ i][ j]<< " ";
            }
            cout<< endl;
        }
    }else{
        cout<< "\n\nNo Possible Solution Exists.";
    }
    
    cout<< "\n\nThank You.\n\n";
    
    return 0;
}
