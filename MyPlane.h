#ifndef __MY_PLANE__
#define __MY_PLANE__

#include "cocos2d.h"
USING_NS_CC;

#define PLAYER_HP 200
#define MONSTER_HP 20
#define BULLET_POWER 10

#define PLAYER 0
#define MONSTER 1
#define PLAYER_BULLET 2
#define MONSTER_BULLET 3

#define PLAYER_BULLET_SPEED 300.0f
#define MONSTER_BULLET_SPEED 30.0f
#define MONSTER_SPEED 30.0f

class MyPlane : public cocos2d::CCSprite, public cocos2d::CCTouchDelegate
{
public:
	static MyPlane *createWithSpriteFrameNameAndType(const char *pszSpriteFrameName, int type)
	{
		CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
		return createWithSpriteFrameAndType(pFrame, type);
	}

	static MyPlane *createWithSpriteFrameAndType(CCSpriteFrame *pFrame, int type)
	{
		MyPlane *myPlane = createWithType(type);
		if (pFrame && myPlane && myPlane->initWithSpriteFrame(pFrame))
			return myPlane;
		return NULL;
	}

	static MyPlane *createWithType(int type)
	{
		MyPlane *myPlane = new MyPlane();
		if (myPlane)
		{
			myPlane->type = type;
			myPlane->autorelease();
			switch(type)
			{
			case PLAYER:
				myPlane->hp = PLAYER_HP;
				break;
			case MONSTER:
				myPlane->hp = MONSTER_HP;
				break;
			default:
				myPlane->hp = BULLET_POWER;
				break;
			}
		}
		return myPlane;
	}

	//重写触屏回调函数
	virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);

	//重写生命周期函数
	virtual void onEnter();
	virtual void onExit();
	void beHit(MyPlane *other);
	bool isOver();
	int getType() const;

    // implement the "static node()" method manually
    CREATE_FUNC(MyPlane);
private:
	int type;
	int hp;
};

#endif // __HELLOWORLD_SCENE_H__
