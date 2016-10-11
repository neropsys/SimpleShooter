#pragma once
#include "GameObject.h"
class Enemy : public GameObject{
public:
	CUSTOM_CREATE_FUNC(Enemy);

	virtual bool onContactBegin(cocos2d::PhysicsContact& contact) override;
	inline void setDestinationPos(const cocos2d::Vec2& dest) { m_destPos = dest; }
	inline void setStartPos(const cocos2d::Vec2& start) { m_startPos = start; }

	virtual void update(float delta) override;

protected:
	Enemy();
	virtual ~Enemy() {};
	virtual void onOutOfArea() override;



	virtual bool init(const std::string& fileName) override;

private:

	cocos2d::Vec2 m_destPos;
	cocos2d::Vec2 m_startPos;
	float m_cooldown;
	float m_shootInterval;

};