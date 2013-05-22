//
//  SFStartScene.cpp
//  ShakeForFood
//
//  Created by Yang David on 5/17/13.
//
//

#include "SFStartScene.h"
#include "SFGamePlayer.h"
#include "SFMapScene.h"
#include "SFSceneManager.h"
#include  <cmath>

CCScene * SFStartScene::scene(){
    
    CCScene * scene = CCScene::node();
    SFStartScene * layer = SFStartScene::node();
    
    scene->addChild(layer);
    
    return scene;
}


bool SFStartScene::init(){
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
	maplayer =new CCSprite();
    maplayer->initWithFile("mainBG.png");
	maplayer->setAnchorPoint(ccp(0,0));
	maplayer->setPosition( ccp(0,0) );
    maplayer->autorelease();
	this->addChild(maplayer);
    
	setIsTouchEnabled(true);
    
    logoTitle =new CCSprite();
    logoTitle->initWithFile("titleLogo.png");
    logoTitle->setPosition(ccp(size.width + logoTitle->getContentSize().width/2,
                               size.height * 3/4));
    logoTitle->autorelease();
    this->addChild(logoTitle);
    logoTitle->runAction(CCMoveBy::actionWithDuration(0.5, ccp(-size.width/2,0)));
    
    {
        CCMenuItemFont* touchToStart =
        CCMenuItemFont::itemFromString("开始", this, menu_selector(SFStartScene::buttonPressed));
        touchToStart->setTag(kTagTouchStart);
        
        touchToStart->setPosition(ccp(size.width/2, size.height/3));
        
        mainMenu = CCMenu::menuWithItems(touchToStart, NULL);
        mainMenu->setPosition(CCPointZero);
        this->addChild(mainMenu);
    }
    
    {
        CCMenuItemFont* newgameM =
        CCMenuItemFont::itemFromString("新游戏", this, menu_selector(SFStartScene::buttonPressed));
        
        newgameM->setTag(kTagNewGame);
        newgameM->setPosition(ccp(size.width/2, size.height/3));
        
        CCMenuItemFont* exitGameN =
        CCMenuItemFont::itemFromString("退出", this, menu_selector(SFStartScene::buttonPressed));
        exitGameN->setTag(kTagExit);
        exitGameN->setPosition(ccp(size.width/2, size.height / 5));
        
        subMenu = CCMenu::menuWithItems(newgameM, exitGameN,NULL);
        subMenu->setPosition(CCPointZero);
        this->addChild(subMenu);
        subMenu->setIsVisible(false);
    }
    
    return true;
}

void SFStartScene::buttonPressed(cocos2d::CCMenuItem * obj){
    
    switch (obj->getTag()) {
        case kTagTouchStart:
            mainMenu->setIsVisible(false);
            subMenu->setIsVisible(true);
            break;
        case kTagNewGame:
            SFSceneManager::startPlay(kSceneTagPlayerSelect);
            break;
        case kTagExit:
            break;
        default:
            break;
    }
}

void SFStartScene::update(float dt){
    
}

void SFStartScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
    
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    
    CCPoint targetPoint = touch->locationInView(touch->view());
    targetPoint = CCDirector::sharedDirector()->convertToGL( targetPoint );
}

void SFStartScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
    
}

void SFStartScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
    
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    CCPoint targetPoint = touch->locationInView(touch->view());
    targetPoint = CCDirector::sharedDirector()->convertToGL( targetPoint );
}
