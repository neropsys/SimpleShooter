#include "GameObject.h"
USING_NS_CC;

bool GameObject::onContactBegin(cocos2d::PhysicsContact& contact)
{

	if (contact.getShapeA()->getBody()->getNode() != m_sprite &&
		contact.getShapeB()->getBody()->getNode() != m_sprite)
		return false;

	return true;
}


bool GameObject::init(const std::string& fileName)
{
	m_sprite = Sprite::create(fileName);
	if (m_sprite == nullptr) {
		return false;
	}
	this->addChild(m_sprite);
	return true;
}



GameObject::GameObject() :
	m_visibleSize(Director::getInstance()->getVisibleSize()),
	m_origin(Director::getInstance()->getVisibleOrigin()),
	m_collisionListener(EventListenerPhysicsContact::create())
{
	m_movableArea = Rect(m_origin.x, m_origin.y, m_visibleSize.width, m_visibleSize.height);
}
