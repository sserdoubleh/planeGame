#include "CCPlane.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "PlaneGameScene.h"

USING_NS_CC;
using namespace CocosDenshion;

CCPlane *CCPlane::createWithHPAndId(int hp, int id)
{
	CCPlane *pNewPlane = CCPlane::create();
	if (pNewPlane)
	{
		pNewPlane->hp = hp;
		pNewPlane->id = id;
	}
	return pNewPlane;
}

bool CCPlane::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCSprite::init());
		bRet = true;
	} while (0);
	return bRet;
}

bool CCPlane::lostHP(int hp)
{
	this->hp -= hp;
	return this->hp <= 0;
}

void CCPlane::isOver()
{
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	char str[100] = {0};
	CCArray *actionFrames = CCArray::createWithCapacity(8);
	actionFrames->retain();

	CCLOG("id: %d",id);
	for (int i = 1; i <= 6 && id * 6 + i <= 35; i++)
	{
		sprintf(str, "explosion_%02d.png", id * 6 + i);
		CCSpriteFrame *frame = cache->spriteFrameByName(str);
		actionFrames->addObject(frame);
	}

	CCAnimation *showAction = CCAnimation::createWithSpriteFrames(actionFrames, 0.05f);

	CCAction *action = CCSequence::create(
		CCAnimate::create(showAction),
		CCCallFunc::create(this, callfunc_selector(CCPlane::removeItselfFromeParent)),
		NULL);
	
	this->stopAllActions();
	this->runAction(action);

	SimpleAudioEngine::sharedEngine()->playEffect(SHIP_DESTROY_EFFECT_MUSIC);
}

void CCPlane::removeItselfFromeParent()
{
	this->removeFromParent();
}