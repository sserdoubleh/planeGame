#include "MyPlane.h"
#include "MyBullet.h"
USING_NS_CC;

MyPlane *MyPlane::m_pMyPlane = NULL;

MyPlane *MyPlane::getSharedMyPlane()
{
	if (m_pMyPlane == NULL)
		m_pMyPlane = MyPlane::create();
	return m_pMyPlane;
}

bool MyPlane::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		//	Create a plane (CCSprite)
		//	Current frame.
		m_frame = 0;
		m_bIsGameOver = false;

		m_pPlane = CCPlane::createWithHPAndId(DEFAULT_HP, 0);

		CCSprite *pMyPlane = (CCSprite*)m_pPlane;
		pMyPlane->initWithSpriteFrameName("ship03.png");
		hp = DEFAULT_HP;

		CCDirector *pDirector = CCDirector::sharedDirector();
		pMyPlane->setPosition(ccp(pDirector->getVisibleSize().width / 2, 100));
		this->addChild(pMyPlane);

		this->schedule(schedule_selector(MyPlane::changePicture), 0.5f);
		this->schedule(schedule_selector(MyPlane::shoot), 0.1f);
		bRet = true;
	} while (0);

	return bRet;
}

bool MyPlane::hitByEnemy(CCSprite *enemy, int power)
{
	if (m_bIsGameOver)
		return false;

	CCPoint point = enemy->getPosition();
	CCSprite *pMyPlane = (CCSprite*)m_pPlane;
	CCPoint positionOfPlane = pMyPlane->getPosition();
	CCSize sizeOfPlane = pMyPlane->getContentSize();
	if (positionOfPlane.x - sizeOfPlane.width / 2 <= point.x
		&& point.x <= positionOfPlane.x + sizeOfPlane.width / 2
		&& positionOfPlane.y - sizeOfPlane.height / 2 <= point.y
		&& point.y <= positionOfPlane.y + sizeOfPlane.height)
	{
		if (m_pPlane->lostHP(power))
			isOver();
		return true;
	}

	return false;
}

void MyPlane::isOver()
{
	CCSprite *pMyPlane = (CCSprite*)m_pPlane;
	m_bIsGameOver = true;
	m_pPlane->isOver();
}

void MyPlane::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	CCLayer::onEnter();
}

void MyPlane::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

bool MyPlane::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if (m_bIsGameOver)
		return false;

	//	touch point
	CCPoint point = touch->getLocation();

	//	the position of my plane

	CCSprite *pMyPlane = (CCSprite*)m_pPlane;
	CCPoint pointOfSprite = pMyPlane->getPosition();
	CCSize size = pMyPlane->getContentSize();
	return abs(point.x - pointOfSprite.x) <= size.width / 2
		&& abs(point.y - pointOfSprite.y) <= size.height / 2;
}

void MyPlane::ccTouchMoved(CCTouch* touch, CCEvent* event){

	if (m_bIsGameOver)
		return;

	CCPoint point = touch->getLocation();
	CCSprite *pMyPlane = (CCSprite*)m_pPlane;
	pMyPlane->stopAllActions();
	pMyPlane->setPosition(point);
}

void MyPlane::shoot(float dt)
{
	if (m_bIsGameOver)
		return;

	MyBullet *pMyBullet = MyBullet::getSharedMyBullet();

	CCSprite *pMyPlane = (CCSprite*)m_pPlane;
	pMyBullet->addNewBullet(pMyPlane->getPosition());
}

void MyPlane::changePicture(float dt)
{
	if (m_bIsGameOver)
		return;

	CCSprite *pMyPlane = (CCSprite*)m_pPlane;
	float beforeChangeHeight =  pMyPlane->getContentSize().height;

	//	Change frame
	m_frame = (m_frame + 1) % SHIP_MAX_NUMBER;
	char str[20] = {0};
	sprintf(str, "ship%02d.png", m_frame + 1);
	pMyPlane->initWithSpriteFrameName(str);

	float afterChangeHeight = pMyPlane->getContentSize().height;

	//	Fix the position to set the position as before.
	pMyPlane->setPosition(ccp(pMyPlane->getPositionX(), pMyPlane->getPositionY() + (afterChangeHeight - beforeChangeHeight) / 2));
}