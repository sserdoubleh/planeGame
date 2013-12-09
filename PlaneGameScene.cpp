#include "PlaneGameScene.h"
#include "MyPlane.h"
#include "MyBullet.h"
#include "MyBackground.h"

USING_NS_CC;

bool PlaneGameScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCScene::init());

		//	Load all picture
		CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
		cache->addSpriteFramesWithFile("textureTransparentPack.plist", "textureTransparentPack.png");
		cache->addSpriteFramesWithFile("textureOpaquePack.plist", "textureOpaquePack.png");
		cache->addSpriteFramesWithFile("explosion.plist", "explosion.png");

		//	BackGround init
		MyBackground *pBackgroud = MyBackground::create();
		this->addChild(pBackgroud);

		//	My plane init
		MyPlane *pMyPlane = MyPlane::getSharedMyPlane();
		this->addChild(pMyPlane);

		bRet = true;
	} while (0);
	return bRet;
}