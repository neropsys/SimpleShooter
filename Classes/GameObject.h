#pragma once
#include "cocos2d.h"
#include <string>
#define CUSTOM_CREATE_FUNC(__TYPE__) \
static __TYPE__* create(const std::string& fileName) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
    if (pRet && pRet->init(fileName)) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    CC_SAFE_DELETE(pRet); \
	return nullptr;\
}

class GameObject : public cocos2d::Node {
public:
	virtual bool onContactBegin(cocos2d::PhysicsContact& contact);
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
	cocos2d::EventListenerPhysicsContact* m_collisionListener;

};

