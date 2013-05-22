//
//  SFMapScene.cpp
//  ShakeForFood
//
//  Created by Yang David on 5/21/13.
//
//

#include "SFMapScene.h"
#include "SFGamePlayer.h"
#include "SFSceneManager.h"
#include "CCGeometry.h"
#include <cmath>



CCScene * SFMapScene::scene(){
    
    CCScene * scene = CCScene::node();
    SFMapScene * mapLyer = SFMapScene::node();
    
    scene->addChild(mapLyer);
    
    return scene;
    
}

bool SFMapScene::init(){
    
    //CCSize size = CCDirector::sharedDirector()->getWinSize();
   
    player = new SFGamePlayer("player.png");
    player->setPosition(ccp(30,120));
    this->addChild(player->getSprite(),kZPlayers,0);
    
    
    targetPoint = player->getPosition();
    enemyList = CCArray::arrayWithCapacity(20);
    
    mapLayer1 = new CCSprite();
    mapLayer1->autorelease();
    mapLayer1->initWithFile("back_img1.png");
    mapLayer1->setPosition(ccp(0, 0));
    
    mapLayer2 = new CCSprite();
    mapLayer2->autorelease();
    mapLayer2->initWithFile("back_img1.png");
    mapLayer2->setPosition(ccp(242, 0));
    
    this->addChild(mapLayer1,kZMap,1);
    this->addChild(mapLayer2,kZMap,2);
    
    
    playerlife = 100;
    lifeHp = new CCSprite();
    lifeHp->initWithFile("blood.png");
    lifeHp->setAnchorPoint(ccp(0, 0));
    lifeHp->setPosition(ccp(95, 20));
    lifeHp->autorelease();
    this->addChild(lifeHp,kZHP,200);
    
    
    manaHp = new CCSprite();
    manaHp->initWithFile("Mana.png");
    manaHp->autorelease();
    manaHp->setAnchorPoint(ccp(0, 0));
    manaHp->setPosition(ccp(95, 0));
    this->addChild(manaHp,kZHP,200);
    
    bottomMenu = new CCSprite();
    bottomMenu->autorelease();
    bottomMenu->initWithFile("DownMenu.png");
    bottomMenu->setPosition(ccp(bottomMenu->getContentSize().width/2, bottomMenu->getContentSize().height/2));
    this->addChild(bottomMenu,kZDownMenu,100);
    this->setIsTouchEnabled(true);
    stepIndex =-1;
    
    
    
	
     playerBulletList = CCArray::arrayWithCapacity(20);
    
     scoreLabel = new  CCLabelTTF();
     scoreLabel->initWithString("0", "Arial", 30);
     scoreLabel->setAnchorPoint(ccp(0, 0));
     scoreLabel->setColor(ccc3(255, 255, 255));
     scoreLabel->setPosition(ccp(0,290));
     scoreLabel->autorelease();
     this->addChild(scoreLabel,kZLabel,301);
    
    
    spRocker= new CCSprite();
    spRocker->initWithFile("LeftPoint.png");
    spRocker->autorelease();
    
    spRockerBg = new CCSprite();
    spRockerBg->autorelease();
    spRockerBg->initWithFile("LeftPlane.png");
    
    
     joyStick = SFHRocker::rockerWithCenter(ccp(40.0f,30.0f),30.0f ,spRocker ,spRockerBg,false); 
     this->addChild(joyStick,kZJoyStick); 
     
     scheduleUpdate();
     schedule(schedule_selector(SFMapScene::playerFire), 0.3f);
     schedule(schedule_selector(SFMapScene::enemyrestart), 0.5f);
     
     return true;

}

void SFMapScene::updateLife(int deltalife){
    playerlife += deltalife;
    if (playerlife<=0) {
        playerlife =0;
        SFSceneManager::startPlay(kSceneTagGameOver);
    }
    else if( playerlife>=100){
        playerlife = 100;
        
    }
    
    lifeHp->setScaleX(playerlife/100.0);
}


void SFMapScene::enemyrestart(CCTimer dt){
    SFGameEnemy * enemy = new SFGameEnemy("enemy.png");
    enemyList->addObject(enemy);
    this->addChild(enemy,kZPlayers,100);
}

void SFMapScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
    
    CCSetIterator it = pTouches->begin();
    CCTouch * touch = (CCTouch*)(*it);
    targetPoint = touch->locationInView(touch->view());
    targetPoint = CCDirector::sharedDirector()->convertToGL(targetPoint);
}

void SFMapScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
    
}

void SFMapScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
    
    CCSetIterator it = pTouches->begin();
    CCTouch * touch = (CCTouch*)(*it);
    
     
    if (CCPoint::CCPointEqualToPoint(targetPoint,touch->locationInView(touch->view()))) {
        return;
    }
    
    targetPoint = touch->locationInView(touch->view());
    targetPoint = CCDirector::sharedDirector()->convertToGL(targetPoint);
    
}

void SFMapScene::playerFire(CCTimer dt){
    
    CCPoint herop = (player->getSprite())->getPosition();
    CCSize herosize = (player->getSprite())->getContentSize();
    int nowS = playerBulletList->count();
    SFGameBullet* newBullet = new SFGameBullet("bullet3456.png");
    newBullet->setPosition(ccp(herop.x + herosize.width, herop.y));
    newBullet->setType(0);
    this->addChild(newBullet->getSprite(),kZBulletBase + nowS);
    playerBulletList->addObject(newBullet);

}

void SFMapScene::update(float dt){
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
	CCPoint maplayer1p = mapLayer1->getPosition();
	CCPoint maplayer2p = mapLayer2->getPosition();
    
	mapLayer1->setPosition(ccp(maplayer1p.x - 5,maplayer1p.y));
	mapLayer2->setPosition(ccp(maplayer2p.x - 5,maplayer2p.y));
    
	if(maplayer2p.x < 0){
        float temp = maplayer2p.x + 242;
        mapLayer1->setPosition(ccp(temp,maplayer1p.y));
	}
	if(maplayer1p.x < 0){
        float temp = maplayer1p.x + 242;
        mapLayer2->setPosition(ccp(temp,maplayer2p.y));
	}
    
    for(int j = enemyList->count() - 1; j >= 0; j--)
    {
        SFGameEnemy *enemy = (SFGameEnemy *)(enemyList->objectAtIndex(j));
        
        if(enemy->getState() != -1)
        {
            enemy->tick();
            
            for(int i = playerBulletList->count() - 1; i >= 0; i--)
            {
                SFGameBullet * mybullet = (SFGameBullet *)(playerBulletList->objectAtIndex(i));
                
                if(enemy->collisionWithBullet(mybullet))
                {
                    enemyList->removeObjectAtIndex(j);
                    this->removeChild(enemy->getSprite(), true);
                    delete enemy;
                    
                    playerBulletList->removeObjectAtIndex(i);
                    this->removeChild(mybullet->getSprite(),true);
                    delete mybullet;
                    
                    playerscore++;
                    this->updateLife(1);
                    
                    //CCString *scoreLa = CCString::createWithFormat("%i",playerscore);
                    
                    char scoreLa[25];
                    snprintf(scoreLa, 25, "%i",playerscore);
                    scoreLabel->setString(scoreLa);
                    break;
                }
            }
        }
    }
    
    for(int i = 0; i < playerBulletList->count(); i++)
    {
        SFGameBullet* mybullet = (SFGameBullet *)(playerBulletList->objectAtIndex(i));
        mybullet->tick();
        
        if((mybullet->getSprite())->getPosition().x > size.width){
            
            playerBulletList->removeObjectAtIndex(i);
            this->removeChild(mybullet->getSprite(),true);
            
            delete mybullet;
        }
    }
    
    for(int i = 0; i < enemyList->count(); i++)
    {
        SFGameEnemy* enemy = (SFGameEnemy *)(enemyList->objectAtIndex(i));
        if((enemy->getSprite())->getPosition().x < 0){
            this->updateLife(-10);
            
            enemyList->removeObjectAtIndex(i);
            this->removeChild(enemy->getSprite(),true);
            delete enemy;
        }
    }
    
    
    //let player move to targetPoint
    if(joyStick->getVelocity() > 0)
    {
        CCPoint orginP = (player->getSprite())->getPosition();
        CCPoint direP = ccpMult(joyStick->getDirection(), player->getSpeed());
        CCPoint lastP = ccp(orginP.x + direP.x, orginP.y + direP.y);
        float minx = (player->getSprite())->getContentSize().width/2;
        
        float maxx = size.width - minx;
        
        float miny = bottomMenu->getContentSize().height + (player->getSprite())->getContentSize().height/2;
        
        float maxy = size.height - (player->getSprite())->getContentSize().height/2;
        
        if(lastP.x <= minx) lastP.x = minx;
        else if(lastP.x >= maxx) lastP.x = maxx;
        if(lastP.y <= miny) lastP.y = miny;
        else if(lastP.y >= maxy) lastP.y = maxy;
        (player->getSprite())->setPosition(lastP);
        
    }
}