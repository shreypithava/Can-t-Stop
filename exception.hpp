//
//  exception.hpp
//  P10-Shrey
//
//  Created by Shrey Pithava on 27/04/18.
//  Copyright © 2018 Shrey Pithava. All rights reserved.
//

#ifndef exception_hpp
#define exception_hpp

#include "tools.hpp"
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
class BadPlayer {
private:
    const string error;
public:
    BadPlayer( string bigError ): error( bigError ) {}
    ~BadPlayer() = default;
    void printException();
};
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
class BadName : public BadPlayer {
public:
    BadName( string nameError ): BadPlayer( nameError ) {}
    ~BadName() = default;
};
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
class BadColor : public BadPlayer {
public:
    BadColor( string colorError ): BadPlayer( colorError ) {}
    ~BadColor() = default;
};

#endif /* exception_hpp */
