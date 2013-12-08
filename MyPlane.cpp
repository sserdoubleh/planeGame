#include "MyPlane.h"
USING_NS_CC;

void MyPlane::onEnter(){

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,false);
	CCSprite::onEnter();
}

void MyPlane::onExit(){
    
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCSprite::onExit();
}

bool MyPlane::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if (type != PLAYER)
		return false;

	CCLOG("ccTouchBegan");
	//	touch point
	CCPoint point = touch->getLocation();

	//	this plane
	CCPoint pointOfSprite = this->getPosition();
	CCSize size = this->getContentSize();
	return abs(point.x - pointOfSprite.x) <= size.width / 2
		&& abs(point.y - pointOfSprite.y) <= size.height / 2;
}

void MyPlane::ccTouchMoved(CCTouch* touch, CCEvent* event){
    CCLOG("ccTouchMoved");
	CCPoint point = touch->getLocation();
	this->stopAllActions();
	this->setPosition(point);
}

void MyPlane::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CCLOG("ccTouchEnded");
}

void MyPlane::beHit(MyPlane *other)
{
	int lost = min(this->hp, other->hp);
	this->hp -= lost;
	other->hp -= lost;
}

bool MyPlane::isOver()
{
	return hp <= 0;
}

int MyPlane::getType() const
{
	return type;
}