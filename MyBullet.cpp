#include "MyBullet.h"
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
		m_pArrayOfBullet = CCArray::create();
		m_pArrayOfBullet->retain();

		this->schedule(schedule_selector(MyBullet::move), 0.1f);
		bRet = true;
	} while (0);
	return bRet;
}

void MyBullet::addNewBullet(CCPoint from)
{
	//CCLOG("Add one Bullet");

	CCSprite *pNewBullet = CCSprite::createWithSpriteFrameName("W1.png");
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
		pCurBullet->setPositionY(pCurBullet->getPositionY() + 40);

		if (pCurBullet->getPositionY() - pCurBullet->getContentSize().height / 2 > pDirector->getWinSize().height)
		{
			m_pArrayOfBullet->removeObjectAtIndex(i);
			this->removeChild(pCurBullet);
		}
		else
		{
			i++;
		}
	}
}