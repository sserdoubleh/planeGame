#ifndef __CC_MY_BULLET_H__
#define __CC_MY_BULLET_H__

#include "cocos2d.h"
USING_NS_CC;

class MyBullet :
	public cocos2d::CCLayer
{
private:
	static MyBullet *m_pSharedMyBullet;

protected:
	//The array of the bullet(CCSprite)
	CCArray *m_pArrayOfBullet;

public:
	
	static const int DEFAULT_POWER = 10;

	static MyBullet * getSharedMyBullet();
	bool init();
	void isOver(int index);

	void addNewBullet(CCPoint from);

	void move(float dt);
	void hit(float dt);

	CREATE_FUNC(MyBullet);
};

#endif