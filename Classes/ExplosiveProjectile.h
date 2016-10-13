#pragma once
#include "cocos2d.h"
#include "Projectile.h"
#include "Constants.h"

class ExplosiveProjectile : public Projectile {
public:
	CUSTOM_CREATE_FUNC(ExplosiveProjectile);


	virtual Projectile* clone() override;
	inline void setFragmentNum(int count) { this->m_fragCount = count;}
protected:
	virtual bool init(const std::string& fileName) override;
	virtual bool setListeners() override;
public:
	ExplosiveProjectile(int projectileCount=5);
	~ExplosiveProjectile() {};
private:
	float m_explosionDelay;
	float m_timePassed;
	int m_fragCount;
	virtual void update(float delta) override;


};