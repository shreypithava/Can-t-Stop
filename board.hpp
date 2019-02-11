//
//  board.hpp
//  P6-Shrey
//
//  Created by Shrey Pithava on 10/03/18.
//  Copyright © 2018 Shrey Pithava. All rights reserved.
//

#ifndef board_hpp
#define board_hpp

#include "tools.hpp"
#include "player.hpp"
#include "column.hpp"

class Board {
private:
    int counter;
    Player* player;
    int tower[3] = {0};
    void createColumns();
    Column* backBone[13];
    static int no;
public:
    Board(): counter(0) {
        createColumns();
        ++no;
    }
    ~Board() {
        for (int k = 2; k <= 12; k++) {
            if( backBone[k] ) delete backBone[k];
        }
        --no;
        if(!no) cout << "Board: " << no << endl;
    }
    void bust();
    bool move( int );
    void stop( Player* );
    ostream& print( ostream& );
    void removePlayer( Player* );
    void setPlayer( Player* p )         { player = p; };
    const int* returnTowers()           { return tower; }
    const int countChecker()            { return counter; }
    bool oneTowerLeft()                 { return counter == 2; }
    bool allTowersUsed()                { return counter == 3; }
};
inline ostream& operator <<( ostream& out, Board& b ) { return b.print( out ); }

#endif /* board_hpp */
