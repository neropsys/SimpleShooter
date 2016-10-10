#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <map>
#include "Player.h"
#include "Meteorite.h"
#include "Box2D/Box2D.h"
#include "Constants.h"
#include <memory>
class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);



private:
	inline void setPhysicsWorld(cocos2d::PhysicsWorld* world) { m_world = world; }
	Player* m_player;
	cocos2d::PhysicsWorld* m_world;
	
	bool onContactBegin(cocos2d::PhysicsContact& contact);

};

#endif // __HELLOWORLD_SCENE_H__
