#include "Meteorite.h"
#include "Constants.h"
USING_NS_CC;
Meteorite* Meteorite::create(const std::string& fileName)
{
	auto ret = new (std::nothrow) Meteorite(fileName);
	if (ret) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

void Meteorite::collided(const std::string& name)
{
	destroy();
}

void Meteorite::onOutOfArea()
{
	if(m_movableArea.containsPoint(this->getPosition()) == false)
		destroy();
}

void Meteorite::update(float delta)
{
	Vec2 position = this->getPosition();
	setPosition(position.x + m_velocity.x, position.y + m_velocity.y);

	onOutOfArea();
}

void Meteorite::destroy()
{
	this->removeFromParent();
}

Meteorite::Meteorite(const std::string& fileName) :
	m_velocity(Vec2(0.f, -1.f))
{
		m_sprite = Sprite::create(fileName);
		this->addChild(m_sprite);

		auto spriteBody = PhysicsBody::createCircle(10.f, PhysicsMaterial(0, 0, 0));
		spriteBody->setCategoryBitmask(0x3);
		spriteBody->setContactTestBitmask(0x3);
		m_sprite->setPhysicsBody(spriteBody);

		m_movableArea = Rect(m_origin.x, m_origin.y,m_visibleSize.width, m_visibleSize.height);
		scheduleUpdate();
}
