//
//  SFMapScene.h
//  ShakeForFood
//
//  Created by Yang David on 5/21/13.
//
//

#ifndef __ShakeForFood__SFMapScene__
#define __ShakeForFood__SFMapScene__

#include <iostream>
#include "cocos2d.h"
#include "SFGamePlayer.h"
#include "SFGameBullet.h"
#include "SFGameEnemy.h"
#include "SFHRocker.h"

#include "SimpleAudioEngine.h"

#define joyStickPoint cpp(40,30)
#define joyStickRadius 30

using namespace cocos2d;

class SFMapScene : public CCLayer {
    
public:
    
    virtual bool init();
    void updateLife(int deltalife);
    void enemyrestart(CCTimer dt);
    void playerFire(CCTimer dt);
    void update(float dt);
    
    static cocos2d::CCScene * scene();
    
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    
    LAYER_NODE_FUNC(SFMapScene);
    
private:
    enum spriteZ{
      kZMap =0,
      kZPlayers,
      kZHP,
      kZLabel,
      kZDownMenu,
      kZJoyStick,
      kZBulletBase
    };
    
    CCArray * playerBulletList;
    SFGamePlayer * player;
    CCArray * enemyList;
    CCPoint targetPoint;
    SFHRocker * joyStick;
    
    int stepIndex;
    int playerlife;
    int playerscore;
    CCSprite * mapLayer1;
    CCSprite * mapLayer2;
    CCSprite * lifeHp;
    CCSprite * manaHp;
    CCSprite * bottomMenu;
    
    CCLabelTTF * scoreLabel;
    CCSprite * spRocker;
    CCSprite * spRockerBg;

    
    
};


#endif /* defined(__ShakeForFood__SFMapScene__) */
