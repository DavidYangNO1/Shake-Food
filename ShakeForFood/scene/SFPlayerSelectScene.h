//
//  SFPlayerSelectScene.h
//  ShakeForFood
//
//  Created by Yang David on 5/21/13.
//
//

#ifndef __ShakeForFood__SFPlayerSelectScene__
#define __ShakeForFood__SFPlayerSelectScene__

#include <iostream>
#include "SFPlayerSelectScene.h"
#include "cocos2d.h"

using namespace cocos2d;

class SFPlayerSelectScene : public CCLayer{
    
    
public:
    
private:
    enum TagButtons{
      
        kTagLeftButton = 40,
        kTagRightButton,
        kTagNewGame,
        kTagExit
    };
    
    enum currentProfession{
        kPSoldier =0,
        kPArcher,
        kPwizard,
        kPsum
    };
    
    int nowProfession;
    
    CCSprite * mapLayer1;
    CCSprite * playerSoldier;
    CCSprite * playerWizard;
    CCSprite * playerArcher;
    
    CCMenu * LRButtonMenu;
    CCLabelTTF * contentText;
    
    void bbuttonPressed(CCMenuItem* obj);
    void professionChanged();
    
public:
    virtual bool init();
    void update(float dt);
    static CCScene * scene();
    
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    
    LAYER_NODE_FUNC(SFPlayerSelectScene);
};


#endif /* defined(__ShakeForFood__SFPlayerSelectScene__) */
