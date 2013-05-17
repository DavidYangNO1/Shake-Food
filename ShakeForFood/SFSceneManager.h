//
//  SFSceneManager.h
//  ShakeForFood
//
//  Created by Yang David on 5/17/13.
//
//

#ifndef __ShakeForFood__SFSceneManager__
#define __ShakeForFood__SFSceneManager__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

enum SceneTag {
     kSceneTagStart= 0,
     kSceneTagPlayerSelect,
     kSceneTagMainGame,
     kSceneTagCoinGame,
     kSceneTagGameOver
};

class SFSceneManager {
    
public:
    static void startPlay(int scenetag = kSceneTagStart);
    
private:
    static void start(cocos2d::CCLayer * layer);
    static CCScene * wrap(CCLayer * layer);
};

#endif /* defined(__ShakeForFood__SFSceneManager__) */
