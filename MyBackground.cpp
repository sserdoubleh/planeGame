#include "MyBackground.h"
#include "cocos2d.h"

USING_NS_CC;

bool MyBackground::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
		CCSpriteFrame *pFrame = cache->spriteFrameByName("bg01.png");
		m_pBackground1 = CCSprite::createWithSpriteFrame(pFrame);
		m_pBackground2 = CCSprite::createWithSpriteFrame(pFrame);

		CCDirector *pDirector = CCDirector::sharedDirector();
		CCPoint origin = pDirector->getVisibleOrigin();
		
		m_pBackground1->setAnchorPoint(ccp(0,0));
		m_pBackground2->setAnchorPoint(ccp(0,0));
		m_pBackground1->setPosition(ccp(0,0));
		m_pBackground2->setPosition(ccp(0, m_pBackground2->getContentSize().height));

		this->addChild(m_pBackground1);
		this->addChild(m_pBackground2);
		bRet = true;
		this->schedule(schedule_selector(MyBackground::move), 0.1f);
	} while (0);

	return bRet;
}

void MyBackground::move(float dt)
{
	if (m_pBackground2->getPositionY() <= 0)
		m_pBackground1->setPosition(ccp(0,0));
	m_pBackground1->setPositionY(m_pBackground1->getPositionY() - 5);
	m_pBackground2->setPositionY(m_pBackground1->getPositionY() + m_pBackground1->getContentSize().height - 1);
}