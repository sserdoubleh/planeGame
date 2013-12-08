#include "HelloWorldScene.h"
#include "MyPlane.h"

#define PL 0

USING_NS_CC;

CCScene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(HelloWorld::menuCloseCallback));

	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
		origin.y + pCloseItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	srand(time(NULL));

	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("textureTransparentPack.plist", "textureTransparentPack.png");
	cache->addSpriteFramesWithFile("textureOpaquePack.plist", "textureOpaquePack.png");
	cache->addSpriteFramesWithFile("explosion.plist", "explosion.png");

	i_enemy = CCArray::createWithCapacity(7);
	i_enemy->retain();
	i_player = CCArray::createWithCapacity(4);
	i_player->retain();
	i_bullet = CCArray::createWithCapacity(3);
	i_bullet->retain();
	i_explosion = CCArray::createWithCapacity(36);
	i_explosion->retain();

	char str[100] = {0};
	for (int i = 0; i <= 5; i++)
	{
		sprintf(str, "E%d.png", i);
		CCSpriteFrame *frame = cache->spriteFrameByName(str);
		i_enemy->addObject(frame);
	}
	for (int i = 1; i <= 3; i++)
	{
		sprintf(str, "ship%02d.png", i);
		CCSpriteFrame *frame = cache->spriteFrameByName(str);
		i_player->addObject(frame);
	}
	for (int i = 1; i <= 2; i++)
	{
		sprintf(str, "W%d.png", i);
		CCSpriteFrame *frame = cache->spriteFrameByName(str);
		i_bullet->addObject(frame);
	}
	sprintf(str, "hit.png");
	CCSpriteFrame *frame = cache->spriteFrameByName(str);
	i_bullet->addObject(frame);
	for (int i = 1; i <= 35; i++)
	{
		sprintf(str, "explosion_%02d.png", i);
		CCSpriteFrame *frame = cache->spriteFrameByName(str);
		i_explosion->addObject(frame);
	}

	m_backGround = CCSprite::createWithSpriteFrameName("bg01.png");
	m_backGround->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width / 2,
		CCDirector::sharedDirector()->getWinSize().height / 2) );
	m_backGround->setRotation(90.0);
	this->addChild(m_backGround);

	m_pPlane = MyPlane::createWithSpriteFrameNameAndType("ship01.png", PLAYER);
	m_pPlane->setPosition( ccp(100,100) );
	this->addChild(m_pPlane);

	m_enemyPlane = CCArray::create();
	m_enemyPlane->retain();
	m_enemyBullet = CCArray::create();
	m_enemyBullet->retain();
	m_playerBullet = CCArray::create();
	m_playerBullet->retain();

	m_isOver = false;

	this->schedule(schedule_selector(HelloWorld::crash));
	this->schedule(schedule_selector(HelloWorld::myShoot), 0.1f);
	this->schedule(schedule_selector(HelloWorld::shoot), 2.0f);
	this->schedule(schedule_selector(HelloWorld::addPlane), 1.0f);

	return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::myShoot(float dt)
{
	if (m_isOver)
		return;
	MyPlane *newBullet = MyPlane::createWithSpriteFrameAndType((CCSpriteFrame*)i_bullet->objectAtIndex(0), PLAYER_BULLET);
	newBullet->setPosition(m_pPlane->getPosition());
	float x = m_pPlane->getPositionX();
	float y = CCDirector::sharedDirector()->getWinSize().height + newBullet->getContentSize().height;
	float length = CCDirector::sharedDirector()->getWinSize().height - m_pPlane->getPositionY();
	newBullet->runAction(CCMoveTo::create( max(0, length / PLAYER_BULLET_SPEED), ccp(x,y)));
	this->addPlane(newBullet);
}

void HelloWorld::shoot(float dt)
{
	static int cnt = 0;
	CCLog("step %d",cnt++);
	CCSetIterator iter;
	CCObject *obj;
	CCARRAY_FOREACH(m_enemyPlane, obj)
	{
		MyPlane *enemy = (MyPlane *) obj;
		MyPlane *newBullet = MyPlane::createWithSpriteFrameAndType((CCSpriteFrame*)i_bullet->objectAtIndex(1), MONSTER_BULLET);
		newBullet->setPosition( enemy->getPosition() );
		float x = enemy->getPositionX(), y = -newBullet->getContentSize().height;
		float length = enemy->getPositionY();
		CCAction *action = CCMoveTo::create( length / MONSTER_BULLET_SPEED, ccp(x,y));
		newBullet->runAction(action);
		this->addPlane(newBullet);
	}
}

void HelloWorld::addPlane(float dt)
{
	int number = CCRANDOM_0_1() * 6;

	CCSpriteFrame *pFrame = (CCSpriteFrame*)(i_enemy->objectAtIndex(number));
	MyPlane *newPlane = MyPlane::createWithSpriteFrameAndType(pFrame, MONSTER);

	float startX = CCRANDOM_0_1() * (CCDirector::sharedDirector()->getWinSize().width); 
	float x = CCRANDOM_0_1() * (CCDirector::sharedDirector()->getWinSize().width);
	float y = CCRANDOM_0_1() * (CCDirector::sharedDirector()->getWinSize().height);
	newPlane->setPosition( ccp(startX, CCDirector::sharedDirector()->getWinSize().height) );

	CCActionInterval *a = CCMoveTo::create(100.0f / MONSTER_SPEED, ccp(x - 100, y));
	CCActionInterval *a1 = CCMoveTo::create(200.0f / MONSTER_SPEED, ccp(x + 100, y));
	CCActionInterval *a2 = CCMoveTo::create(200.0f / MONSTER_SPEED, ccp(x - 100, y));
	CCAction *repeat = CCRepeatForever::create(CCSequence::create(a1, a2, NULL));
	CCAction *action = CCSequence::create( CCMoveTo::create( 2.0f, ccp(x, y) ), a, repeat, NULL);
	newPlane->runAction ( repeat );
	this->addPlane(newPlane);
}

