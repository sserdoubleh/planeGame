#include "MyBullet.h"
#include "EnemyPlane.h"
#include "CCBullet.h"
#include "cocos2d.h"

USING_NS_CC;

MyBullet *MyBullet::m_pSharedMyBullet = NULL;

const float MyBullet::DEFAULT_SPEED = 30.0f;

MyBullet *MyBullet::newMyBullet()
{
	m_pSharedMyBullet = MyBullet::create();
	return m_pSharedMyBullet;
}

MyBullet *MyBullet::getSharedMyBullet()
{
	if (m_pSharedMyBullet == NULL)
		m_pSharedMyBullet = MyBullet::create();
	return m_pSharedMyBullet;
}

bool MyBullet::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		m_pArrayOfBullet = CCArray::create();
		m_pArrayOfBullet->retain();

		this->schedule(schedule_selector(MyBullet::move));
		this->schedule(schedule_selector(MyBullet::hit));
		bRet = true;
	} while (0);
	return bRet;
}

void MyBullet::isOver(CCBullet *pDelBullet)
{
	m_pArrayOfBullet->removeObject(pDelBullet);
	pDelBullet->isOver();
}

void MyBullet::addNewBullet(CCPoint from)
{
	CCBullet *pNewBullet = CCBullet::createWithPowerAndId(DEFAULT_POWER, 1);

	//	Add to task team.
	m_pArrayOfBullet->addObject(pNewBullet);

	//	Add to layer.
	pNewBullet->setPosition(from);
	this->addChild(pNewBullet);
}


void MyBullet::move(float dt)
{
	CCDirector *pDirector = CCDirector::sharedDirector();
	for (int i = 0; i < m_pArrayOfBullet->count(); )
	{
		CCBullet *pCurBullet = (CCBullet*)m_pArrayOfBullet->objectAtIndex(i);
		pCurBullet->setPositionY(pCurBullet->getPositionY() + DEFAULT_SPEED);

		if (pCurBullet->getPositionY() - pCurBullet->getContentSize().height / 2 > pDirector->getVisibleSize().height)
			isOver(pCurBullet);
		else
			i++;
	}
}

void MyBullet::hit(float dt)
{
	EnemyPlane *pEnemyPlane = EnemyPlane::getSharedEnemyPlane();
	for (int i = 0; i < m_pArrayOfBullet->count(); )
	{
		CCBullet *pCurBullet = (CCBullet*) m_pArrayOfBullet->objectAtIndex(i);
		if (pEnemyPlane->hitByBullet(pCurBullet, DEFAULT_POWER))
			isOver(pCurBullet);
		else
			i++;
	}
}