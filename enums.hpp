//
//  enums.hpp
//  P2-Shrey
//
//  Created by Shrey Pithava on 2/13/18.
//  Copyright © 2018 Shrey Pithava. All rights reserved.
//
#ifndef enums_hpp
#define enums_hpp

#include "tools.hpp"

extern const string colorNames[];
extern const string statusNames[];
extern const string GameStatus[];

enum ColorEnum
{
    tower,
    orange,
    yellow,
    green,
    blue,
    max_colors,
};
//--------------------------------------------------
enum colStatus
{
    available,
    pending,
    captured,
    max_status,
};
//-------------------------------------------------
enum Gstatus
{
    begun,
    done,
    quit,
    max_G,
};

#endif /* enums_hpp */
