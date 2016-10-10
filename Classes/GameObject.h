#pragma once
#include "cocos2d.h"
class GameObject : public cocos2d::Node {

protected:
	virtual void onOutOfArea()=0;
	virtual ~GameObject() {};
	GameObject();
protected:
	cocos2d::Rect m_movableArea;
	cocos2d::Size m_visibleSize;
	cocos2d::Vec2 m_origin;

};

