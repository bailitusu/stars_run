//
//  GameScene.c
//  first
//
//  Created by yuhan zhang on 11/17/14.
//
//

#include "GameScene.h"

USING_NS_CC;


Scene* GameScene::createScene()
{
    Scene *gameScene = NULL;
    gameScene = Scene::createWithPhysics();

    BgLayer *bgLayer = BgLayer::create();
    gameScene->addChild(bgLayer,0);
    
    PlayerLayer *playerLayer = PlayerLayer::create();
    gameScene->addChild(playerLayer,1);
    
//    GOD_MODE = false;
//    gameScene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
//    CCLOG("gravity = %f",gameScene->getPhysicsWorld()->getGravity().y);
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("background-music-aac.wav", true);
    
    return gameScene;
}












