#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class MyPlane;

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

private:
	CCArray *i_enemy;
	CCArray *i_player;
	CCArray *i_bullet;
	CCArray *i_explosion;
	CCArray *m_enemyPlane;
	CCArray *m_playerBullet;
	CCArray *m_enemyBullet;
	MyPlane *m_pPlane;
	CCSprite *m_backGround;

	bool m_isOver;

	void myShoot(float);
	void shoot(float dt);
	void addPlane(float dt);
	void crash(float dt);

	bool isCrash(MyPlane *plane1, MyPlane *plane2);
	bool isOut(MyPlane *plane);
	void addPlane(MyPlane *plane);
	void removePlane(MyPlane *plane);
	void removeIt(CCNode *pSenddr, void *data);
};

#endif // __HELLOWORLD_SCENE_H__
