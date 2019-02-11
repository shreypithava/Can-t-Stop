//
//  player.cpp
//  P2-Shrey
//
//  Created by Shrey Pithava on 2/13/18.
//  Copyright © 2018 Shrey Pithava. All rights reserved.
//

#include "player.hpp"

int Player::no = 0;
//-----------------------------------------------------------------------------------------------------
//----------------print function for player------------------------------------------------------------
ostream& Player::print( ostream& out ) {
    out << "The player's name is " << playerName << " and it's color is " << colorNames[color] << endl;
    return out;
}
//-----------------------------------------------------------------------------------------------------
//---------column tracker------------------------------------------------------------------------------
bool Player::wonColumn( int x ) {
    nameOfCol[score] = x;
    score += 1;
    cout << "Column #" << x << " added" << endl;
    return ( score == 3 );
}
//-----------------------------------------------------------------------------------------------------
