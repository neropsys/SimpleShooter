#pragma once
#include "cocos2d.h"
#include "KeyCommand.h"

#include <memory>
using namespace Command;
class InputHandler{

public:
	static std::unique_ptr<InputHandler> Init();
	void handleInput();
	inline cocos2d::EventListenerKeyboard* GetEventListener() { return m_eventListener; }
	InputHandler();
	~InputHandler() {};
	cocos2d::EventKeyboard::KeyCode fireKey;
	cocos2d::EventKeyboard::KeyCode moveUpKey;
	cocos2d::EventKeyboard::KeyCode moveDownKey;
	cocos2d::EventKeyboard::KeyCode moveLeftKey;
	cocos2d::EventKeyboard::KeyCode moveRightKey;

private:

	cocos2d::EventListenerKeyboard* m_eventListener;
	KeyCommand* m_fire;
	KeyCommand* m_moveUp;
	KeyCommand* m_moveDown;
	KeyCommand* m_moveLeft;
	KeyCommand* m_moveRight;
	
	std::map<cocos2d::EventKeyboard::KeyCode, bool> m_keyInput;
};