#ifndef __CC_PLANE_GAME_SCENE_H__
#define __CC_PLANE_GAME_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class PlaneGameScene :
	public cocos2d::CCScene
{
public:
	
	bool init();

	void judgeCrash(float dt);

	CREATE_FUNC(PlaneGameScene);
};

#endif