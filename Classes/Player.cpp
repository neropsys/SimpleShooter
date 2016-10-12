#include "Player.h"
#include "Constants.h"

USING_NS_CC;
#define COCOS2D_DEBUG 1
Player::Player():
	m_cooldown(0.f),
	m_shootInterval(0.5f),
	m_previousPosition(this->getPosition()),
	m_projectile(Projectile::create("red-dot-hi.png"))

{
}

Player::~Player()
{
	m_projectile->release();
	m_eventListener->release();
	m_collisionListener->release();
}

void Player::onOutOfArea()
{
	if (m_movableArea.containsPoint(this->getPosition()) == false) {
		this->setPosition(m_previousPosition);
	}
}

bool Player::init(const std::string& fileName)
{
	if (GameObject::init(fileName) == false)
		return false;
	m_cooldown = m_shootInterval;
	this->setName(PLAYER);
	m_projectile->setVelocity(Vec2(0, 2.f));
	m_projectile->setMask(PLAYER_PROJ_MASK);
	m_projectile->retain();

	m_movableArea = Rect(
		m_origin.x + m_sprite->getContentSize().width / 2,
		m_origin.y + m_sprite->getContentSize().height / 2,
		(m_origin.x + m_visibleSize.width) - (m_sprite->getContentSize().width * 2 + m_sprite->getContentSize().width / 2),
		(m_origin.y + m_visibleSize.height) / 2 - m_sprite->getContentSize().height / 2);

	//make variable
	m_eventListener = EventListenerKeyboard::create();
	m_eventListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* eventPtr) {

		Vec2 location = eventPtr->getCurrentTarget()->getPosition();

		if (m_keyInput.find(keyCode) == m_keyInput.end()) {
			m_keyInput[keyCode] = true;
		}

	};
	m_eventListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* eventPtr) {
		m_keyInput.erase(keyCode);
		if(keyCode == EventKeyboard::KeyCode::KEY_SPACE)
			m_cooldown = m_shootInterval;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_eventListener, this);


	 m_collisionListener->onContactBegin = CC_CALLBACK_1(Player::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_collisionListener, this);

	auto spriteBody = PhysicsBody::createCircle(10.f, PhysicsMaterial(0, 0, 0));
	spriteBody->setCategoryBitmask(PLAYER_MASK);
	spriteBody->setContactTestBitmask(PLAYER_MASK);
	spriteBody->setCollisionBitmask(OBJ_SPACE);
	m_sprite->setPhysicsBody(spriteBody);

	scheduleUpdate();
	return true;
}

bool Player::isKeyPressed(cocos2d::EventKeyboard::KeyCode code)
{
	if (m_keyInput.find(code) != m_keyInput.end())
		return m_keyInput[code];
	return false;
}



void Player::update(float delta)
{

	m_previousPosition = this->getPosition();
	Vec2 position = this->getPosition();
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_A)) {
		position.x-=2;
	}
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_D)) {
		position.x+=2;
	}
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_W)) {
		position.y+=2;
	}
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_S)) {
		position.y-=2;
	}
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_SPACE)) {

		shoot(delta);
		
	}
	setPosition(position);
	onOutOfArea();
}




bool Player::onContactBegin(cocos2d::PhysicsContact& contact)
{
	if (GameObject::onContactBegin(contact) == false)
		return false;
	this->pause();
	setVisible(false);

	m_keyInput.clear();

	return true;
}

void Player::shoot(float delta)
{
	m_cooldown += delta;

	if (m_cooldown >= m_shootInterval) {	
		auto fakeOne = m_projectile->clone();
		Vec2 currentVelocity = this->getPosition() - m_previousPosition;
		fakeOne->setVelocity(fakeOne->getVelocity() + currentVelocity);
		fakeOne->setPosition(this->getPosition().x, this->getPosition().y + m_sprite->getContentSize().height / 2);
		
		this->getParent()->addChild(fakeOne);
		m_cooldown = 0;
	}
}
