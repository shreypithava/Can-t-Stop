//
//  player.hpp
//  P2-Shrey
//
//  Created by Shrey Pithava on 2/13/18.
//  Copyright © 2018 Shrey Pithava. All rights reserved.
//
#ifndef player_hpp
#define player_hpp

#include "tools.hpp"
#include "enums.hpp"

class Player {
private:
    int score;
    static int no;
    int* nameOfCol;
    const ColorEnum color;
    const string playerName;
public:
    Player( string& name, ColorEnum colour ): playerName( name ), color( colour ), score(0) {
        nameOfCol = new int[3];
        ++no;
    }
    ~Player() {
        delete[] nameOfCol;
        --no;
        if(!no) cout << "Players: " << no << endl;
    }
    bool wonColumn( int );
    ostream& print( ostream& );
    void winGame()                { score = 3; }
    int theScore()    const       { return score; }
    const int returnColour()      { return color; }
    int* wonColumns() const       { return nameOfCol; }
    string plyrName()             { return playerName; }
    bool wonGame()                { return ( score == 3 ); }
    string getColor()             { return colorNames[color]; }
};

inline ostream& operator <<( ostream& out, Player& p ) { return p.print( out ); }
#endif /* player_hpp */
