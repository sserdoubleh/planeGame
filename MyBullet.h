#ifndef __CC_MY_BULLET_H__
#define __CC_MY_BULLET_H__

#include "cocos2d.h"
USING_NS_CC;

class MyBullet :
	public cocos2d::CCLayer
{
private:
	static const int DEFAULT_POWER = 10;
protected:
	//The array of the bullet(CCSprite)
	CCArray *m_pArrayOfBullet;
	static MyBullet *m_pSharedMyBullet;

public:
	static MyBullet * getSharedMyBullet();
	bool init();
	void addNewBullet(CCPoint from);

	void move(float dt);

	CREATE_FUNC(MyBullet);
};

#endif