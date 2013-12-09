#ifndef __CC_MY_BULLET_H__
#define __CC_MY_BULLET_H__

#include "cocos2d.h"
USING_NS_CC;

class MyBullet :
	public cocos2d::CCLayer
{
public:
	
	static const int DEFAULT_POWER = 10;

	//The array of the bullet(CCSprite)
	CCArray *m_pArrayOfBullet;


};

#endif