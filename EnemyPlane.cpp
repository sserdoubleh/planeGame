#include "cocos2d.h"
#include "CCPlane.h"
#include "EnemyPlane.h"
#include "EnemyBullet.h"
#include "PlaneGameScene.h"
#include "MyPlane.h"

USING_NS_CC;

const float EnemyPlane::DEFAULT_SHIFT_DISTANCE = 50.0f;
const float EnemyPlane::DEFAULT_SPEED = 25.0f;
const float EnemyPlane::DEFAULT_SPACE = 60.0f;

EnemyPlane *EnemyPlane::m_pSharedEnemyPlane = NULL;

EnemyPlane *EnemyPlane::newEnemyPlane()
{
	m_pSharedEnemyPlane = EnemyPlane::create();
	return m_pSharedEnemyPlane;
}

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
		this->schedule(schedule_selector(EnemyPlane::hit));
		this->schedule(schedule_selector(EnemyPlane::judgeOutOfRange));

		bRet = true;
	} while (0);
	return bRet;
}

void EnemyPlane::isOver(int index)
{
	CCSprite *pDelPlane = (CCSprite*)m_pArrayOfPlane->objectAtIndex(index);
	m_pArrayOfPlane->removeObjectAtIndex(index);
	CCPlane *pPlane = (CCPlane*)pDelPlane;
	pPlane->isOver();

	PlaneGameScene *gameScene = (PlaneGameScene*)this->getParent();
	gameScene->addScore(20);
}

bool EnemyPlane::hitByBullet(CCSprite *bullet, int power)
{
	CCPoint point = bullet->getPosition();
	for (int i = 0; i < m_pArrayOfPlane->count(); i++)
	{
		CCSprite *pCurPlane = (CCSprite*)m_pArrayOfPlane->objectAtIndex(i);
		CCPoint positionOfPlane = pCurPlane->getPosition();
		CCSize sizeOfPlane = pCurPlane->getContentSize();
		if (positionOfPlane.x - sizeOfPlane.width / 2 <= point.x
			&& point.x <= positionOfPlane.x + sizeOfPlane.width / 2
			&& positionOfPlane.y - sizeOfPlane.height / 2 <= point.y
			&& point.y <= positionOfPlane.y + sizeOfPlane.height)
		{
			CCPlane *pPlane = (CCPlane *)pCurPlane;
			if (pPlane->lostHP(power))
				isOver(i);
			return true;
		}
	}
	return false;
}

void EnemyPlane::addEnemyPlane(float dt)
{
	int random_number = CCRANDOM_0_1() * 6;
	CCPlane *pNewEnemyPlane = CCPlane::createWithHPAndId(DEFAULT_HP, random_number);
	CCSprite *pNewPlane = (CCSprite *) pNewEnemyPlane;

	char str[20];
	sprintf(str, "E%d.png", random_number);
	pNewPlane->initWithSpriteFrameName(str);

	m_pArrayOfPlane->addObject(pNewPlane);

	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint origin = pDirector->getVisibleOrigin();
	CCSize visibleSize = pDirector->getVisibleSize();
	float random_x = CCRANDOM_0_1() * visibleSize.width;
	float x = CCRANDOM_0_1() * visibleSize.width;
	float y = CCRANDOM_0_1() * (visibleSize.height - DEFAULT_SPACE) + DEFAULT_SPACE;

	CCSequence *action = CCSequence::create(
		CCPlace::create(ccp(random_x, origin.y + visibleSize.height)),
		CCMoveTo::create(1.0f, ccp(x, y)),
		CCCallFuncN::create(this, callfuncN_selector(EnemyPlane::repeatAction)),
		NULL);

	pNewPlane->runAction(action);

	this->addChild(pNewPlane);
}

void EnemyPlane::repeatAction(CCNode *node)
{
	CCPlane *plane = (CCPlane*)node;
	CCActionInterval *a1 = CCMoveBy::create(DEFAULT_SHIFT_DISTANCE / DEFAULT_SPEED,
		ccp(-DEFAULT_SHIFT_DISTANCE, 0));
	CCActionInterval *a2 = CCMoveBy::create(DEFAULT_SHIFT_DISTANCE / DEFAULT_SPEED,
		ccp(DEFAULT_SHIFT_DISTANCE, 0));
	CCRepeatForever *pRepeat = CCRepeatForever::create(
		CCSequence::create(a1, a2, NULL));
	plane->stopAllActions();
	plane->runAction(pRepeat);
}

void EnemyPlane::shoot(float dt)
{
	for (int i = 0; i < m_pArrayOfPlane->count(); i++)
	{
		CCSprite *pCurPlane = (CCSprite*)m_pArrayOfPlane->objectAtIndex(i);
		EnemyBullet::getSharedEnemyBullet()->addNewBullet(pCurPlane->getPosition());
	}
}

void EnemyPlane::hit(float dt)
{
	MyPlane *pMyPlane = MyPlane::getSharedMyPlane();
	for (int i = 0; i < m_pArrayOfPlane->count(); )
	{
		CCSprite *pCurPlane = (CCSprite*)m_pArrayOfPlane->objectAtIndex(i);
		if (pMyPlane->hitByEnemy(pCurPlane, DEFAULT_POWER))
			isOver(i);
		else
			i++;
	}
}

void EnemyPlane::judgeOutOfRange(float dt)
{
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCSize sizeOfVisible = pDirector->getVisibleSize();
	for (int i = 0; i < m_pArrayOfPlane->count(); )
	{
		CCSprite *pCurPlane = (CCSprite*)m_pArrayOfPlane->objectAtIndex(i);
		CCPoint positionOfPlane = pCurPlane->getPosition();
		if (positionOfPlane.x < 0 || positionOfPlane.x > sizeOfVisible.width)
			isOver(i);
		else
			i++;
	}
}