#include "Player.h"
#include "Constants.h"
#include "Projectile.h"
USING_NS_CC;
#define COCOS2D_DEBUG 1
Player::Player():
	m_cooldown(0.f),
	m_shootInterval(0.5f),
	m_previousPosition(this->getPosition())
{
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

	

	m_movableArea = Rect(
		m_origin.x + m_sprite->getContentSize().width / 2,
		m_origin.y + m_sprite->getContentSize().height / 2,
		(m_origin.x + m_visibleSize.width) - (m_sprite->getContentSize().width * 2 + m_sprite->getContentSize().width / 2),
		(m_origin.y + m_visibleSize.height) / 2 - m_sprite->getContentSize().height / 2);

	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* eventPtr) {

		Vec2 location = eventPtr->getCurrentTarget()->getPosition();

		if (m_keyInput.find(keyCode) == m_keyInput.end()) {
			m_keyInput[keyCode] = true;
		}

	};
	eventListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* eventPtr) {
		m_keyInput.erase(keyCode);
		if(keyCode == EventKeyboard::KeyCode::KEY_SPACE)
			m_cooldown = m_shootInterval;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);


	 m_collisionListener->onContactBegin = CC_CALLBACK_1(Player::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_collisionListener, this);

	auto spriteBody = PhysicsBody::createCircle(10.f, PhysicsMaterial(0, 0, 0));
	spriteBody->setCategoryBitmask(0x1);
	spriteBody->setContactTestBitmask(0x1);
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
		--position.x;
	}
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_D)) {
		++position.x;
	}
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_W)) {
		++position.y;
	}
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_S)) {
		--position.y;
	}
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_SPACE)) {

		m_cooldown += delta;

		if (m_cooldown >= m_shootInterval) {
			Projectile* projectile = Projectile::create("red-dot-hi.png");
			projectile->setVelocity(Vec2(0, 1.f));
			projectile->setMask(PROJECTILE_MASK);
			projectile->setPosition(this->getPosition().x, this->getPosition().y + m_sprite->getContentSize().height / 2);
			this->getParent()->addChild(projectile);
			m_cooldown = 0;
		}
	}
	setPosition(position);
	onOutOfArea();
}




bool Player::onContactBegin(cocos2d::PhysicsContact& contact)
{
	if (GameObject::onContactBegin(contact) == false)
		return false;
	this->removeFromParentAndCleanup(true);
	return true;
}


