//
//  SFStartScene.h
//  ShakeForFood
//
//  Created by Yang David on 5/17/13.
//
//

#ifndef __ShakeForFood__SFStartScene__
#define __ShakeForFood__SFStartScene__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;

class SFStartScene: public CCLayer {
    
private:
    
    enum TagButtons{
        kTagTouchStart = 40,
        kTagNewGame,
        kTagExit
    };
    
    CCSprite * maplayer;
    CCSprite * logoTitle;
    CCMenu * mainMenu;
    CCMenu * subMenu;
    void buttonPressed(cocos2d::CCMenuItem * obj);
    
public:
    virtual bool init();
    void update(float dt);
    static CCScene * scene();
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    
    LAYER_NODE_FUNC(SFStartScene);
};



#endif /* defined(__ShakeForFood__SFStartScene__) */
