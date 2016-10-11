#include "Enemy.h"
#include "Constants.h"
USING_NS_CC;

Enemy::Enemy() :
	m_destPos(Vec2(0, 0)),
	m_startPos(getPosition()),
	m_cooldown(0.f),
	m_shootInterval(0.5f)
{
}

bool Enemy::onContactBegin(cocos2d::PhysicsContact& contact)
{
	this->removeFromParentAndCleanup(true);
	return true;
}

void Enemy::update(float delta)
{
	Vec2 direction = m_destPos - m_startPos;
	direction.normalize();
	Vec2 currentPosition = getPosition();
	setPosition(currentPosition.x + direction.x, currentPosition.y + direction.y);
	onOutOfArea();
}


void Enemy::onOutOfArea()
{
	if(m_movableArea.containsPoint(this->getPosition())==false)
		removeFromParentAndCleanup(true);
}

bool Enemy::init(const std::string& fileName)
{
	if (GameObject::init(fileName) == false)
		return false;
	this->setName(ENEMY);

	auto spriteBody = PhysicsBody::createCircle(10.f, PhysicsMaterial(0, 0, 0));
	spriteBody->setCategoryBitmask(0x1);
	spriteBody->setContactTestBitmask(0x2);
	m_sprite->setPhysicsBody(spriteBody);
	scheduleUpdate();
	return true;

}

