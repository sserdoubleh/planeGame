#ifndef __CC_ENEMY_PLANE_H__
#define __CC_ENEMY_PLANE_H__

#include "cocos2d.h"
USING_NS_CC;

class EnemyPlane :
	public cocos2d::CCLayer
{
private:
	static const int DEFAULT_HP = 50;
	static const int DEFAULT_POWER = 20;
	static const float DEFAULT_SHIFT_DISTANCE;
	static const float DEFAULT_SPEED;
	static const float DEFAULT_SPACE;
	static EnemyPlane *m_pSharedEnemyPlane;

protected:
	//	The array of the enemy planes (CCPlane)
	CCArray *m_pArrayOfPlane;
public:

	static EnemyPlane *newEnemyPlane();
	static EnemyPlane *getSharedEnemyPlane();
	bool init();
	void isOver(int index);
	bool hitByBullet(CCSprite *bullet, int power);
	void repeatAction(CCNode *node);

	void shoot(float dt);
	void addEnemyPlane(float dt);
	void hit(float dt);
	void judgeOutOfRange(float dt);

	CREATE_FUNC(EnemyPlane);
};

#endif