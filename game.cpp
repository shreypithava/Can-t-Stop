//
//  game.cpp
//  P4-Shrey
//
//  Created by Shrey Pithava on 3/2/18.
//  Copyright © 2018 Shrey Pithava. All rights reserved.
//

#include "game.hpp"

int Game::no = 0;
//-----------------------------------------------------------------------------------------------------------------
//---------------------------Creates a player----------------------------------------------------------------------
void Game::getNewPlayer( string theName, ColorEnum plyrcolor ) {
    Player* temp = new Player( theName, plyrcolor );
    list.insertBack( temp );
}
//-----------------------------------------------------------------------------------------------------------------
//----------------------------Gameplay-----------------------------------------------------------------------------
void Game::play() {
    firstPlayer();
    while ( status == begun ) { status = oneTurn( list.rPptr() ); }
    if ( status == done ) {
        Player* p = list.first();
        do {
            scoreBoard.update( p->plyrName(), p->wonColumns(), p->theScore() );
        } while ( p != list.next() );
    }
}
//-----------------------------------------------------------------------------------------------------------------
//---------------------A Player's turn-----------------------------------------------------------------------------
Gstatus Game::oneTurn( Player* p ) {
    cout << "\n1.Roll\t2.Stop\t3.Resign\t4.Show Scoreboard\t5.Quit." << endl;
    int choice = 0;
    bool rol[2] = { false };
    for (;;) {
        cin >> choice;
        try {
            if (cin.fail()) { throw "Insert a number"; }
            break;
        }
        catch ( char const* exception ) {
            cin.clear();
            cin.ignore(32767,'\n');
            cerr << exception << endl;
        }
    }
    switch ( choice ) {
        case 1:
            dicevals = dice.roll();
            cout << "Columns are " << dicevals[0] << " " << dicevals[1] << endl;
            if ( oneTowerLeft() && dicevals[0] != dicevals[1] && notInlist() ) {
                if (priority()) theBoard.move( dicevals[1] );
                else            theBoard.move( dicevals[0] );
            }
            else {
                for (int m = 0 ; m < 2 ; m++) { rol[m] = theBoard.move( dicevals[m] ); }
                if ( !rol[0] && !rol[1] ) {
                    cout << "You are Bust" << endl;
                    theBoard.bust();
                    list.next();
                }
            }
            theBoard.print( cout );
            list.turn();
            playerTower();
            cout << "Number of towers left: " << 3 - theBoard.countChecker() << endl;
            return begun;
        case 2:
            theBoard.stop( p );
            if ( p->wonGame() ) {
                p->print( cout );
                return done;
            }
            nextPlayer();
            theBoard.print( cout );
            list.turn();
            return begun;
        case 3:
            scoreBoard.update( p->plyrName(), p->wonColumns(), p->theScore() );
            theBoard.removePlayer( p );
            list.remove();
            theBoard.setPlayer( list.rPptr() );
            if ( list.onePlayer() ) {
                list.turn();
                cout << "Won the game" << endl;
                p->winGame();
                return done;
            }
            theBoard.print( cout );
            list.turn();
            return begun;
        case 4:
            scoreBoard.print( p );
            return begun;
        case 5:
            return quit;
        default:
            cout << "Enter between 1 and 4" << endl;
            return begun;
    }
}
//-----------------------------------------------------------------------------------------------------------------
//---------------------------------Checks for unused data----------------------------------------------------------
bool Game::checkData( string name, int color ) {
    for (int k = 0 ; k < 4 ; k++) {
        try {
            if ( name == names[k] && flag[color-1] ) { throw BadPlayer("Cannot reuse name and color"); }
            if ( name == names[k] )                  { throw BadName("Name already in use.\nEnter an unused name."); }
            if ( flag[color-1] )                     { throw BadColor("Color already in use\nEnter color number from list"); }
        }
        catch( BadColor& badcolor ) {
            badcolor.printException();
            return false;
        }
        catch( BadName& badname ) {
            badname.printException();
            return false;
        }
        catch ( BadPlayer& badplayer ) {
            badplayer.printException();
            return false;
        }
    }
    names[color-1] = name;
    flag[color-1] = true;
    return true;
}
//-----------------------------------------------------------------------------------------------------------------
//---------------------------Gets a number of players--------------------------------------------------------------
void Game::getPlayers() {
    int k = 0;
    string theName;
    int inputcolor;
    while (k < 2 || k > 4) {
        cout << "Enter No of Players(2-4)" << endl;
        cin >> k;
        try {
            if ( cin.fail() ) throw "Enter a number";
        }
        catch ( char const* exception ) {
            cin.clear();
            cin.ignore(32767,'\n');
            cerr << exception << endl;
        }
    }
    cin.ignore( 32767, '\n' );
    for (int m = 1; m <= k; m++) {
        cout << "Enter name and color of player no: " << m << endl;
        getline( cin, theName );
        for (int p = 1; p <= 4; ++p) {
            if ( !(flag[p-1]) ) {
                for ( int k = 0 ; (colorNames[p][k]) ; k++ ) {
                    if (!k) { cout << "(" << colorNames[p][0] << ")"; }
                    else    { cout << colorNames[p][k]; }
                }
                cout << endl;
            }
        }
        inputcolor = getColor();
        if ( !( checkData( theName, inputcolor ) ) ) { --m; }
        else {
            flag[inputcolor-1] = true;
            getNewPlayer( theName, static_cast<ColorEnum>(inputcolor) );
        }
    }
    list.turn();
}
//-----------------------------------------------------------------------------------------------------------------
//------------------------------------Priority function------------------------------------------------------------
bool Game::priority() {
    cout << "Select priority (1). " << dicevals[0] << ",\t(2). " << dicevals[1] << endl;
    int a;
    cin >> a;
    return ( a == 2 );
}
//-----------------------------------------------------------------------------------------------------------------
bool Game::notInlist() {
    const int* towers = theBoard.returnTowers();
    for (int slot = 0 ; slot < 3 ; slot++) {
        if ( towers[slot] == dicevals[0] || towers[slot] == dicevals[1] ) return false;
    }
    return true;
}
//-----------------------------------------------------------------------------------------------------------------
const int Game::getColor() {
    string al;
    for (;;) {
        getline( cin, al );
        transform( al.begin(), al.end(), al.begin(), ::toupper );
        if      (al == "O") { return 1; }
        else if (al == "Y") { return 2; }
        else if (al == "G") { return 3; }
        else if (al == "B") { return 4; }
        else                { cout << "Enter alphabet from list" << endl; }
    }
}
//-----------------------------------------------------------------------------------------------------------------
void Game::playerTower() {
    for (;;) {
        if (theBoard.countChecker()) {
            cout << "Columns you are playing for: ";
            const int* playerTowers = theBoard.returnTowers();
            for (int k = 0; k < theBoard.countChecker(); k++) { cout << playerTowers[k] << " "; }
            cout << endl;
        }
        break;
    }
}
