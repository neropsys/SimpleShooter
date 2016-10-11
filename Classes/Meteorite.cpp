#include "Meteorite.h"
#include "Constants.h"
USING_NS_CC;


Meteorite::Meteorite() :
	m_velocity(Vec2(0.f, -1.f))
{
}



bool Meteorite::onContactBegin(cocos2d::PhysicsContact& contact)
{
	if (GameObject::onContactBegin(contact) == false)
		return false;
	destroy();
	return true;
}

void Meteorite::onOutOfArea()
{
	if(m_movableArea.containsPoint(this->getPosition()) == false)
		destroy();
}

bool Meteorite::init(const std::string& fileName)
{
	if (GameObject::init(fileName) == false)
		return false;
	auto spriteBody = PhysicsBody::createCircle(10.f, PhysicsMaterial(0, 0, 0));
	spriteBody->setCategoryBitmask(METEORITE_MASK);
	spriteBody->setCollisionBitmask(OBJ_SPACE);
	spriteBody->setContactTestBitmask(METEORITE_MASK);
	m_sprite->setPhysicsBody(spriteBody);

	m_collisionListener->onContactBegin = CC_CALLBACK_1(Meteorite::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_collisionListener, this);

	scheduleUpdate();

	return true;
}

void Meteorite::update(float delta)
{
	Vec2 position = this->getPosition();
	setPosition(position.x + m_velocity.x, position.y + m_velocity.y);

	onOutOfArea();
}

void Meteorite::destroy()
{
	this->removeFromParentAndCleanup(true);
}
