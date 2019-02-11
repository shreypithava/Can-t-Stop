//
//  main.cpp
//  P1-Shrey
//
//  Created by Shrey Pithava on 1/25/18.
//  Copyright © 2018 Shrey Pithava. All rights reserved.
//
#ifndef dice_hpp
#define dice_hpp

#include "tools.hpp"
#define INPUT "input.txt"
//-------------------------------------------------------------------------------------------------
//------------------Dice class---------------------------------------------------------------------
class Dice {
protected:
    int* array;
    void roll();
    static int noD;
    const int nDice;
    Dice( int n = 4 ): nDice( n ) {
        if ( n <= 0 ) fatal( "Has to be greater than zero" );
        else {
            array = new int[n];
            ++noD;
        }
    }
    ~Dice() {
        if ( array ) delete array;
        --noD;
        if(!noD) cout << "Dice: " << noD << endl;
    }
public:
    ostream& print( ostream& );
};
inline ostream& operator <<( ostream& out, Dice& d ){ return d.print( out ); }
//-------------------------------------------------------------------------------------------------
//-------The Game dice class-----------------------------------------------------------------------
class CantStopDice : public Dice {
protected:
    static int noC;
    int sumArray[2];
public:
    CantStopDice(): Dice(4) { ++noC; }
    ~CantStopDice() {
        --noC;
        if(!noC) cout << "CantStopDice: " << noC << endl;
    }
    int* roll();
};
//-------------------------------------------------------------------------------------------------
//-----------------Artificial dice-----------------------------------------------------------------
class FakeDice : public CantStopDice {
private:
    ifstream in;
    int* diceData;
    int dataCount;
    static int noF;
    void readData();
public:
    FakeDice(): diceData( new int[200] ), in( INPUT ), dataCount(0), CantStopDice() {
        readData();
        ++noF;
    }
    ~FakeDice() {
        delete[] diceData;
        --noF;
        if(!noF) cout << "FakeDice: " << noF << endl;
    }
    int* roll();
};
//-------------------------------------------------------------------------------------------------
#endif /* dice_hpp */


