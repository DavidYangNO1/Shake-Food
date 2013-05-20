//
//  SFHRocker.h
//  ShakeForFood
//
//  Created by Yang David on 5/20/13.
//
//

#ifndef __ShakeForFood__SFHRocker__
#define __ShakeForFood__SFHRocker__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class SFHRocker : public CCLayer {
    
public:
    static SFHRocker * rockerWithCenter(CCPoint inpoint,float inRadius,CCSprite * aJsSprite,CCSprite * aJsBg,bool isFollowRole);
    
    void Active();
    
    void Inactive();
    
private:
    
    SFHRocker * initWithCenter(CCPoint inpoint,float inRadius,CCSprite * aJsSprite,CCSprite * aJsBg,bool isFollowRole);
    
    CCPoint centerPoint;
    CCPoint currentPoint;
    
    bool active;
    float radius;
    CCSprite * JsSprite;
    bool _isFollowRole; // true follow user gesture
    
    void updatePos(float dt);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    LAYER_NODE_FUNC(SFHRocker);
public:
    CCPoint getDirection();
    float getVelocity();
};


#endif /* defined(__ShakeForFood__SFHRocker__) */
