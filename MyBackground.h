#ifndef __CC_MY_BACKGROUND_H__
#define __CC_MY_BACKGROUND_H__

#include "cocos2d.h"
USING_NS_CC;

class MyBackground :
	public cocos2d::CCLayer
{
private:
	static const float DEFAULT_MOVE_SPEED;

protected:
	CCSprite *m_pBackground1;
	CCSprite *m_pBackground2;

	CCArray *m_pArrayBackground;

	int m_nCurFrame;

public:

	bool init();

	void move(float dt);

	CREATE_FUNC(MyBackground);
};

#endif