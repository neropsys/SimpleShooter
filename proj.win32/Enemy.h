#pragma once
#include "cocos2d.h"
#include "GameObject.h"
#include "ICollidable.h"
class Enemy : public GameObject, public ICollidable{
public:
	static Enemy* create(const std::string& fileName);


	virtual void collided(const std::string& name) override;


	virtual void update(float delta) override;

protected:
	virtual void onOutOfArea() override;


};