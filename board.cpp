//
//  board.cpp
//  P6-Shrey
//
//  Created by Shrey Pithava on 10/03/18.
//  Copyright © 2018 Shrey Pithava. All rights reserved.
//

#include "board.hpp"

int Board::no = 0;
//----------------------------------------------------------------------------------
//---------------------Print function-----------------------------------------------
ostream& Board::print( ostream& out ) {
    for (int k = 0; k <= 97; k++) out << "*";
    out << endl;
    for (int col1 = 2; col1 <= 12; col1++) {
        if (backBone[col1]) backBone[col1]->print(out);
    }
    for (int k = 0; k <= 97; k++) out << "*";
    out << endl;
    return out;
}
//----------------------------------------------------------------------------------
//----------------------moves tower-------------------------------------------------
bool Board::move( int column ) {
    for ( int col = 0; col <= 2; col++ ) {
        if ( tower[col] == column ) return backBone[column]->move();
    }
    if ( counter < 3 ) {
        if ( backBone[column]->returnMarker( player->returnColour() ) ) {
            if ( backBone[column]->move( player->returnColour() ) ) {
                tower[counter++] = column;
                return true;
            }
        }
        if ( backBone[column]->move() ) {
            tower[counter++] = column;
            return true;
        }
    }
    return false;
}
//----------------------------------------------------------------------------------
//-------------Converts towers to colors--------------------------------------------
void Board::stop( Player* p ) {
    for (int k = 0; k <= 2; k++) {
        if( tower[k] ) {
            backBone[ tower[k] ]->stop(p);
            tower[k] = 0;
        }
    }
    counter = 0;
}
//----------------------------------------------------------------------------------
//----------------Bust function-----------------------------------------------------
void Board::bust() {
    for (int k = 0; k <= 2; k++) {
        if ( tower[k] ) {
            backBone[ tower[k] ]->bust();
            tower[k] = 0;
        }
    }
    counter = 0;
}
//----------------------------------------------------------------------------------
//------------create columns--------------------------------------------------------
void Board::createColumns() {
    for (int k = 2; k <= 12; k++) { backBone[k] = new Column(k); }
}
//----------------------------------------------------------------------------------
//--------------Removes player's progress-------------------------------------------
void Board::removePlayer( Player* p ) {
    for (int column = 2; column <= 12; column++) {
        backBone[column]->removeMarker( p->returnColour() );
        backBone[column]->removeTower();
    }
    for (;counter > 0;) tower[--counter] = 0;
}
