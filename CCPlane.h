#ifndef __CC_PLANE_H__
#define __CC_PLANE_H__

#include "cocos2d.h"
USING_NS_CC;

class CCPlane :
	cocos2d::CCSprite
{
protected:
	int hp;
	int id;

public:
	
	static CCPlane *createWithHPAndId(int hp, int id);

	bool init();

	bool lostHP(int hp);

	void isOver();

	void removeItselfFromeParent();

	CREATE_FUNC(CCPlane);
};

#endif