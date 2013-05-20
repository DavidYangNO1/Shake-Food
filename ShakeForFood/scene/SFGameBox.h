//
//  SFGameBox.h
//  ShakeForFood
//
//  Created by Yang David on 5/20/13.
//
//

#ifndef __ShakeForFood__SFGameBox__
#define __ShakeForFood__SFGameBox__

#include <iostream>
#include "constants.h"
#include "SFGameTile.h"
#include "CCLayer.h"

using namespace cocos2d;

class SFGameBox : public CCNode {
    
public:
    
    SFGameTile * first;
    SFGameTile * second;
    
    CCSize size;
    CCArray * content;
    CCArray * readyToRemoveTiles;
    
    CCLayer * layer;
    SFGameTile * outBorderTile;
    
private:
    bool lock;
    
public:
    
    SFGameBox(CCSize inSize,int afactor);
    
    SFGameTile * objectAtXAndY(int posX,int posY);
    
    void checkWith(Orientation orient);
    bool check();
    void setLock(bool ff);
    bool isLocked();
    void removeSprite(SFGameTile * sender);
    void afterAllMoveDone();
    bool haveMore();
    int repair();
    int repairSingleColumn(int columnIndex);
};

#endif /* defined(__ShakeForFood__SFGameBox__) */
