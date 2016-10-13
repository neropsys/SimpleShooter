#pragma once
#include "cocos2d.h"
#include "GameObject.h"
#include "Constants.h"
class Projectile : public GameObject{
public:
	static enum BulletType{
		Explosive
	};
	CUSTOM_CREATE_FUNC(Projectile);
	Projectile* setVelocity(const cocos2d::Vec2& velocity);
	inline cocos2d::Vec2 getVelocity() { return m_velocity; }
	void setMask(int mask);
	virtual bool onContactBegin(cocos2d::PhysicsContact& contact) override;
	virtual Projectile* clone();
	void setBodySize(float size);
protected:
	virtual void update(float delta) override;
	virtual void onOutOfArea() override;
	virtual bool init(const std::string& fileName) override;
	virtual bool setListeners();
	virtual ~Projectile() {};
protected:
	Projectile();
	int m_mask;
	cocos2d::Vec2 m_velocity;

private:


	Projectile(const Projectile&) {};


};