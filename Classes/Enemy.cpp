#include "Enemy.h"
#include "Constants.h"
#include "Projectile.h"
USING_NS_CC;

Enemy::Enemy() :
	m_destPos(Vec2(0, 0)),
	m_startPos(getPosition()),
	m_cooldown(0.f),
	m_shootInterval(1.f),
	m_projectile(Projectile::create("red-dot-hi.png"))
{
}

Enemy::~Enemy()
{
	m_projectile->release();
}

bool Enemy::onContactBegin(cocos2d::PhysicsContact& contact)
{
	if (GameObject::onContactBegin(contact) == false)
		return false;

	this->removeFromParentAndCleanup(true);
	return true;
}

void Enemy::update(float delta)
{
	Vec2 direction = m_destPos - m_startPos;
	direction.normalize();
	Vec2 currentPosition = getPosition();
	Node::setPosition(currentPosition.x + direction.x, currentPosition.y + direction.y);

	shoot(delta);

	onOutOfArea();
}


void Enemy::shoot(float delta)
{

	m_cooldown += delta;

	if (m_cooldown >= m_shootInterval) {
		Projectile* projectile = m_projectile->clone();
		projectile->setPosition(this->getPosition().x, this->getPosition().y - m_sprite->getContentSize().height / 10);
		projectile->setRotation(getRotation());

		this->getParent()->addChild(projectile);
		m_cooldown = 0;
	}
}

void Enemy::setPosition(const Vec2& position)
{
	GameObject::setPosition(position);
	m_startPos = position;
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
	m_projectile->setVelocity(Vec2(0, -1.f));
	m_projectile->setMask(ENEMY_PROJ_MASK);
	m_projectile->retain();

	auto spriteBody = PhysicsBody::createCircle(10.f, PhysicsMaterial(0, 0, 0));
	spriteBody->setCategoryBitmask(ENEMY_MASK);
	spriteBody->setCollisionBitmask(OBJ_SPACE);
	spriteBody->setContactTestBitmask(ENEMY_MASK);
	m_sprite->setPhysicsBody(spriteBody);

	m_collisionListener->onContactBegin = CC_CALLBACK_1(Enemy::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_collisionListener, this);

	scheduleUpdate();
	return true;

}

