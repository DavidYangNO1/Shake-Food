//
//  SFGameOverScene.h
//  ShakeForFood
//
//  Created by Yang David on 5/22/13.
//
//

#ifndef __ShakeForFood__SFGameOverScene__
#define __ShakeForFood__SFGameOverScene__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class SFGameOverScene : public CCLayer {
    
public:
    
    enum kGameOverZ{
      kZMap =0,
      kZPlayers,
      kZHP,
      kZLabel,
      kZDownMenu,
      kZJoyStick,
      kZBulletsBase = 100
    };
    
    CCSprite * mapLayer;
    CCLabelTTF * scoreLabel;
    void restartButtonPressed(CCObject * obj);
    virtual bool init();
    void update(float dt);
    static cocos2d::CCScene* scene();
    
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    
    LAYER_NODE_FUNC(SFGameOverScene);
};

#endif /* defined(__ShakeForFood__SFGameOverScene__) */
