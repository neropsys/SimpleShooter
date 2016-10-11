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


	auto enemy = Enemy::create("airplane.png");
	enemy->setRotation(180);
	enemy->setPosition(Vec2(origin.x + visibleSize.width /3, origin.y + visibleSize.height / 3));
	enemy->setDestinationPos(Vec2(origin.x + visibleSize.width / 3, origin.y + visibleSize.height / 3));
	enemy->setStartPos(Vec2(origin.x + visibleSize.width / 3, origin.y + visibleSize.height / 3));
	this->addChild(enemy);

	
	//auto contactListener = EventListenerPhysicsContact::create();
	//contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	//getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
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


bool HelloWorld::onContactBegin(cocos2d::PhysicsContact& contact)
{
	/*auto aObj = contact.getShapeA()->getBody();
	auto bObj = contact.getShapeB()->getBody();
	if ((aObj->getCategoryBitmask() & bObj->getCollisionBitmask() != 0) ||
		(bObj->getCategoryBitmask() & aObj->getCollisionBitmask() != 0)) {
		//static_cast<ICollidable>(contact.getShapeA()->getBody()->getNode())
		auto aCollision = contact.getShapeA()->getBody()->get;
		dynamic_cast<GameObject*>(aCollision)->collided("fds");
		//collision((ICollidable*)aCollision);
		contact.getShapeB()->getBody()->getNode()->removeFromParent();
	}*/

	return true;
}
