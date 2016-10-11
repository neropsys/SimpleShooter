#pragma once
#include "cocos2d.h"
#include "GameObject.h"
#include "ICollidable.h"
#include <map>
class Player : public GameObject, public ICollidable {

public:
	static Player* create(const std::string& fileName);

	virtual void collided(const std::string& name) override;

private:
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
	virtual void update(float delta) override;


	Player();
private:

	cocos2d::Vec2 m_previousPosition;



	std::map<cocos2d::EventKeyboard::KeyCode, bool> m_keyInput;
	float m_cooldown;
	float m_shootInterval;
protected:
	virtual void onOutOfArea() override;
	virtual bool init(const std::string& fileName)override;
};