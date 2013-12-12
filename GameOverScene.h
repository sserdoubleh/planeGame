#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"
#include "WelcomeScene.h"

USING_NS_CC;

class GameOverScene :
	public CCScene
{
public:

	static GameOverScene *scene(int score);

	void newGameMenu(CCObject *sender);
	void turnToPlayGame();

	CREATE_FUNC(GameOverScene);
};

#endif