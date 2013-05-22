//
//  SFGameOverScene.cpp
//  ShakeForFood
//
//  Created by Yang David on 5/22/13.
//
//

#include "SFGameOverScene.h"
#include "SFGamePlayer.h"
#include "SFMapScene.h"
#include <cmath>

CCScene * SFGameOverScene::scene(){
    
    CCScene * scene = CCScene::node();
    SFGameOverScene * layer = SFGameOverScene::node();
    scene->addChild(layer);
    return scene;
}

bool SFGameOverScene::init(){
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
	mapLayer = new CCSprite();
    mapLayer->initWithFile("gameoverBG.jpeg");
	mapLayer->setAnchorPoint(ccp(0,0));
	mapLayer->setPosition( ccp(0,0) );
	this->addChild(mapLayer);
    
	setIsTouchEnabled(true);
    
    scoreLabel = CCLabelTTF::labelWithString("游戏结束", "Arial", 30);
    scoreLabel->setColor(ccc3(255, 255, 255));
    scoreLabel->setPosition(ccp(size.width/2,size.height * 3/4));
    this->addChild(scoreLabel);
    
    CCMenuItemImage* restartButton = CCMenuItemImage::itemFromNormalImage("CloseNormal.png", "CloseSelected.png", this, menu_selector(SFGameOverScene::restartButtonPressed));
    restartButton->setPosition(ccp(size.width/2, size.height/2));
    CCMenu* closeMenu = CCMenu::menuWithItems(restartButton, NULL);
    closeMenu->setPosition(CCPointZero);
    this->addChild(closeMenu);
    
    return true;
}


void SFGameOverScene::restartButtonPressed(cocos2d::CCObject* obj)
{
    CCDirector::sharedDirector()->replaceScene(SFMapScene::scene());
}

void SFGameOverScene::update(float dt){
    
}
void SFGameOverScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
    
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    
    CCPoint targetPoint = touch->locationInView(touch->view());
    targetPoint = CCDirector::sharedDirector()->convertToGL( targetPoint );
}

void SFGameOverScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
    
}

void SFGameOverScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
    
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    CCPoint targetPoint = touch->locationInView(touch->view());
    targetPoint = CCDirector::sharedDirector()->convertToGL( targetPoint );
}
