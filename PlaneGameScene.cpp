#include "PlaneGameScene.h"
#include "MyPlane.h"
#include "MyBullet.h"
#include "MyBackground.h"
#include "EnemyPlane.h"
#include "EnemyBullet.h"
#include "time.h"
#include "GameOverScene.h"
#include "cocos2d.h"

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
		m_pMyPlane = MyPlane::newMyPlane();
		this->addChild(m_pMyPlane,1);

		//	My bullet init
		m_pMyBullet = MyBullet::newMyBullet();
		this->addChild(m_pMyBullet,0);

		srand(time(NULL));
		//	Enemy plane init
		m_pEnemyPlane = EnemyPlane::newEnemyPlane();
		this->addChild(m_pEnemyPlane,1);

		//	Enemy bullet init
		m_pEnemyBullet = EnemyBullet::newEnemyBullet();
		this->addChild(m_pEnemyBullet,0);

		//	Score recode init
		m_nScore = 0;
		CCString *sScore = CCString::createWithFormat("%d", m_nScore);
		CCDirector *pDirector = CCDirector::sharedDirector();
		CCSize sizeOfVisible = pDirector->getVisibleSize();

		m_pScore = CCLabelBMFont::create(sScore->getCString(), "arial-14.fnt");

		m_pScore->setPosition(ccp(sizeOfVisible.width - 25, sizeOfVisible.height - 25));
		m_pScore->setColor(ccRED);
		this->addChild(m_pScore, 1);

		//	preload music
		SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(BACKGROUND_MUSIC);
		SimpleAudioEngine::sharedEngine()->preloadEffect(FIRE_EFFECT_MUSIC);
		SimpleAudioEngine::sharedEngine()->preloadEffect(SHIP_DESTROY_EFFECT_MUSIC);
		SimpleAudioEngine::sharedEngine()->preloadEffect(EXPLODE_EFFECT_MUSIC);

		//	set volume
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5f);
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.3f);

		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(BACKGROUND_MUSIC, true);

		bRet = true;
	} while (0);
	return bRet;
}

void PlaneGameScene::addScore(int score)
{
	m_nScore += score;
	CCString *sScore = CCString::createWithFormat("%d", m_nScore);
	m_pScore->setString(sScore->getCString());
}

void PlaneGameScene::isGameOver()
{
	m_pMyBullet->unschedule(schedule_selector(MyPlane::changePicture));
	m_pMyBullet->unschedule(schedule_selector(MyPlane::shoot));

	m_pEnemyPlane->unschedule(schedule_selector(EnemyPlane::addEnemyPlane));

	GameOverScene *gameOver = GameOverScene::scene(m_nScore);

	CCDirector::sharedDirector()->replaceScene(gameOver);
}