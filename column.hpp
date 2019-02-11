//
//  column.hpp
//  P3-Shrey
//
//  Created by Shrey Pithava on 2/18/18.
//  Copyright © 2018 Shrey Pithava. All rights reserved.
//

#ifndef column_hpp
#define column_hpp

#include "tools.hpp"
#include "enums.hpp"
#include "player.hpp"

class Column {
private:
    static int no;
    const int cNumber;
    const int cLength;
    colStatus cstatus;
    int marker[5] = {0};
    static const int numBox[13];
public:
    Column( int colNumber ):  cNumber( colNumber ), cLength( numBox[colNumber] ), cstatus( available ) { ++no; }
    ~Column() {
        --no;
        if(!no) cout << "Columns: " << no << endl;
    }
    void bust();
    int Marker( int );
    void removeTower();
    void stop( Player* );
    bool move( int a = 0 );
    const colStatus state();
    void removeMarker( int );
    ostream& print( ostream& );
    int returnMarker( int a )     { return marker[a]; }
};
//-----------------------------------------------------------------------------------------
inline ostream& operator <<( ostream& out, Column& c ) { return c.print( out ); }

#endif /* column_hpp */
