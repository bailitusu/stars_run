//
//  GameScene.h
//  first
//
//  Created by yuhan zhang on 11/17/14.
//
//

#ifndef __first__GameScene__
#define __first__GameScene__

#include <cocos2d.h>
#include "SimpleAudioEngine.h"
#include "BgLayer.h"
#include "PlayerLayer.h"

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    static bool GOD_MODE;
};


#endif /* defined(__first__GameScene__) */
