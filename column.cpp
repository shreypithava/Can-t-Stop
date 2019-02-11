//
//  column.cpp
//  P3-Shrey
//
//  Created by Shrey Pithava on 2/18/18.
//  Copyright © 2018 Shrey Pithava. All rights reserved.
//

#include "column.hpp"
//-------------------------------------------------------------------------------------------------------
int Column::no = 0;
//-------------------------------------------------------------------------------------------------------
const int Column::numBox[13] = {0, 0, 3, 5, 7, 9, 11, 13, 11, 9, 7, 5, 3};
//-------------------------------------------------------------------------------------------------------
//------------------------Print function-----------------------------------------------------------------
ostream& Column::print( ostream& out ) {
    out  << setw(2) << cNumber << ". "<< "(" << setw(2) << cLength << ") " << statusNames[cstatus] << " ";
    out << "|";
    for(int k = 1 ;k <= cLength ; k++) {
        for (int m = 0 ; m < 5 ; m++) {
            if ( marker[m] == k ) { out << colorNames[m][0]; }
            else                  { out << "-"; }
        }
        out << "|";
    }
    out << endl;
    return out;
}
//-------------------------------------------------------------------------------------------------------
const colStatus Column::state() { return cstatus; }
//-------------------------------------------------------------------------------------------------------
//------------------------Moves a tower------------------------------------------------------------------
bool Column::move( int a ) {
    if ( cstatus != captured ) {
        if ( cstatus == pending ) return true;
        if ( a ) marker[0] = marker[a];
        ++marker[0];
        if ( marker[0] == cLength ) cstatus = pending;
        return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------------------------
//---------------------Converts tower to Color------------------------------------------------------------
void Column::stop( Player* p ) {
    marker[ p->returnColour() ] = marker[0];
    if ( cstatus == pending ) {
        cstatus = captured;
        if ( p->wonColumn(cNumber) ) { cout << "This player won the game\n"; }
        for (int marker1 = 0 ; marker1 < 5; marker1++) {
            if ( p->returnColour() == marker1 ) continue;
            marker[ marker1 ] = 0;
        }
    }
    else marker[0] = 0;
}
//--------------------------------------------------------------------------------------------------------
void Column::bust() {
    if ( cstatus == pending ) cstatus = available;
    marker[0] = 0;
}
//--------------------------------------------------------------------------------------------------------
int Column::Marker( int no ) {
    if ( marker[no] != 0 ) {
        marker[0] = marker[no];
        return marker[no];
    }
    return 0;
}
//--------------------------------------------------------------------------------------------------------
void Column::removeMarker( int b ) { marker[b] = 0; }
//--------------------------------------------------------------------------------------------------------
void Column::removeTower() { marker[0] = 0; }
