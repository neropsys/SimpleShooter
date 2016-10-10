#pragma once
#include "cocos2d.h"
#include "GameObject.h"
#include "ICollidable.h"
#include "Constants.h"
class Projectile : public GameObject, public ICollidable {
public:
	static Projectile* create(const std::string& fileName);
	Projectile* setVelocity(const cocos2d::Vec2& velocity);
	inline void setMask(int mask) { m_sprite->getPhysicsBody()->setContactTestBitmask(mask); }
	virtual void collided(const std::string& name) override;

private:
	virtual void update(float delta) override;
	Projectile(const std::string& fileName);
private:
	cocos2d::Vec2 m_velocity;
	cocos2d::Sprite* m_sprite;

protected:



	virtual void onOutOfArea() override;

};