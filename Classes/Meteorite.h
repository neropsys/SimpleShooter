#pragma once
#include "GameObject.h"
class Meteorite : public GameObject {
public:
	CUSTOM_CREATE_FUNC(Meteorite);

	virtual bool onContactBegin(cocos2d::PhysicsContact& contact) override;
	inline void setVelocity(const cocos2d::Vec2& velocity) { m_velocity = velocity; }
protected:
	virtual void onOutOfArea() override;

	virtual bool init(const std::string& fileName) override;

private:
	virtual void update(float delta) override;
	void destroy();
	Meteorite();
	cocos2d::Vec2 m_velocity;

};