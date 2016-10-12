#pragma once
#include "cocos2d.h"
#include "GameObject.h"
#include "Constants.h"
class Projectile : public GameObject{
public:
	CUSTOM_CREATE_FUNC(Projectile);
	Projectile* setVelocity(const cocos2d::Vec2& velocity);
	inline cocos2d::Vec2 getVelocity() { return m_velocity; }
	void setMask(int mask);
	virtual bool onContactBegin(cocos2d::PhysicsContact& contact) override;
	virtual Projectile* clone();

private:
	virtual void update(float delta) override;
	Projectile();
	Projectile(const Projectile&) {};
private:
	cocos2d::Vec2 m_velocity;

protected:

	virtual void onOutOfArea() override;
	virtual bool init(const std::string& fileName) override;
	virtual bool init();

protected:
	int m_mask;

};