void HelloWorld::crash(float dt)
{
	CCObject *obj, *obj2;
	CCARRAY_FOREACH(m_enemyPlane, obj)
	{
		if (m_isOver)
			break;
		MyPlane *enemy = (MyPlane*)obj;
		if (isCrash(enemy, m_pPlane))
		{
			m_pPlane->beHit(enemy);
			if (m_pPlane->isOver())
				this->removePlane(m_pPlane);
			if (enemy->isOver())
				this->removePlane(enemy);
		}
	}
	CCARRAY_FOREACH(m_enemyBullet, obj)
	{
		if (m_isOver)
			break;
		MyPlane *enemy = (MyPlane*)obj;
		if (isCrash(enemy, m_pPlane))
		{
			m_pPlane->beHit(enemy);
			if (m_pPlane->isOver())
				this->removePlane(m_pPlane);
			if (enemy->isOver())
				this->removePlane(enemy);
		}
	}
KILL:
	CCARRAY_FOREACH(m_playerBullet, obj)
	{
		MyPlane *bullte = (MyPlane*)obj;
		CCARRAY_FOREACH(m_enemyPlane, obj2)
		{
			MyPlane *enemy = (MyPlane*)obj2;
			if (isCrash(bullte, enemy))
			{
				enemy->beHit(bullte);
				if (enemy->isOver())
					this->removePlane(enemy);
				if (bullte->isOver())
					this->removePlane(bullte);
				goto KILL;
			}
		}
	}

	CCARRAY_FOREACH(m_playerBullet, obj)
	{
		MyPlane *bullte = (MyPlane*) obj;
		if (isOut(bullte))
			this->removePlane(bullte);
	}
	CCARRAY_FOREACH(m_enemyBullet, obj)
	{
		MyPlane *bullte = (MyPlane*) obj;
		if (isOut(bullte))
			this->removePlane(bullte);
	}
	CCARRAY_FOREACH(m_enemyPlane, obj)
	{
		MyPlane *plane = (MyPlane*) obj;
		if (isOut(plane))
			this->removePlane(plane);
	}
}

bool HelloWorld::isCrash(MyPlane *plane1, MyPlane *plane2)
{
	CCPoint point1 = plane1->getPosition();
	CCPoint point2 = plane2->getPosition();
	CCSize size1 = plane1->getContentSize();
	CCSize size2 = plane2->getContentSize();

	for (int i = 0; i < 4; i++)
	{
		float x, y;
		if (i&1)
			x = point1.x - size1.width / 2;
		else
			x = point1.x + size1.width / 2;
		if (i&2)
			y = point1.y - size1.height / 2;
		else
			y = point1.y + size1.height / 2;

		if (point2.x - size2.width / 2 <= x
			&& x <= point2.x + size2.width / 2
			&& point2.y - size2.height / 2 <= y
			&& y <= point2.y + size2.height / 2)
			return true;
	}
	return false;
}

bool HelloWorld::isOut(MyPlane *plane)
{
	CCPoint point = plane->getPosition();
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	if (point.x < 0 || point.x > size.width
		|| point.y <  0 || point.y > size.width)
		return true;
	return false;
}

void HelloWorld::addPlane(MyPlane *newPlane)
{
	switch(newPlane->getType())
	{
	case MONSTER:
		m_enemyPlane->addObject((CCObject*)newPlane);
		this->addChild(newPlane);
		break;
	case PLAYER_BULLET:
		m_playerBullet->addObject(newPlane);
		this->addChild(newPlane);
		break;
	case MONSTER_BULLET:
		m_enemyBullet->addObject(newPlane);
		this->addChild(newPlane);
		break;
	}
}

void HelloWorld::removePlane(MyPlane *plane)
{
	int number = CCRANDOM_0_1() * 35;
	CCSpriteFrame *frame;
	int type = plane->getType();
	switch(type)
	{
	case PLAYER:
		m_isOver = true;
		frame = (CCSpriteFrame *)i_explosion->objectAtIndex(number);
		break;
	case MONSTER:
		m_enemyPlane->removeObject(plane);
		frame = (CCSpriteFrame *)i_explosion->objectAtIndex(number);
		break;
	case MONSTER_BULLET:
		m_enemyBullet->removeObject(plane);
		frame = (CCSpriteFrame *)i_bullet->objectAtIndex(2);
		break;
	case PLAYER_BULLET:
		m_playerBullet->removeObject(plane);
		frame = (CCSpriteFrame *)i_bullet->objectAtIndex(2);
		break;
	}
	plane->initWithSpriteFrame(frame);
	plane->stopAllActions();
	CCAction *action = CCSequence::create(CCDelayTime::create(0.2f),
		CCCallFuncND::create(this, callfuncND_selector(HelloWorld::removeIt), (void*)true),
		NULL);
	plane->runAction(action);
}

void HelloWorld::removeIt(CCNode *pSenddr, void *data)
{
	this->removeChild(pSenddr);
	pSenddr->removeFromParentAndCleanup(true);
}