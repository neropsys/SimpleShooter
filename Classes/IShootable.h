#pragma once
class IShootable {
public:
	virtual ~IShootable() {};
	virtual void shoot(float delta) = 0;
};