#pragma once
#include "GameObject.h"
#include "ICollidable.h"
class Meteorite : public GameObject, public ICollidable {
public:
	static Meteorite* create(const std::string& fileName);

	virtual void collided(const std::string& name) override;
	inline void setVelocity(const cocos2d::Vec2& velocity) { m_velocity = velocity; }
protected:
	virtual void onOutOfArea() override;
private:
	virtual void update(float delta) override;
	void destroy();
	Meteorite(const std::string& fileName);

	cocos2d::Sprite* m_sprite;
	cocos2d::Vec2 m_velocity;

};