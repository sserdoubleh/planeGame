#ifndef __CC_MY_PLANE_H__
#define __CC_MY_PLANE_H__

#include "cocos2d.h"
#include "CCPlane.h"
USING_NS_CC;

class MyPlane :
	public cocos2d::CCLayer
{
private:
	static const int DEFAULT_HP = 20;
	static const int SHIP_MAX_NUMBER = 3;

protected:
	int m_frame;
	bool m_bIsGameOver;
	CCPlane *m_pPlane;
	static MyPlane *m_pMyPlane;

public:

	static MyPlane *newMyPlane();
	static MyPlane *getSharedMyPlane();

	bool init();
	void isOver();
	bool hitByEnemy(CCSprite *enemy, int power);

	//touch
	virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);

	//touch
	virtual void onEnter();
	virtual void onExit();

	void changePicture(float dt);
	void shoot(float dt);

    CREATE_FUNC(MyPlane);
};

#endif