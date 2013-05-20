//
//  SFGameSprite.cpp
//  ShakeForFood
//
//  Created by Yang David on 5/17/13.
//
//

#include "SFGameSprite.h"

SFGameSprite::SFGameSprite(void){
    
}

SFGameSprite::~SFGameSprite(){
    
}

SFGameSprite::SFGameSprite(char * name){
    
    gameSprite = new CCSprite();
    
    if (gameSprite && gameSprite->initWithFile(name)) {
        
        gameSprite->autorelease();
        return;
    }
    CC_SAFE_DELETE(gameSprite);
}

void SFGameSprite::tick(){
    
}


void SFGameSprite::setPosition(CCPoint inPoint){
    
    gameSprite ->setPosition(inPoint);
    
}

CCSprite * SFGameSprite::getSprite(){
    
    return gameSprite;
    
}

void SFGameSprite::setState(int inState){
    
    state = inState;
}

int SFGameSprite::getState(){
    
    return state;
}

bool SFGameSprite::collision(){
    
    return false;
    
}

CCSize SFGameSprite::getSize(){
    
    return gameSprite->getContentSize();
    
}
