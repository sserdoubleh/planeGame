#ifndef __CC_MY_PLANE_H__
#define __CC_MY_PLANE_H__

#include "cocos2d.h"
USING_NS_CC;

class MyPlane :
	public cocos2d::CCLayer,
	public cocos2d::CCTouchDelegate
{
private:
	static const int DEFAULT_HP = 200;
	static const int SHIP_MAX_NUMBER = 3;
protected:
	int hp;
	int m_frame;
	CCSprite *m_pPlane;
	static MyPlane *m_pMyPlane;

public:

	static MyPlane *getSharedMyPlane();

	bool init();

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
