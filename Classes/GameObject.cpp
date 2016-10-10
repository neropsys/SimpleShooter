#include "GameObject.h"
USING_NS_CC;
GameObject::GameObject():
	m_visibleSize(Director::getInstance()->getVisibleSize()),
	m_origin(Director::getInstance()->getVisibleOrigin())
{
}
