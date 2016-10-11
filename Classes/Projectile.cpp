#include "Projectile.h"
USING_NS_CC;

Projectile* Projectile::setVelocity(const cocos2d::Vec2& velocity)
{
	m_velocity = velocity;
	return this;
}

void Projectile::setMask(int mask)
{
	m_sprite->getPhysicsBody()->setContactTestBitmask(mask);
	m_sprite->getPhysicsBody()->setCollisionBitmask(mask);
}

bool Projectile::onContactBegin(cocos2d::PhysicsContact& contact)
{
	if (GameObject::onContactBegin(contact) == false)
		return false;
	this->removeFromParentAndCleanup(true);
	return true;
}

void Projectile::update(float delta)
{

	Vec2 position = this->getPosition();
	setPosition(position.x + m_velocity.x, position.y + m_velocity.y);
	onOutOfArea();
	
}

Projectile::Projectile()
{	
}

void Projectile::onOutOfArea()
{
	if (m_movableArea.containsPoint(this->getPosition()) == false) {
		this->removeFromParentAndCleanup(true);
	}
}

bool Projectile::init(const std::string& fileName)
{
	if (GameObject::init(fileName) == false) return false;

	auto spriteBody = PhysicsBody::createCircle(5.f, PhysicsMaterial(0, 0, 0));
	spriteBody->setCategoryBitmask(0x1);
	m_sprite->setPhysicsBody(spriteBody);

	m_collisionListener->onContactBegin = CC_CALLBACK_1(Projectile::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_collisionListener, this);

	scheduleUpdate();
	return true;
}
