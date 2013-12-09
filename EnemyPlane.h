#ifndef __CC_ENEMY_PLANE_H__
#define __CC_ENEMY_PLANE_H__

#include "cocos2d.h"
USING_NS_CC;

class EnemyPlane :
	public cocos2d::CCLayer
{
private:
	static EnemyPlane *m_pSharedEnemyPlane;
protected:
	CCArray *m_pArrayOfPlane;
public:

	static EnemyPlane *getSharedEnemyPlane();
	bool init();
	void isOver(int index);

	void shoot(float dt);
	void addEnemyPlane(float dt);

	CREATE_FUNC(EnemyPlane);
};

#endif