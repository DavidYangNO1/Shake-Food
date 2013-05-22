//
//  SFCoinsGameScene.cpp
//  ShakeForFood
//
//  Created by Yang David on 5/22/13.
//
//

#include "SFCoinsGameScene.h"

CCScene * SFCoinsGameScene::scene(){
    
    CCScene * scene = CCScene::node();
    SFCoinsGameScene * layer = SFCoinsGameScene::node();
    scene->addChild(layer);
    return scene;
}

bool SFCoinsGameScene::init(){
    
    box = new SFGameBox(CCSize(kBoxWidth, kBoxHeight), 6);
    box->layer = this;
    box->layer->retain();
    box->setLock(true);
    setIsTouchEnabled(true);
    box->autorelease();
    box->retain();
    return true;
}

SFCoinsGameScene::~SFCoinsGameScene(){
    
    box->layer->release();
    box->release();
}

void SFCoinsGameScene::onEnterTransitionDidFinish(){
    
    box->check();
    
}

void SFCoinsGameScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
    
    if(box->isLocked())
        return;
	CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    CCPoint location = touch->locationInView(touch->view());
    location = CCDirector::sharedDirector()->convertToGL( location );
    
    int x = (location.x -kStartX) / kTileSize;
	int y = (location.y -kStartY) / kTileSize;
	
	if (selectedTile && selectedTile->x ==x && selectedTile->y == y)
		return;
    SFGameTile *tile = box->objectAtXAndY(x, y);
    
    if(selectedTile && selectedTile->nearTile(tile))
    {
        box->setLock(true);
        this->changeWithTileABandSel(selectedTile, tile, callfuncND_selector(SFCoinsGameScene::checkSenderandData));
        selectedTile = NULL;
    }
    else
    {
        selectedTile = tile;
        this->afterOneShineTrun(tile->sprite);
    }
}

void SFCoinsGameScene::changeWithTileABandSel(SFGameTile* a,SFGameTile* b,SEL_CallFuncND sel){
    
    
    CCFiniteTimeAction* actionA = CCSequence::actions(CCMoveTo::actionWithDuration(kMoveTileTime, b->pixPosition()),CCCallFuncND::actionWithTarget(this, sel, a),NULL);
    
    CCFiniteTimeAction* actionB = CCSequence::actions(CCMoveTo::actionWithDuration(kMoveTileTime, b->pixPosition()),CCCallFuncND::actionWithTarget(this, sel, b),NULL);
    
    a->sprite->runAction(actionA);
    b->sprite->runAction(actionB);
    
    a->trade(b);
    
}
void SFCoinsGameScene::checkSenderandData(SFGameTile* sender,SFGameTile* data){
   
    if(NULL == firstOne){
		firstOne = data;
		return;
	}
	
    bool result = box->check();
	if (result)
        box->setLock(false);
	else
    {
        changeWithTileABandSel(data, firstOne, callfuncND_selector(SFCoinsGameScene::backcheckSenderandData));
	}
    
    firstOne = NULL;
}

void SFCoinsGameScene::backcheckSenderandData(SFGameTile* sender,SFGameTile* data)
{
    if(NULL == firstOne)
    {
        firstOne = data;
        return;
    }
    firstOne = NULL;
    box->setLock(false);
}


void SFCoinsGameScene::afterOneShineTrun(CCSprite* asprite)
{
    if(selectedTile && asprite == selectedTile->sprite)
    {
        CCSprite* sprite = asprite;
        CCFiniteTimeAction* someAction =
        CCSequence::actions(CCScaleBy::actionWithDuration(kMoveTileTime, 0.5f),
                            CCScaleBy::actionWithDuration(kMoveTileTime, 2.0f),
                            CCCallFuncN::actionWithTarget(this, callfuncN_selector(SFCoinsGameScene::afterOneShineTrun)),NULL);
        sprite->runAction(someAction);
    }
}
