#ifndef __CC_MY_BULLET_H__
#define __CC_MY_BULLET_H__

#include "cocos2d.h"
#include "CCBullet.h"
USING_NS_CC;

class MyBullet :
	public cocos2d::CCLayer
{
private:
	static MyBullet *m_pSharedMyBullet;
	static const int DEFAULT_POWER = 10;
	static const float DEFAULT_SPEED;

protected:
	//	The array of the bullet(MyBullet)
	CCArray *m_pArrayOfBullet;

public:

	static MyBullet * newMyBullet();
	static MyBullet * getSharedMyBullet();
	bool init();
	void isOver(CCBullet *pDelBullet);

	void addNewBullet(CCPoint from);

	void move(float dt);
	void hit(float dt);

	CREATE_FUNC(MyBullet);
};

#endif