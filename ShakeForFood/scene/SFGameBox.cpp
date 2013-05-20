//
//  SFGameBox.cpp
//  ShakeForFood
//
//  Created by Yang David on 5/20/13.
//
//

#include "SFGameBox.h"

SFGameBox::SFGameBox(CCSize inSize,int afactor){
    
    size = inSize;
    
    outBorderTile = new SFGameTile(-1,-1);
    content = CCArray::arrayWithCapacity(size.height);
	content->retain();
    
	for (int y=0; y < size.height; y++) {
		
        CCArray* rowContent = CCArray::arrayWithCapacity(size.width);
        
		for (int x=0; x < size.width; x++) {
            
			SFGameTile *tile = new SFGameTile(x,y);
            
            rowContent->addObject(tile);
            
		}
        
        content->addObject(rowContent);
        
	}
    
    readyToRemoveTiles = CCArray::arrayWithCapacity(size.height);
    readyToRemoveTiles->retain();
}

SFGameTile * SFGameBox::objectAtXAndY(int posX,int posY){
    
    if (posX < 0 || posX >= kBoxWidth || posY < 0 || posY >= kBoxHeight){
		return outBorderTile;
    }
    return (SFGameTile* )((CCArray*)content->objectAtIndex(posY))->objectAtIndex(posX);
}

void SFGameBox::checkWith(Orientation orient){
    
    int iMax = (orient == OrientationHori) ? size.width : size.height;
	int jMax = (orient == OrientationVert) ? size.height : size.width;
    
	for (int i=0; i<iMax; i++) {
		int count = 0;
		int value = -1;
        first = NULL;
        second = NULL;
		for (int j=0; j<jMax; j++)
        {
            SFGameTile* tile = this->objectAtXAndY((orient == OrientationHori) ?i :j,(orient == OrientationHori) ?j :i);
			if(tile->value == value)
            {
				count++;
				if (count > 3)
                {
                    readyToRemoveTiles->addObject(tile);
				}
                else if (count == 3)
                {
                    readyToRemoveTiles->addObject(first);
                    readyToRemoveTiles->addObject(second);
                    readyToRemoveTiles->addObject(tile);
                    first = NULL;
                    second = NULL;
                }
                else if (count == 2) {
                    second = tile;
                }
                else {
                    
                }
				
			}
            else
            {
				count = 1;
				first = tile;
                second = NULL;
				value = tile->value;
			}
		}
	}
}

bool SFGameBox::check(){
    checkWith(OrientationHori);
    checkWith(OrientationVert);
    checkWith(OrientationHori);
    checkWith(OrientationVert);
    
	if (readyToRemoveTiles->count() == 0)
		return false;
	int count = readyToRemoveTiles->count();
	for (int i=0; i < count; i++)
    {
        SFGameTile* tile = (SFGameTile*)readyToRemoveTiles->objectAtIndex(i);
        tile->value = 0;
		if (tile->sprite)
        {
            tile->sprite->runAction(CCSequence::actions(CCScaleTo::actionWithDuration(0.3f, 0.0f),
                                                       CCCallFuncN::actionWithTarget(this, callfuncN_selector(SFGameBox::removeSprite)),
                                                       NULL));
		}
	}
    
    readyToRemoveTiles->removeAllObjects();
    int maxCount = this->repair();
    
    layer->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(kMoveTileTime * maxCount + 0.03f),
                                        CCCallFunc::actionWithTarget(this, callfunc_selector(SFGameBox::afterAllMoveDone)),
                                        NULL));
	return true;
}

void SFGameBox::setLock(bool ff){
    lock = ff;
}

bool SFGameBox::isLocked(){
    return lock;
}

void SFGameBox::removeSprite(SFGameTile * sender){
    
    layer->removeChild(sender, true);
    
}

void SFGameBox::afterAllMoveDone(){
   
    if(check())
        return;
    if(haveMore())
        setLock(false);
    else
    {
        for (int y=0; y< kBoxHeight; y++) {
            for (int x=0; x< kBoxWidth; x++) {
                SFGameTile* tile = objectAtXAndY(x, y);
                tile->value = 0;
            }
        }
        check();
    }
}

int SFGameBox::repair(){
    int maxCount =0;
    for (int x =0; x<size.width; x++) {
        
        int count = repairSingleColumn(x);
        if (count>maxCount) {
            maxCount = count;
        }
    }
    return maxCount;
}

