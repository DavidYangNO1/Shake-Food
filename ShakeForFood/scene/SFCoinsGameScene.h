//
//  SFCoinsGameScene.h
//  ShakeForFood
//
//  Created by Yang David on 5/22/13.
//
//

#ifndef __ShakeForFood__SFCoinsGameScene__
#define __ShakeForFood__SFCoinsGameScene__

#include <iostream>
#include "SFGameBox.h"
#include "cocos2d.h"
using namespace cocos2d;

class SFCoinsGameScene : public CCLayer {
    
public:
    //SFCoinsGameScene();
    ~SFCoinsGameScene();
    
    virtual bool init();
    static CCScene * scene();
    
    void changeWithTileABandSel(SFGameTile* a,SFGameTile* b,SEL_CallFuncND sel);
    
    void checkSenderandData(SFGameTile* sender,SFGameTile* data);
    void backcheckSenderandData(SFGameTile* sender,SFGameTile* data);
    void onEnterTransitionDidFinish();
    void afterOneShineTrun(CCSprite* sprite);
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    
    LAYER_NODE_FUNC(SFCoinsGameScene);
    
private:
    SFGameBox * box;
    SFGameTile * selectedTile;
    SFGameTile * firstOne;
};

#endif /* defined(__ShakeForFood__SFCoinsGameScene__) */
