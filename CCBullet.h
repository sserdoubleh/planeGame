#ifndef __CC_BULLET_H__
#define __CC_BULLET_H__

#include "cocos2d.h"

USING_NS_CC;

class CCBullet	:
	public CCSprite
{
protected:
	int id;
	int power;

public:

	static CCBullet *createWithPowerAndId(int power, int id);

	bool init();

	void isOver();

	void removeItselfFromeParent();

	CREATE_FUNC(CCBullet);
};

#endif