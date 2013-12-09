#include "cocos2d.h"
#include "EnemyPlane.h"
#include "EnemyBullet.h"

USING_NS_CC;

EnemyPlane *EnemyPlane::m_pSharedEnemyPlane = NULL;

EnemyPlane *EnemyPlane::getSharedEnemyPlane()
{
	if (m_pSharedEnemyPlane == NULL)
		m_pSharedEnemyPlane = EnemyPlane::create();
	return m_pSharedEnemyPlane;
}

bool EnemyPlane::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		m_pArrayOfPlane = CCArray::create();
		m_pArrayOfPlane->retain();

		this->schedule(schedule_selector(EnemyPlane::addEnemyPlane), 2.0f);
		this->schedule(schedule_selector(EnemyPlane::shoot), 3.0f);

		bRet = true;
	} while (0);
	return bRet;
}

void EnemyPlane::isOver(int index)
{
	CCSprite *pDelPlane = (CCSprite*)m_pArrayOfPlane->objectAtIndex(index);
	m_pArrayOfPlane->removeObjectAtIndex(index);
	pDelPlane->removeFromParent();
}

void EnemyPlane::addEnemyPlane(float dt)
{
	CCLOG("ADD a enemy plane");

	int random_number = CCRANDOM_0_1() * 6;
	char str[20];
	sprintf(str, "E%d.png", random_number);
	CCSprite *pNewEnemyPlane = CCSprite::createWithSpriteFrameName(str);

	m_pArrayOfPlane->addObject(pNewEnemyPlane);

	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint origin = pDirector->getVisibleOrigin();
	CCSize visibleSize = pDirector->getVisibleSize();
	float random_x = CCRANDOM_0_1() * visibleSize.width;
	float random_X = CCRANDOM_0_1() * visibleSize.width;
	float random_Y = CCRANDOM_0_1() * visibleSize.height;

	CCAction *pAction = CCSequence::create(
		CCPlace::create(ccp(random_x, origin.y + visibleSize.height)),
		CCMoveTo::create(1.0f,ccp(random_X, random_Y)),
		NULL);
	pNewEnemyPlane->runAction(pAction);

	this->addChild(pNewEnemyPlane);
}

void EnemyPlane::shoot(float dt)
{
	for (int i = 0; i < m_pArrayOfPlane->count(); i++)
	{
		CCSprite *pCurPlane = (CCSprite*)m_pArrayOfPlane->objectAtIndex(i);
		EnemyBullet::getSharedEnemyBullet()->addNewBullet(pCurPlane->getPosition());
	}
}