//
//  SFHRocker.cpp
//  ShakeForFood
//
//  Created by Yang David on 5/20/13.
//
//

#include "SFHRocker.h"

void SFHRocker::updatePos(float dt){
    
    JsSprite->setPosition(ccpAdd(JsSprite->getPosition(), ccpMult(ccpSub(currentPoint, JsSprite->getPosition()), 0.5)));
}

void SFHRocker::Active(){
    
    if (!active) {
        active = true;
        schedule(schedule_selector(SFHRocker::updatePos));
        CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, false);
    }
}

void SFHRocker::Inactive(){
    if (active) {
        active=false;
        this->unschedule(schedule_selector(SFHRocker::updatePos));//
        CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
    }
}


CCPoint SFHRocker::getDirection()
{
    return ccpNormalize(ccpSub(currentPoint,centerPoint));
}

float SFHRocker::getVelocity()
{
    return ccpDistance(centerPoint, currentPoint);
}

SFHRocker* SFHRocker:: rockerWithCenter(CCPoint aPoint ,float aRadius ,CCSprite* aJsSprite,CCSprite* aJsBg,bool _isFollowRole){
    
    SFHRocker *jstick= new SFHRocker();
    
    if (jstick && jstick->init()) {
        
        jstick->initWithCenter(aPoint,aRadius,aJsSprite,aJsBg,_isFollowRole);
        jstick->autorelease();
        return jstick;
    }
    CC_SAFE_DELETE(jstick);
    return NULL;
}

bool SFHRocker::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    if (!active)
        return false;
    this->setIsVisible(true);
    
    
    CCPoint touchPoint = touch->locationInView(touch->view());
    touchPoint = CCDirector:: sharedDirector()->convertToGL(touchPoint);
    if(!_isFollowRole){
        if (ccpDistance(touchPoint, centerPoint) > radius){
            return false;
        }
    }
    currentPoint = touchPoint;
    if(_isFollowRole){
        centerPoint=currentPoint;
        JsSprite->setPosition(currentPoint);
        this->getChildByTag(88)->setPosition(currentPoint);
    }
    return true;
}

void  SFHRocker::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    CCPoint touchPoint = touch->locationInView(touch->view());
    touchPoint = CCDirector:: sharedDirector()->convertToGL(touchPoint);
    if (ccpDistance(touchPoint, centerPoint) > radius)
    {
        currentPoint =ccpAdd(centerPoint,ccpMult(ccpNormalize(ccpSub(touchPoint, centerPoint)), radius));
    }else {
        currentPoint = touchPoint;
    }
}
void  SFHRocker::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    currentPoint = centerPoint;
    if(_isFollowRole){
        this->setIsVisible(false);
    }
}

SFHRocker* SFHRocker::initWithCenter(CCPoint aPoint ,float aRadius ,CCSprite* aJsSprite,CCSprite* aJsBg,bool _isFollowRole){
    
    _isFollowRole =_isFollowRole;
    active = false;
    radius = aRadius;
    if(!_isFollowRole){
        centerPoint =aPoint;
    }else{
        centerPoint =ccp(0,0);
    }
    
    currentPoint = centerPoint;
    JsSprite = aJsSprite;
    JsSprite->setPosition(centerPoint);
    aJsBg->setPosition(centerPoint);
    aJsBg->setTag(88);
    this->addChild(aJsBg);
    this->addChild(JsSprite);
    if(_isFollowRole){
        this->setIsVisible(false);
    }
    this->Active();//激活摇杆
    return this;
}
