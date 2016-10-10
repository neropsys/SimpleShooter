#pragma once
#include <string>
class ICollidable {
public:
	virtual ~ICollidable() {};
	virtual void collided(const std::string& name) = 0;
};