//
//  SFGameSprite.h
//  ShakeForFood
//  
//  Created by Yang David on 5/17/13.
//  
//  @auther weflytotti@qq.com

#ifndef __ShakeForFood__SFGameSprite__
#define __ShakeForFood__SFGameSprite__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

/* ------------------------------------------------------------------
 *
 * ! Game Sprite base class
 *
 * ------------------------------------------------------------------*/

class SFGameSprite :public CCNode {
     
protected:
    CCSprite * gameSprite;
    int state;
public:
     
};

#endif /* defined(__ShakeForFood__SFGameSprite__) */
