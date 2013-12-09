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
		//	Create a plane (CCSprite)
		//	Current frame.
		m_frame = 0;
		m_pPlane = CCSprite::createWithSpriteFrameName("ship03.png");
		hp = DEFAULT_HP;

		CCDirector *pDirector = CCDirector::sharedDirector();
		m_pPlane->setPosition(ccp(pDirector->getVisibleSize().width / 2, 100));
		this->addChild(m_pPlane);

		this->schedule(schedule_selector(MyPlane::changePicture), 0.5f);
		this->schedule(schedule_selector(MyPlane::shoot), 0.1f);
		bRet = true;
	} while (0);

	return bRet;
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
	//	touch point
	CCPoint point = touch->getLocation();

	//	the position of my plane
	CCPoint pointOfSprite = m_pPlane->getPosition();
	CCSize size = m_pPlane->getContentSize();
	return abs(point.x - pointOfSprite.x) <= size.width / 2
		&& abs(point.y - pointOfSprite.y) <= size.height / 2;
}

void MyPlane::ccTouchMoved(CCTouch* touch, CCEvent* event){
	CCPoint point = touch->getLocation();
	m_pPlane->stopAllActions();
	m_pPlane->setPosition(point);
}

void MyPlane::shoot(float dt)
{
	MyBullet *pMyBullet = MyBullet::getSharedMyBullet();

	pMyBullet->addNewBullet(m_pPlane->getPosition());
}

void MyPlane::changePicture(float dt)
{
	float beforeChangeHeight =  m_pPlane->getContentSize().height;

	m_frame = (m_frame + 1) % SHIP_MAX_NUMBER;
	char str[20] = {0};
	sprintf(str, "ship%02d.png", m_frame + 1);
	m_pPlane->initWithSpriteFrameName(str);

	float afterChangeHeight = m_pPlane->getContentSize().height;

	m_pPlane->setPosition(ccp(m_pPlane->getPositionX(), m_pPlane->getPositionY() + (afterChangeHeight - beforeChangeHeight) / 2));

	//CCLOG("width:%lf height:%lf",m_pPlane->getContentSize().width, m_pPlane->getContentSize().height);
	//CCLOG("bottom:%lf",m_pPlane->getPositionY() - m_pPlane->getContentSize().height / 2);
}