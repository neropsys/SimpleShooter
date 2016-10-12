#pragma once
#include "cocos2d.h"
#include "GameObject.h"
#include "IShootable.h"
#include "Projectile.h"
#include <map>
class Player : public GameObject, IShootable {

public:
	CUSTOM_CREATE_FUNC(Player);
	virtual bool onContactBegin(cocos2d::PhysicsContact& contact) override;
	virtual void shoot(float delta) override;

protected:
	virtual void onOutOfArea() override;
	virtual bool init(const std::string& fileName) override;
private:
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
	virtual void update(float delta) override;
	Player();
	~Player();
private:
	cocos2d::Vec2 m_previousPosition;
	Projectile* m_projectile;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> m_keyInput;
	float m_cooldown;
	float m_shootInterval;

};