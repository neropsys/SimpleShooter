#pragma once
#include "cocos2d.h"
#include <string>
class GameObject : public cocos2d::Node {

protected:
	virtual void onOutOfArea()=0;
	virtual bool init(const std::string& fileName);
	virtual ~GameObject() {};
	GameObject();
protected:
	cocos2d::Rect m_movableArea;
	cocos2d::Size m_visibleSize;
	cocos2d::Vec2 m_origin;
	cocos2d::Sprite* m_sprite;

};

