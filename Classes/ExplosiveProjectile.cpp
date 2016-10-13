#include "ExplosiveProjectile.h"
#include <math.h>
USING_NS_CC;
using namespace std;
bool ExplosiveProjectile::setListeners()
{
	scheduleUpdate();
	return true;
	
}

Projectile* ExplosiveProjectile::clone()
{
	auto ret = new ExplosiveProjectile();
	ret->m_sprite = Sprite::createWithTexture(m_sprite->getTexture());
	ret->addChild(ret->m_sprite);
	ret->m_velocity = this->m_velocity;
	ret->m_fragCount = this->m_fragCount;
	ret->setListeners();
	ret->setBodySize(5.f);
	ret->setMask(this->m_mask);
	return ret;
}

bool ExplosiveProjectile::init(const std::string& fileName)
{
	if (!Projectile::init(fileName))
		return false;
	return setListeners();
}

ExplosiveProjectile::ExplosiveProjectile(int projectileCount) :m_fragCount(5), m_timePassed(0), m_explosionDelay(0.5f)
{
}


void ExplosiveProjectile::update(float delta)
{
	m_timePassed += delta;
	Vec2 position = this->getPosition();
	setPosition(position.x + m_velocity.x, position.y + m_velocity.y);

	if (m_timePassed > m_explosionDelay) {
		for (int i = 0; i < m_fragCount; i++) {
			Projectile* fragment = Projectile::create("red-dot-hi.png");
			fragment->setBodySize(1.f);
			fragment->setMask(ENEMY_PROJ_MASK);
			float angle = (180.f / m_fragCount) * i;
			Vec2 direction = Vec2(cos(CC_DEGREES_TO_RADIANS(angle)), sin(CC_DEGREES_TO_RADIANS(angle)));
			fragment->setVelocity(-direction*2);
			fragment->setPosition(this->getPosition());
			this->getParent()->addChild(fragment);
		}
		this->removeFromParentAndCleanup(true);
	}

}

