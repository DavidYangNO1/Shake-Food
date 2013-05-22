//
//  SFPlayerSelectScene.cpp
//  ShakeForFood
//
//  Created by Yang David on 5/21/13.
//
//

#include "SFPlayerSelectScene.h"
#include "SFSceneManager.h"
#include <cmath>
using namespace cocos2d;


CCScene * SFPlayerSelectScene::scene(){
    
    CCScene * scene = CCScene::node();
    SFPlayerSelectScene * layer = SFPlayerSelectScene::node();
    scene->addChild(layer);
    return scene;
}

bool SFPlayerSelectScene::init(){
    
    nowProfession = 0;
    
	CCSize size = CCDirector::sharedDirector()->getWinSize();
    
	mapLayer1 = new CCSprite();
    mapLayer1->initWithFile("selectbg.jpeg");
    mapLayer1->autorelease();
	mapLayer1->setAnchorPoint(ccp(0,0));
	mapLayer1->setPosition( ccp(0,0) );
	this->addChild(mapLayer1);
    
    playerSoldier = new CCSprite();
    playerSoldier->initWithFile("playersoldier.png");
    playerSoldier->autorelease();
    playerSoldier->setAnchorPoint(ccp(0,0));
    this->addChild(playerSoldier);
    
    playerArcher = new CCSprite();
    playerSoldier->initWithFile("playerHunter.png");
    playerSoldier->autorelease();
    playerArcher->setAnchorPoint(ccp(0,0));
    this->addChild(playerArcher);
    
    playerWizard =  new CCSprite();
    playerSoldier->initWithFile("playerWizard.png");
    playerSoldier->autorelease();
    playerWizard->setAnchorPoint(ccp(0,0));
    this->addChild(playerWizard);
    
    CCMenuItemImage* leftButton = CCMenuItemImage::itemFromNormalImage("AAleft.png", "AAleft.png", this, menu_selector(SFPlayerSelectScene::bbuttonPressed));
    
    leftButton->setTag(kTagLeftButton);
    leftButton->setPosition(ccp(leftButton->getContentSize().width/2, size.height/2));
    
    CCMenuItemImage * rightButton = CCMenuItemImage::itemFromNormalImage("AAright.png", "AAright.png", this, menu_selector(SFPlayerSelectScene::bbuttonPressed));
    rightButton->setTag(kTagRightButton);
    rightButton->setPosition(ccp(size.width - rightButton->getContentSize().width/2, size.height/2));
    
    LRButtonMenu = CCMenu::menuWithItems(leftButton,rightButton,NULL);
    LRButtonMenu->setPosition(CCPointZero);
    this->addChild(LRButtonMenu);
    
    contentText =  CCLabelTTF::labelWithString("Hello milk", CCSizeMake(size.width/2 - leftButton->getContentSize().width/2, size.height), CCTextAlignmentLeft, "Marker Felt", 20);
    contentText->setAnchorPoint(ccp(0,0));
    contentText->setPosition(ccp(leftButton->getContentSize().width , 0));
    this->addChild(contentText);
    
	setIsTouchEnabled(true);
    
    this->professionChanged();
    
    return true;
}

void SFPlayerSelectScene::bbuttonPressed(CCMenuItem* obj){
    
    switch (obj->getTag()) {
        case kTagLeftButton:
            nowProfession--;
            if(nowProfession < 0)
                nowProfession += kPsum;
            this->professionChanged();
            break;
        case kTagRightButton:
            nowProfession++;
            if(nowProfession >= kPsum)
                nowProfession -= kPsum;
            this->professionChanged();
            break;
        case kTagNewGame:
            SFSceneManager::startPlay(kSceneTagMainGame);
            break;
        case kTagExit:
            break;
        default:
            break;
    }
}

void SFPlayerSelectScene::professionChanged(){
    
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    playerSoldier->setIsVisible(false);
    playerArcher->setIsVisible(false);
    playerWizard->setIsVisible(false);
    
    CCSprite* cacheSprite;
    
    CCString *cacheText;
    
    switch (nowProfession) {
        case kPSoldier:
            cacheSprite = playerSoldier;
            cacheText =new CCString("战士\n生命恢复 10\n攻击力 10\n生命值 100\n按得越快，战士的子弹越大！");
            cacheText->autorelease();
            break;
        case kPArcher:
            cacheSprite = playerArcher;
            cacheText = new CCString("猎人\n生命恢复 5\n攻击力 10\n生命值 100\n拥有一个可以自动攻击敌人的宝宝！");
            cacheText->autorelease();
            break;
        case kPwizard:
            cacheText = new CCString("巫师\n生命恢复 5\n攻击力 10\n生命值 50\n可以消耗魔法进行大范围爆炸伤害！");
            cacheText->autorelease();
            cacheSprite = playerWizard;
            break;
        default:
            cacheSprite = playerSoldier;
            break;
    }
    cacheSprite->setIsVisible(true);
    cacheSprite->setPosition(ccp(size.width,60));
    cacheSprite->runAction(CCMoveBy::actionWithDuration(0.3, ccp(-size.width/2,0)));
    contentText->setString(cacheText->toStdString().c_str());
    
}

void SFPlayerSelectScene::update(float dt){
    
}

void SFPlayerSelectScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
    
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    CCPoint targetPoint = touch->locationInView(touch->view());
    targetPoint = CCDirector::sharedDirector()->convertToGL( targetPoint );
    
}

void SFPlayerSelectScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
    
}

void SFPlayerSelectScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
    
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    CCPoint targetPoint = touch->locationInView(touch->view());
    targetPoint = CCDirector::sharedDirector()->convertToGL( targetPoint );

}

