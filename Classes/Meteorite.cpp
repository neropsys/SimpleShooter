#include "Meteorite.h"
#include "Constants.h"
USING_NS_CC;


Meteorite::Meteorite() :
	m_velocity(Vec2(0.f, -1.f))
{
}


Meteorite* Meteorite::create(const std::string& fileName)
{
	auto ret = new (std::nothrow) Meteorite();
	if (ret && ret->init(fileName)) {
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

bool Meteorite::init(const std::string& fileName)
{
	if (GameObject::init(fileName) == false)
		return false;
	auto spriteBody = PhysicsBody::createCircle(10.f, PhysicsMaterial(0, 0, 0));
	spriteBody->setCategoryBitmask(0x3);
	spriteBody->setContactTestBitmask(0x3);
	m_sprite->setPhysicsBody(spriteBody);

	m_movableArea = Rect(m_origin.x, m_origin.y, m_visibleSize.width, m_visibleSize.height);
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
	this->removeFromParent();
}
