#include "MyBackground.h"
#include "cocos2d.h"

USING_NS_CC;

const float MyBackground::DEFAULT_MOVE_SPEED = 0.5f;

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
		CCSize sizeOfVisible = pDirector->getVisibleSize();
		
		m_pBackground1->setAnchorPoint(ccp(0,0));
		m_pBackground2->setAnchorPoint(ccp(0,0));
		m_pBackground1->setPosition(ccp(0,0));
		m_pBackground2->setPosition(ccp(0, m_pBackground2->getContentSize().height));

		m_pArrayBackground = CCArray::createWithCapacity(5);
		m_pArrayBackground->retain();

		m_nCurFrame = 0;
		for (int i = 0; i < 4; i++)
		{
			int x = i & 1? 1: 0, y = i & 2? 1: 0;
			CCSprite *pBackground = CCSprite::create("b01.png", CCRectMake(x * 240, y * 240, 240, 240));
			m_pArrayBackground->addObject(pBackground);
			if (i < 2)
			{
				pBackground->setPosition( ccp(sizeOfVisible.width / 2, sizeOfVisible.height / 2 + i * sizeOfVisible.height) );
				this->addChild(pBackground, 1);
			}
		}

		this->addChild(m_pBackground1);
		this->addChild(m_pBackground2);
		bRet = true;
		this->schedule(schedule_selector(MyBackground::move));
	} while (0);

	return bRet;
}

void MyBackground::move(float dt)
{
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCSize sizeOfVisible = pDirector->getVisibleSize();

	if (m_pBackground2->getPositionY() <= 0)
		m_pBackground1->setPosition(ccp(0,0));
	m_pBackground1->setPositionY(m_pBackground1->getPositionY() - DEFAULT_MOVE_SPEED);
	m_pBackground2->setPositionY(m_pBackground1->getPositionY() + m_pBackground1->getContentSize().height - 1);

	CCSprite *pPreBackground = (CCSprite*)m_pArrayBackground->objectAtIndex(m_nCurFrame);
	CCSprite *pPostBackground = (CCSprite*)m_pArrayBackground->objectAtIndex((m_nCurFrame + 1) % 4);

	pPreBackground->setPositionY(pPreBackground->getPositionY() - DEFAULT_MOVE_SPEED);
	pPostBackground->setPositionY(pPreBackground->getPositionY() + sizeOfVisible.height);

	if (pPreBackground->getPositionY() + sizeOfVisible.height / 2 <= 0)
	{
		m_nCurFrame = (m_nCurFrame + 1) % 4;
		CCSprite *pNexBackGround = (CCSprite*)m_pArrayBackground->objectAtIndex((m_nCurFrame + 1) % 4);
		pNexBackGround->setPosition(ccp(sizeOfVisible.width / 2, pPostBackground->getPositionY() + sizeOfVisible.height));
		this->addChild(pNexBackGround, 1);
		pPreBackground->removeFromParent();
	}
}