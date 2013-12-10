#include "MyBullet.h"
#include "EnemyPlane.h"
#include "cocos2d.h"

USING_NS_CC;

MyBullet *MyBullet::m_pSharedMyBullet = NULL;

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

		this->schedule(schedule_selector(MyBullet::move), 0.1f);
		this->schedule(schedule_selector(MyBullet::hit), 0.1f);
		bRet = true;
	} while (0);
	return bRet;
}

void MyBullet::isOver(int index)
{
	CCSprite *pDelBullet = (CCSprite*)m_pArrayOfBullet->objectAtIndex(index);
	m_pArrayOfBullet->removeObjectAtIndex(index);
	pDelBullet->removeFromParent();
}

void MyBullet::addNewBullet(CCPoint from)
{
	CCSprite *pNewBullet = CCSprite::createWithSpriteFrameName("W1.png");
	ccBlendFunc blend = {GL_SRC_ALPHA, GL_ONE};
	pNewBullet->setBlendFunc(blend);
	m_pArrayOfBullet->addObject(pNewBullet);

	pNewBullet->setPosition(from);
	this->addChild(pNewBullet);
}


void MyBullet::move(float dt)
{
	CCDirector *pDirector = CCDirector::sharedDirector();
	for (int i = 0; i < m_pArrayOfBullet->count(); )
	{
		CCSprite *pCurBullet = (CCSprite*)m_pArrayOfBullet->objectAtIndex(i);
		pCurBullet->setPositionY(pCurBullet->getPositionY() + pCurBullet->getContentSize().height);

		if (pCurBullet->getPositionY() - pCurBullet->getContentSize().height / 2 > pDirector->getWinSize().height)
			isOver(i);
		else
			i++;
	}
}

void MyBullet::hit(float dt)
{
	EnemyPlane *pEnemyPlane = EnemyPlane::getSharedEnemyPlane();
	for (int i = 0; i < m_pArrayOfBullet->count(); )
	{
		CCSprite *pCurBullet = (CCSprite*) m_pArrayOfBullet->objectAtIndex(i);
		if (pEnemyPlane->hitByBullet(pCurBullet, DEFAULT_POWER))
			isOver(i);
		else
			i++;
	}
}