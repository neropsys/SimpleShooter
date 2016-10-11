#pragma once
#include "cocos2d.h"
#include "GameObject.h"
#include "ICollidable.h"
#include "Constants.h"
class Projectile : public GameObject, public ICollidable {
public:
	static Projectile* create(const std::string& fileName);
	Projectile* setVelocity(const cocos2d::Vec2& velocity);
	void setMask(int mask);
	virtual void collided(const std::string& name) override;

private:
	virtual void update(float delta) override;
	Projectile();
private:
	cocos2d::Vec2 m_velocity;

protected:



	virtual void onOutOfArea() override;


	virtual bool init(const std::string& fileName) override;

};