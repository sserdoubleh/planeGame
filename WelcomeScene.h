#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class WelcomeScene :
	public cocos2d::CCScene
{
private:
	static const char m_sMenuItem[];
	static SEL_MenuHandler callbackFuncions[]; 

public:
	bool init();
	
	void newGameMenu(CCObject *sender);
	void optionMenu(CCObject *sender);
	void aboutMenu(CCObject *sender);
	void playAgainMenu(CCObject *sender);

	CREATE_FUNC(WelcomeScene);
};

#endif