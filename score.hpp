//
//  score.hpp
//  P11-Shrey
//
//  Created by Shrey Pithava on 02/05/18.
//  Copyright © 2018 Shrey Pithava. All rights reserved.
//

#ifndef score_hpp
#define score_hpp

#include "tools.hpp"
#include "player.hpp"

#define INF  "record.txt"
#define OUTF "outfile.txt"
#define SBoard map<string, Score>
#define SBPair pair<string, Score>
//-------------------------------------------------------------------------------------
//--------------Score Class------------------------------------------------------------
class Score {
private:
    static int no;
    int array[13] = {0};
    void realize( istream& );
    void serialize( ostream& );
    void update( int, const int* );
    Score() {}
public:
    ~Score()  = default;
    ostream& print( ostream& );
    friend class ScoreBoard;
};

inline ostream& operator <<( ostream& out, Score& s ) { return s.print( out ); }
//-------------------------------------------------------------------------------------
//---------ScoreBoard Class------------------------------------------------------------
class ScoreBoard : public SBoard {
private:
    int scoreNo;
    SBoard theMap;
    static int noS;
    void realize();
    Score* score[7];
    void serialize();
    void gameUpdate();
public:
    ScoreBoard(): scoreNo(0) {
        realize();
        ++noS;
    }
    ~ScoreBoard() {
        serialize();
        while ( scoreNo > 0 ) delete score[--scoreNo];
        --noS;
        if(!noS) cout << "ScoreBoard: " << noS << endl;
    }
    void print( Player* );
    void update( const string, const int*, const int );
};

#endif /* score_hpp */
