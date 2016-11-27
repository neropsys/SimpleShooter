#include "InputHandler.h"
using namespace cocos2d;
std::unique_ptr<InputHandler> InputHandler::Init()
{
	auto ret = std::make_unique<InputHandler>();
	return std::move(ret);
}

void InputHandler::handleInput()
{
	
}

InputHandler::InputHandler() :
	fireKey(EventKeyboard::KeyCode::KEY_SPACE),
	moveRightKey(EventKeyboard::KeyCode::KEY_D),
	moveLeftKey(EventKeyboard::KeyCode::KEY_A),
	moveUpKey(EventKeyboard::KeyCode::KEY_W),
	moveDownKey(EventKeyboard::KeyCode::KEY_S),
	m_eventListener(EventListenerKeyboard::create())
{

}
