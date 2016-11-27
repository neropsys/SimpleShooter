#pragma once
#include "cocos2d.h"
#include "GameObject.h"
#include "IShootable.h"
#include "Projectile.h"
#include "InputHandler.h"
#include <map>
class InputHandler;
class Player : public GameObject, IShootable {
public:
	CUSTOM_CREATE_FUNC(Player);
	virtual bool onContactBegin(cocos2d::PhysicsContact& contact) override;
	virtual void shoot(float delta) override;

	const inline void SetCooldown(float cd) { m_cooldown = cd; }
	const inline float GetCooldown() { return m_cooldown;}
	inline float GetShootInterval()const { return m_shootInterval; }
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
	std::shared_ptr<InputHandler> m_inputHandler;
	Projectile* m_projectile;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> m_keyInput;
	float m_cooldown;
	float m_shootInterval;

};