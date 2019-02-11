//
//  game.hpp
//  P4-Shrey
//
//  Created by Shrey Pithava on 3/2/18.
//  Copyright © 2018 Shrey Pithava. All rights reserved.
//

#ifndef game_hpp
#define game_hpp

#include "dice.hpp"
#include "tools.hpp"
#include "enums.hpp"
#include "clist.hpp"
#include "score.hpp"
#include "board.hpp"
#include "player.hpp"
#include "exception.hpp"

class Game {
private:
    int* dicevals;
    ScoreBoard scoreBoard;
    CList<Player> list;
    Board theBoard;
    CantStopDice dice;
    Gstatus status;
    static int no;
    bool flag[4] = { false };
    string names[4] = {""};
    void play();
    const int getColor();
    bool priority();
    bool notInlist();
    void getPlayers();
    void getNewPlayer( int );
    Gstatus oneTurn( Player* );
    bool checkData( string, int );
    void playerTower();
    void getNewPlayer( string, ColorEnum );
    void nextPlayer()    { theBoard.setPlayer(list.next()); }
    void firstPlayer()   { theBoard.setPlayer(list.first()); }
    bool oneTowerLeft()  { return theBoard.oneTowerLeft(); }
public:
    Game(): status( begun ) {
        dicevals = new int[2];
        ++no;
        getPlayers();
        play();
    }
    ~Game() {
        --no;
        cout << "Game: " << no << endl;
    }
};

#endif /* game_hpp */

