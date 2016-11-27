#pragma once
#include "cocos2d.h"
class Player;
namespace Command {
	class KeyCommand {
	public:
		KeyCommand() {};
		virtual ~KeyCommand() {};
		virtual void execute(Player& player, float delta) = 0;
	};
	class FireCommand : public KeyCommand {
	public:
		virtual void execute(Player& player, float delta);
	};
	class MoveCommand : public KeyCommand {
	public:
		virtual void execute(Player& player, float delta);
	};
}