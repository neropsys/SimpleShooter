#include "Projectile.h"
USING_NS_CC;

Projectile* Projectile::setVelocity(const cocos2d::Vec2& velocity)
{
	m_velocity = velocity;
	return this;
}

void Projectile::setMask(int mask)
{
	m_mask = mask;
	m_sprite->getPhysicsBody()->setContactTestBitmask(mask);
	m_sprite->getPhysicsBody()->setCategoryBitmask(mask);
	m_sprite->getPhysicsBody()->setGroup(-mask);
}

bool Projectile::onContactBegin(cocos2d::PhysicsContact& contact)
{
	if (GameObject::onContactBegin(contact) == false)
		return false;
	this->removeFromParentAndCleanup(true);
	return true;
}



Projectile* Projectile::clone()
{
	auto ret = new Projectile();

	ret->m_sprite = Sprite::createWithTexture(m_sprite->getTexture());
	ret->addChild(ret->m_sprite);
	ret->m_velocity = this->m_velocity;
	ret->setListeners();
	ret->setBodySize(5.f);
	ret->setMask(this->m_mask);
	return ret;
}

void Projectile::setBodySize(float size)
{
	auto body = PhysicsBody::createCircle(size, PhysicsMaterial(0, 0, 0));
	body->setCollisionBitmask(PROJ_SPACE);
	m_sprite->setPhysicsBody(body);

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
	setBodySize(5.f);

	return setListeners();
}

bool Projectile::setListeners()
{

	m_collisionListener->onContactBegin = CC_CALLBACK_1(Projectile::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_collisionListener, this);

	scheduleUpdate();
	return true;
}
