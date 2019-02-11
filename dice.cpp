//
//  dice.cpp
//  P1-Shrey
//
//  Created by Shrey Pithava on 3/2/18.
//  Copyright © 2018 Shrey Pithava. All rights reserved.
//

#include "dice.hpp"

int Dice::noD = 0;
int CantStopDice::noC = 0;
int FakeDice::noF = 0;
//--------------------------------------------------------
//-------------Print function-----------------------------
ostream& Dice::print( ostream& out ) {
    out << "Dice values are: ";
    char ch(96);
    for (int k = 0; k < nDice; k++) { out << ++ch << "-" << array[k] << " "; }
    out << endl;
    return out;
}
//------------------------------------------------------------------
//-----------------rolls nDice dice---------------------------------
void Dice::roll() {
    srand( (unsigned)( time(NULL) ) );
    for (int k = 0; k < nDice; k++){ array[k] = rand() % 6 + 1; }
    print( cout );
}
//------------------------------------------------------------------
int* CantStopDice::roll() {
    Dice::roll();
    char c1,c2;
    sumArray[1] = 0;
    while (true) {
        cout << "Enter depicted and different Alphabets to select values" << endl;
        cin >> c1;
        cin.ignore();
        cin >> c2;
        if (static_cast<int>(c1) > 96 && static_cast<int>(c1) < 101 && static_cast<int>(c2) > 96 && static_cast<int>(c2) < 101 && c1 != c2) { break; }
    }
    sumArray[0] = array[ static_cast<int>(c1)-97 ] + array[ static_cast<int>(c2)-97 ];
    for (int m = 0; m < 4; m++) { sumArray[1] += array[m]; }
    sumArray[1] -= sumArray[0];
    return sumArray;
}
//------------------------------------------------------------------
int* FakeDice::roll() {
    for (int m = 0; m < 2; m++, dataCount++) {
        if ( !diceData[dataCount] ) { fatal("No values available(EOF)"); }
        sumArray[m] = diceData[dataCount];
    }
    cout << "Columns are " << sumArray[0] << " and " << sumArray[1] << endl;
    return sumArray;
}
//--------------------------------------------------------------
void FakeDice::readData() {
    int k = -1, dice1 = 0, dice2 = 0, slot = -1;
    while (in) {
        if (!in) { fatal("EOF"); }
        switch ((++k % 2) + 1) {
            case 1:
                in >> dice1;
                break;
            case 2:
                in >> dice2;
                diceData[++slot] = dice1 + dice2;
                break;
            default:
                break;
        }
    }
}
