//
//  score.cpp
//  P11-Shrey
//
//  Created by Shrey Pithava on 02/05/18.
//  Copyright © 2018 Shrey Pithava. All rights reserved.
//

#include "score.hpp"

int ScoreBoard::noS = 0;
//---------------------------------------------------------------------
//---------------------Score Print function----------------------------
ostream& Score::print ( ostream& out ) {
    cout << "| Games: " << array[0] << " |" << " Won: "<< array[1] << " |  ";
    for (int col = 2; col <= 12; col++) { out << array[col] << " "; }
    out << endl;
    return out;
}
//---------------------------------------------------------------------
//---------------Scoreboard print function----------------------------
void ScoreBoard::print( Player* p ) {
    SBoard::iterator it;
    it = theMap.begin();
    while ( it != theMap.end() ) {
        if ( it->first == "Game" || it->first == p->plyrName() ) {
            cout << it->first << "\t";
            it->second.print( cout );
        }
        ++it;
    }
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
void Score::update( int score, const int* colNames ) {
    for (int k = 0; colNames[k] ; k++) { array[colNames[k]]++; }
    if ( score == 3 ) { array[1]++; }
    array[0]++;
}
//-------------------------------------------------------------------
void ScoreBoard::update( const string name, const int* theColumns, const int pScore ) {
    bool flag = false;
    for(;;) {
        SBoard::iterator it;
        it = theMap.begin();
        while ( it != theMap.end()) {
            if ( it->first == name ) {
                it->second.update( pScore, theColumns );
                flag = true;
                break;
            }
            ++it;
        }
        if ( !flag ) {
            score[scoreNo] = new Score;
            score[scoreNo]->update( pScore, theColumns );
            theMap.insert( SBPair ( name, *score[scoreNo] ) );
            scoreNo++;
        }
        break;
    }
}
//-----------------------------------------------------------------------
void Score::serialize( ostream& write ) {
    for (int col = 0; col <= 12; col++) { write << array[col] << " "; }
    write << endl;
}
//---------------------------------------------------------------------
void ScoreBoard::serialize() {
    gameUpdate();
    ofstream toFile( OUTF );
    SBoard::iterator it;
    it = theMap.begin();
    while ( it != theMap.end() ) {
        toFile << left << it->first << setw(5) << " ";
        it->second.serialize( toFile );
        ++it;
    }
}
//---------------------------------------------------------------------
void Score::realize( istream& read ) {
    int count = 0;
    while ( count < 13 ) {
        read >> array[count];
        ++count;
    }
}
//--------------------------------------------------------------------
void ScoreBoard::realize() {
    ifstream inFile( INF );
    while ( inFile ) {
        string name;
        inFile >> name;
        if (!inFile) break;
        score[scoreNo] = new Score;
        score[scoreNo]->realize( inFile );
        theMap.insert( SBPair ( name,* score[scoreNo] ) );
    }
}
//--------------------------------------------------------------------
void ScoreBoard::gameUpdate() {
    SBoard::iterator itOut;
    itOut = theMap.begin();
    while ( itOut->first != "Game" ) { ++itOut; }
    for (int column = 2;column < 13;) {
        itOut->second.array[column] = 0;
        SBoard::iterator itIn;
        itIn = theMap.begin();
        while ( itIn != theMap.end() ) {
            if ( itIn->first != "Game" ) { itOut->second.array[column] += itIn->second.array[column]; }
            ++itIn;
        }
        ++column;
    }
    itOut->second.array[0] += 1;
}
