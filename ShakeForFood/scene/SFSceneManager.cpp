//
//  SFSceneManager.cpp
//  ShakeForFood
//
//  Created by Yang David on 5/17/13.
//
//

#include "SFSceneManager.h"
#include "SFStartScene.h"
#include "SFGameOverScene.h"
#include "SFCoinsGameScene.h"
#include "SFMapScene.h"
#include "SFPlayerSelectScene.h"

void SFSceneManager::startPlay(int scenetag){
    
    CCLayer * layer ;
    switch (scenetag) {
        case kSceneTagStart:
            layer = SFStartScene::node();
            break;
        case kSceneTagMainGame:
            layer = SFMapScene::node();
            break;
        case kSceneTagGameOver:
            layer = SFGameOverScene::node();
            break;
        case kSceneTagPlayerSelect:
            layer = SFPlayerSelectScene::node();
            break;
        case kSceneTagCoinGame:
            layer = SFCoinsGameScene::node();
            break;
        default:
            break;
    }
    
    SFSceneManager::start(layer);
    
}

void SFSceneManager::start(cocos2d::CCLayer * layer){
    
    CCDirector* director = CCDirector::sharedDirector();
    CCScene* newScene = SFSceneManager::wrap(layer);
    
    if (director->getRunningScene())
    {
        director->replaceScene(newScene);
    }
    else
    {
        director->runWithScene(newScene);
    }
}

CCScene * SFSceneManager::wrap(CCLayer * layer){
    CCScene * scene = CCScene::node();
    scene->addChild(layer);
    return scene;
}
