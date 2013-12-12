#include "cocos2d.h"
#include "CCBullet.h"
#include "SimpleAudioEngine.h"
#include "PlaneGameScene.h"

USING_NS_CC;
using namespace CocosDenshion;

CCBullet *CCBullet::createWithPowerAndId(int power, int id)
{
	CCBullet *newBullet = CCBullet::create();
	if (newBullet)
	{
		newBullet->power = power;
		newBullet->id = id;
		
		//	Set picture
		char str[30] = {0};
		sprintf(str, "W%d.png", id);
		newBullet->initWithSpriteFrameName(str);

		//	Set blend
		ccBlendFunc blend = {GL_SRC_ALPHA, GL_ONE};
		newBullet->setBlendFunc(blend);
	}
	return newBullet;
}

bool CCBullet::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCSprite::init());
		bRet = true;
	} while (0);
	return bRet;
}

void CCBullet::isOver()
{
	this->initWithSpriteFrameName("hit.png");

	//	Set blend
	ccBlendFunc blend = {GL_SRC_ALPHA, GL_ONE};
	this->setBlendFunc(blend);
	
	CCAction *action = CCSequence::create(
		CCDelayTime::create(0.1f),
		CCCallFunc::create(this, callfunc_selector(CCBullet::removeItselfFromeParent)),
		NULL);

	this->stopAllActions();
	this->runAction(action);

	SimpleAudioEngine::sharedEngine()->playEffect(EXPLODE_EFFECT_MUSIC);
}

void CCBullet::removeItselfFromeParent()
{
	this->removeFromParent();
}