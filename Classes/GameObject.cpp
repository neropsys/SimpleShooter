#include "GameObject.h"
USING_NS_CC;

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
	m_origin(Director::getInstance()->getVisibleOrigin())
{
}
