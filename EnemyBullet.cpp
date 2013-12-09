#include "EnemyBullet.h"
#include "cocos2d.h"

USING_NS_CC;

EnemyBullet *EnemyBullet::m_pSharedEnemyBullet = NULL;

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

		this->schedule(schedule_selector(EnemyBullet::move), 0.1f);
		bRet = true;
	} while (0);
	return bRet;
}

void EnemyBullet::isOver(int index)
{
	CCSprite *pDelBullet = (CCSprite*)m_pArrayOfBullet->objectAtIndex(index);
	m_pArrayOfBullet->removeObjectAtIndex(index);
	pDelBullet->removeFromParent();
}

void EnemyBullet::addNewBullet(CCPoint from)
{
	CCLOG("ADD a enemy bullet!");
	CCSprite *pNewBullet = CCSprite::createWithSpriteFrameName("W2.png");
	m_pArrayOfBullet->addObject(pNewBullet);

	pNewBullet->setPosition(from);
	this->addChild(pNewBullet);
}

void EnemyBullet::move(float dt)
{
	CCDirector *pDirector = CCDirector::sharedDirector();
	for (int i = 0; i < m_pArrayOfBullet->count(); )
	{
		CCSprite *pCurBullet = (CCSprite*)m_pArrayOfBullet->objectAtIndex(i);
		pCurBullet->setPositionY(pCurBullet->getPositionY() - 5);

		if (pCurBullet->getPositionY() + pCurBullet->getContentSize().height / 2 < 0)
			isOver(i);
		else
			i++;
	}
}