#include "Projectile.h"
USING_NS_CC;
Projectile* Projectile::create(const std::string& fileName)
{
	auto ret = new (std::nothrow) Projectile();
	if (ret && ret->init(fileName)) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

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

void Projectile::collided(const std::string& name)
{
	this->removeFromParent();
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
		this->removeFromParent();
	}
}

bool Projectile::init(const std::string& fileName)
{
	if (GameObject::init(fileName) == false) return false;

	auto spriteBody = PhysicsBody::createCircle(5.f, PhysicsMaterial(0, 0, 0));
	spriteBody->setCategoryBitmask(0x1);
	m_sprite->setPhysicsBody(spriteBody);
	m_movableArea = Rect(m_origin.x, m_origin.y, m_visibleSize.width, m_visibleSize.height);

	scheduleUpdate();
	return true;
}
