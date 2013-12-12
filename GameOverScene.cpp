#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "PlaneGameScene.h"

USING_NS_CC;
using namespace CocosDenshion;

GameOverScene *GameOverScene::scene(int score)
{
	GameOverScene *pScene = GameOverScene::create();

	char sMenuItem[] = "menu.png";

	CCSprite* spriteNormal = CCSprite::create(sMenuItem, CCRectMake(126 * 3, 33 * 0, 126, 33));
	CCSprite* spriteSelected = CCSprite::create(sMenuItem, CCRectMake(126 * 3, 33 * 1, 126, 33));
	CCSprite* spriteDisabled = CCSprite::create(sMenuItem, CCRectMake(126 * 3, 33 * 2, 126, 33));
	CCMenuItemSprite *item = CCMenuItemSprite::create(
		spriteNormal, spriteSelected, spriteDisabled,
		pScene, menu_selector(GameOverScene::newGameMenu)
	);

	CCMenu *pMenu = CCMenu::create(item, NULL);

	pScene->addChild(pMenu, 1);

	CCSize sizeOfVisible = CCDirector::sharedDirector()->getVisibleSize();


	CCSprite *backGround = CCSprite::create("loading.png");
	backGround->setPosition(ccp(sizeOfVisible.width / 2, sizeOfVisible.height / 2));

	pScene->addChild(backGround, 0);

	CCSprite *logo = CCSprite::create("logo.png");
	logo->setPosition(ccp(sizeOfVisible.width / 2, sizeOfVisible.height - logo->getContentSize().height / 2));

	pScene->addChild(logo, 1);

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MAIN_MUSIC);

	return pScene;
}

void GameOverScene::newGameMenu(CCObject *sender)
{
	//	turn to play game scene
	CCAction *pAction = CCSequence::create(
		CCDelayTime::create(3.0f),
		CCCallFunc::create(this, callfunc_selector(GameOverScene::turnToPlayGame)),
		NULL);


	//	button effect
	SimpleAudioEngine::sharedEngine()->playEffect(BUTTON_EFFECT);

	this->runAction(pAction);
}

void GameOverScene::turnToPlayGame()
{
	CCLOG("do");
	PlaneGameScene *newGame = PlaneGameScene::create();
	CCLOG("ok build");
	CCDirector::sharedDirector()->replaceScene(newGame);
	CCLOG("ok ");
}