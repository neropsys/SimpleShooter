#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Constants.h"
#include "GameObject.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
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
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	m_player = Player::create("CloseSelected.png");
	m_player->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 10 + origin.y));
	this->addChild(m_player, 0);

	auto meteor = Meteorite::create("stone.png");
	meteor->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y+ visibleSize.height / 2));	
	this->addChild(meteor);

	m_gamePaused = true;

	auto enemy = Enemy::create("airplane.png");
	enemy->setRotation(180);
	enemy->setPosition(Vec2(origin.x + visibleSize.width /3, origin.y + visibleSize.height / 3));
	enemy->setDestinationPos(Vec2(origin.x + visibleSize.width / 3, origin.y + visibleSize.height / 3));
	enemy->setStartPos(Vec2(origin.x + visibleSize.width / 3, origin.y + visibleSize.height / 3));
	this->addChild(enemy);
	
	m_label = Label::create("Press esc to begin", "Ariel", 16);
	m_label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(m_label);

	auto keyInputEvent = EventListenerKeyboard::create();
	keyInputEvent->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* eventPtr) {
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			if (m_gamePaused) {
				resumeGame();				
				m_gamePaused = false;
			}
			else {
				pauseGame();
				m_gamePaused = true;
			}
			break;
		default:
			break;
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyInputEvent, this);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    

}

void HelloWorld::update(float delta)
{
	if (!this->getChildByName(PLAYER)) {

	}
}

void HelloWorld::onEnter()
{
	Layer::onEnter();
	pauseGame();
}

void HelloWorld::pauseGame()
{
	for (const auto& it : this->getChildren()) {
		it->pause();
	}
	m_label->setVisible(true);

}

void HelloWorld::resumeGame()
{
	for (const auto& it : this->getChildren()) {
		it->resume();
	}
	m_label->setVisible(false);
}

