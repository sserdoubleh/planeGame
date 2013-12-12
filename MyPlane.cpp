#include "MyPlane.h"
#include "MyBullet.h"
#include "SimpleAudioEngine.h"
#include "PlaneGameScene.h"

USING_NS_CC;
using namespace CocosDenshion;

MyPlane *MyPlane::m_pMyPlane = NULL;

MyPlane *MyPlane::newMyPlane()
{
	m_pMyPlane = MyPlane::create();
	return m_pMyPlane;
}

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

		m_pPlane->initWithSpriteFrameName("ship03.png");

		CCDirector *pDirector = CCDirector::sharedDirector();
		m_pPlane->setPosition(ccp(pDirector->getVisibleSize().width / 2, 100));
		this->addChild(m_pPlane);

		this->schedule(schedule_selector(MyPlane::changePicture), 0.5f);
		this->schedule(schedule_selector(MyPlane::shoot), 0.2f);
		bRet = true;
	} while (0);

	return bRet;
}

bool MyPlane::hitByEnemy(CCSprite *enemy, int power)
{

	if (m_bIsGameOver)
		return false;

	CCPoint point = enemy->getPosition();
	CCPoint positionOfPlane = m_pPlane->getPosition();
	CCSize sizeOfPlane = m_pPlane->getContentSize();

	if (positionOfPlane.x - sizeOfPlane.width / 2 <= point.x
		&& point.x <= positionOfPlane.x + sizeOfPlane.width / 2
		&& positionOfPlane.y - sizeOfPlane.height / 2 <= point.y
		&& point.y <= positionOfPlane.y + sizeOfPlane.height)
	{
		CCLOG("HP: %d", m_pPlane->hp);
		if (m_pPlane->lostHP(power))
			isOver();
		return true;
	}

	return false;
}

void MyPlane::isOver()
{
	m_bIsGameOver = true;
	m_pPlane->isOver();

	PlaneGameScene *pPlaneGameScene = (PlaneGameScene*)this->getParent();

	pPlaneGameScene->isGameOver();
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
	CCPoint pointOfSprite = m_pPlane->getPosition();
	//	the size of my plane
	CCSize size = m_pPlane->getContentSize();

	return abs(point.x - pointOfSprite.x) <= size.width / 2
		&& abs(point.y - pointOfSprite.y) <= size.height / 2;
}

void MyPlane::ccTouchMoved(CCTouch* touch, CCEvent* event){

	if (m_bIsGameOver)
		return;

	CCPoint point = touch->getLocation();

	CCDirector *pDirector = CCDirector::sharedDirector();
	CCSize sizeOfVisible = pDirector->getVisibleSize();

	CCPoint newPoint = CCPoint( max(0.0f,min(point.x, sizeOfVisible.width)), max(0.0f,min(point.y,sizeOfVisible.height)) );

	m_pPlane->stopAllActions();
	m_pPlane->setPosition(newPoint);
}

void MyPlane::shoot(float dt)
{
	if (m_bIsGameOver)
		return;

	MyBullet *pMyBullet = MyBullet::getSharedMyBullet();

	CCPoint positionOfPlane = m_pPlane->getPosition();
	CCSize sizeOfPlane = m_pPlane->getContentSize();

	pMyBullet->addNewBullet(ccp(positionOfPlane.x - sizeOfPlane.width / 4, positionOfPlane.y));
	pMyBullet->addNewBullet(ccp(positionOfPlane.x + sizeOfPlane.width / 4, positionOfPlane.y));

	SimpleAudioEngine::sharedEngine()->playEffect(FIRE_EFFECT_MUSIC);
}

void MyPlane::changePicture(float dt)
{
	if (m_bIsGameOver)
		return;

	float beforeChangeHeight =  m_pPlane->getContentSize().height;

	//	Change frame
	m_frame = (m_frame + 1) % SHIP_MAX_NUMBER;
	char str[20] = {0};
	sprintf(str, "ship%02d.png", m_frame + 1);
	m_pPlane->initWithSpriteFrameName(str);

	m_pPlane->initWithSpriteFrameName(str);

	float afterChangeHeight = m_pPlane->getContentSize().height;

	//	Fix the position to set the position as before.
	m_pPlane->setPosition(ccp(m_pPlane->getPositionX(),
		m_pPlane->getPositionY() + (afterChangeHeight - beforeChangeHeight) / 2));
}