int SFGameBox::repairSingleColumn(int columnIndex)
{
	int extension = 0;
	for (int y=0; y<size.height; y++)
    {
        SFGameTile* tile = objectAtXAndY(columnIndex, y);
        if(tile->value == 0)
            extension++;
        else if (extension == 0)
        {}
        else
        {
            SFGameTile* destTile = objectAtXAndY(columnIndex, y - extension);
            tile->sprite->runAction(CCMoveBy::actionWithDuration(kMoveTileTime * extension, ccp(0,-kTileSize*extension)));
            destTile->value = tile->value;
            destTile->sprite = tile->sprite;
        }
	}
	for (int i=0; i<extension; i++)
    {
		int value = (arc4random()%kKindCount+1);
        SFGameTile* destTile = objectAtXAndY(columnIndex, kBoxHeight-extension+i);
        
        char name[255];
        snprintf(name, 255, "q%d.png",value);
        //CCString* name = CCString::createWithFormat("q%d.png",value);
		CCSprite *sprite = CCSprite::spriteWithFile(name);
		
        sprite->setPosition(ccp(kStartX + columnIndex * kTileSize + kTileSize/2, kStartY + (kBoxHeight + i) * kTileSize + kTileSize/2));
        layer->addChild(sprite);
        sprite->runAction(CCMoveBy::actionWithDuration(kMoveTileTime*extension, ccp(0,-kTileSize*extension)));
		destTile->value = value;
		destTile->sprite = sprite;
	}
	return extension;
}

bool SFGameBox::haveMore()
{
	for (int y=0; y<size.height; y++)
    {
		for (int x=0; x<size.width; x++)
        {
            SFGameTile* aTile = objectAtXAndY(x, y);
			//v 1 2
			if (aTile->y-1 >= 0) {
                SFGameTile* bTile = objectAtXAndY(x, y-1);
				if (aTile->value == bTile->value) {
					{
                        SFGameTile* cTile = objectAtXAndY(x, y+2);
						if (cTile->value == aTile->value)
							return true;
					}
					{
                        SFGameTile* cTile = objectAtXAndY(x-1, y+1);
						if (cTile->value == aTile->value)
							return true;
					}
					{
                        SFGameTile* cTile = objectAtXAndY(x+1, y+1);
						if (cTile->value == aTile->value)
							return true;
					}
					{
                        SFGameTile* cTile = objectAtXAndY(x,y-3);
						if (cTile->value == aTile->value)
							return true;
					}
					{
                        SFGameTile* cTile = objectAtXAndY(x-1, y-2);
						if (cTile->value == aTile->value)
							return true;
					}
					{
                        SFGameTile* cTile = objectAtXAndY(x+1, y-2);
						if (cTile->value == aTile->value)
							return true;
					}
                }
			}
			//v 1 3
			if (aTile->y-2 >= 0) {
				SFGameTile *bTile = objectAtXAndY(x, y-2);
				if (aTile->value == bTile->value)
                {
					{
                        SFGameTile* cTile = objectAtXAndY(x, y+1);
						if (cTile->value == aTile->value)
							return true;
					}
					{
                        SFGameTile* cTile = objectAtXAndY(x,y-3);
						if (cTile->value == aTile->value)
							return true;
					}
					{
                        SFGameTile* cTile = objectAtXAndY(x-1, y-1);
						if (cTile->value == aTile->value)
							return true;
					}
					{
                        SFGameTile* cTile = objectAtXAndY(x+1, y-1);
						if (cTile->value == aTile->value)
							return true;
					}
				}
			}
			// h 1 2
			if (aTile->x+1 < kBoxWidth) {
                SFGameTile* bTile = objectAtXAndY(x+1, y);
				if (aTile->value == bTile->value) {
					{
                        SFGameTile* cTile = objectAtXAndY(x-2, y);
						if (cTile->value == aTile->value)
							return true;
					}
					{
                        SFGameTile* cTile = objectAtXAndY(x-1, y-1);
						if (cTile->value == aTile->value)
							return true;
					}
					{
                        SFGameTile* cTile = objectAtXAndY(x-1, y+1);
						if (cTile->value == aTile->value)
							return true;
					}
					{
                        SFGameTile* cTile = objectAtXAndY(x+3, y);
						if (cTile->value == aTile->value)
							return true;
					}
					{
                        SFGameTile* cTile = objectAtXAndY(x+2, y-1);
						if (cTile->value == aTile->value)
							return true;
					}
					{
                        SFGameTile* cTile = objectAtXAndY(x+2, y+1);
						if (cTile->value == aTile->value)
							return true;
					}
				}
			}
			//h 1 3
			if (aTile->x+2 >= kBoxWidth) {
                SFGameTile* bTile = objectAtXAndY(x+2, y);
				if (aTile->value == bTile->value)
                {
					{
                        SFGameTile* cTile = objectAtXAndY(x+3, y);
						if (cTile->value == aTile->value)
							return true;
					}
					{
                        SFGameTile* cTile = objectAtXAndY(x-1, y);
						if (cTile->value == aTile->value)
							return true;
					}
					{
                        SFGameTile* cTile = objectAtXAndY(x+1, y-1);
						if (cTile->value == aTile->value)
							return true;
					}
					{
                        SFGameTile* cTile = objectAtXAndY(x+1, y+1);
						if (cTile->value == aTile->value)
							return true;
					}
				}
			}
		}
	}
	return false;
}


