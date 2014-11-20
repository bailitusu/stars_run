//
//  playLayer.h
//  first
//
//  Created by yuhan zhang on 11/18/14.
//
//

#ifndef __first__playLayer__
#define __first__playLayer__

#include <cocos2d.h>
#include <Box2D/Box2d.h>
#include "GameScene.h"

class PlayerLayer : public cocos2d::Layer
{
public:
    PlayerLayer();
    virtual bool init();
    
    CREATE_FUNC(PlayerLayer);

    cocos2d::PhysicsWorld* world;
    
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Point origin;
    
    bool GOD_MODE;
    cocos2d::Vector<cocos2d::Sprite *> stars;
//    cocos2d::Array *upPipes;
//    cocos2d::Array *downPipes;
    
    cocos2d::Sprite* addOneStar();
    void addStars(float dt);
    void addUpPipe(cocos2d::Point p);
    void addDownPipe(cocos2d::Point p);
    void addGround();
    bool onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *event);
    bool onContactBegin(cocos2d::PhysicsContact& contact);
};

#endif /* defined(__first__playLayer__) */
