#pragma once
#include "cocos2d.h"
#include "Projectile.h"
#include "Constants.h"
#include "base/CCVector.h"

class ExplosiveProjectile : public Projectile {
public:
	CUSTOM_CREATE_FUNC(ExplosiveProjectile);


	virtual Projectile* clone() override;

protected:
	virtual bool init(const std::string& fileName) override;
	virtual bool setListeners() override;
public:
	ExplosiveProjectile();
	~ExplosiveProjectile() {};
private:
	float m_explosionDelay;
	float m_timePassed;
	int m_fragCount;
	virtual void update(float delta) override;
	cocos2d::Vector<Projectile*> m_frags;

};