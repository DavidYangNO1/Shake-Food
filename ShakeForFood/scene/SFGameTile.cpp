//
//  SFGameTile.cpp
//  ShakeForFood
//
//  Created by Yang David on 5/20/13.
//
//

#include "SFGameTile.h"
#include <cmath>

SFGameTile::SFGameTile(int ax,int ay){
    
    x = ax;
    y = ay;
}

SFGameTile:: ~SFGameTile(){
    
    sprite = NULL;
}

bool SFGameTile::nearTile(SFGameTile * othertile){
    
   	return
	(x == othertile->x && abs(y - othertile->y)==1)||
	(y == othertile->y && abs(x - othertile->x)==1);
}


void SFGameTile::trade(SFGameTile * othertile){
    
    CCSprite* tempSprite = sprite;
    
	int tempValue = value;
    
	sprite = othertile->sprite;
	value = othertile->value;
    
	othertile->sprite = tempSprite;
	othertile->value = tempValue;
    
    tempSprite = NULL;
}

CCPoint SFGameTile::pixPosition(){
    
    	return ccp(kStartX + x * kTileSize +kTileSize/2.0f,kStartY + y * kTileSize +kTileSize/2.0f);
}
