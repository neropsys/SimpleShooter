#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <map>
#include "Player.h"
#include "Meteorite.h"
#include "Enemy.h"
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




	virtual void update(float delta) override;


	virtual void onEnter() override;

private:
	inline void setPhysicsWorld(cocos2d::PhysicsWorld* world) { m_world = world; }
	void pauseGame();
	void resumeGame();
	Player* m_player;
	cocos2d::PhysicsWorld* m_world;
	bool m_gamePaused;
	cocos2d::Label* m_label;



};

#endif // __HELLOWORLD_SCENE_H__
