#include "EnemyBullet.h"
#include "MyPlane.h"
#include "CCBullet.h"
#include "cocos2d.h"

USING_NS_CC;

EnemyBullet *EnemyBullet::m_pSharedEnemyBullet = NULL;
const float EnemyBullet::DEFAULT_SPEED = 3.0f;

EnemyBullet *EnemyBullet::newEnemyBullet()
{
	m_pSharedEnemyBullet = EnemyBullet::create();
	return m_pSharedEnemyBullet;
}

EnemyBullet *EnemyBullet::getSharedEnemyBullet()
{
	if (m_pSharedEnemyBullet == NULL)
		m_pSharedEnemyBullet = EnemyBullet::create();
	return m_pSharedEnemyBullet;
}

bool EnemyBullet::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		m_pArrayOfBullet = CCArray::create();
		m_pArrayOfBullet->retain();

		this->schedule(schedule_selector(EnemyBullet::move));
		this->schedule(schedule_selector(EnemyBullet::hit));
		bRet = true;
	} while (0);
	return bRet;
}

void EnemyBullet::isOver(CCBullet *pDelBullet)
{
	m_pArrayOfBullet->removeObject(pDelBullet);
	pDelBullet->isOver();
}

void EnemyBullet::addNewBullet(CCPoint from)
{
	CCBullet *pNewBullet = CCBullet::createWithPowerAndId(DEFAULT_POWER, 2);

	//	Add to task team.
	m_pArrayOfBullet->addObject(pNewBullet);

	//	Add to layer.
	pNewBullet->setPosition(from);
	this->addChild(pNewBullet);
}

void EnemyBullet::move(float dt)
{
	CCDirector *pDirector = CCDirector::sharedDirector();
	for (int i = 0; i < m_pArrayOfBullet->count(); )
	{
		CCBullet *pCurBullet = (CCBullet*)m_pArrayOfBullet->objectAtIndex(i);
		pCurBullet->setPositionY(pCurBullet->getPositionY() - DEFAULT_SPEED);

		if (pCurBullet->getPositionY() + pCurBullet->getContentSize().height / 2 < 0)
			isOver(pCurBullet);
		else
			i++;
	}
}

void EnemyBullet::hit(float dt)
{
	MyPlane *pMyPlane = MyPlane::getSharedMyPlane();
	for (int i = 0; i < m_pArrayOfBullet->count(); )
	{
		CCBullet *pCurBullet = (CCBullet*) m_pArrayOfBullet->objectAtIndex(i);
		if (pMyPlane->hitByEnemy(pCurBullet, DEFAULT_POWER))
			isOver(pCurBullet);
		else
			i++;
	}
}