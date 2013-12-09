#ifndef __CC_ENEMY_BULLET_H__
#define __CC_ENEMY_BULLET_H__

#include "cocos2d.h"
USING_NS_CC;

class EnemyBullet :
	public cocos2d::CCLayer
{
private:
	static EnemyBullet *m_pSharedEnemyBullet;
protected:
	CCArray *m_pArrayOfBullet;
public:

	static EnemyBullet *getSharedEnemyBullet();
	bool init();
	void isOver(int index);

	void addNewBullet(CCPoint from);

	void move(float dt);

	CREATE_FUNC(EnemyBullet);
};

#endif