#ifndef __CC_PLANE_GAME_SCENE_H__
#define __CC_PLANE_GAME_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "EnemyPlane.h"
#include "EnemyBullet.h"
#include "MyPlane.h"
#include "MyBullet.h"
USING_NS_CC;
using namespace CocosDenshion;

#define BACKGROUND_MUSIC "Music/bgMusic.mp3"
#define FIRE_EFFECT_MUSIC "Music/fireEffect.mp3"
#define EXPLODE_EFFECT_MUSIC "Music/explodeEffect.mp3"
#define SHIP_DESTROY_EFFECT_MUSIC "Music/shipDestroyEffect.mp3"

class PlaneGameScene :
	public cocos2d::CCScene
{
private:
	static const int kTagScore = 999;
protected:
	int m_nScore;
	CCLabelBMFont *m_pScore;

	MyPlane *m_pMyPlane;
	MyBullet *m_pMyBullet;
	EnemyPlane *m_pEnemyPlane;
	EnemyBullet *m_pEnemyBullet;

public:
	bool init();

	void addScore(int score);

	void isGameOver();

	CREATE_FUNC(PlaneGameScene);
};

#endif