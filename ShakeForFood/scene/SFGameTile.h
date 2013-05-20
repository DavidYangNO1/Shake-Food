//
//  SFGameTile.h
//  ShakeForFood
//
//  Created by Yang David on 5/20/13.
//
//

#ifndef __ShakeForFood__SFGameTile__
#define __ShakeForFood__SFGameTile__

#include <iostream>
#include "cocos2d.h"
#include "constants.h"

using namespace cocos2d;

class SFGameTile :public CCNode {
    
    
public:
    int x;
    int y;
    int value;
    CCSprite * sprite;
    
    SFGameTile(int ax,int ay);
    ~SFGameTile();
    
    bool nearTile(SFGameTile * othertile);
    void trade(SFGameTile * othertile);
    CCPoint pixPosition();
};

#endif /* defined(__ShakeForFood__SFGameTitle__) */
