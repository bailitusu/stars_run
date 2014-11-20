//
//  playLayer.cpp
//  first
//
//  Created by yuhan zhang on 11/18/14.
//
//

#include "PlayerLayer.h"

USING_NS_CC;
#define STAR_NUM 9
#define STAR_CATEGORY 0x01
#define GROUND_CATEGORY 0xFF

PlayerLayer::PlayerLayer(){
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
}

bool PlayerLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }

    GOD_MODE = false;
    
    
    /**
     here I want to use different interval time
     */
    this->schedule(schedule_selector(PlayerLayer::addStars),1.0f,STAR_NUM,0);



    addGround();
    addUpPipe(Point(visibleSize.width/2 + origin.x, visibleSize.height + 50));
    addDownPipe(Point(visibleSize.width/3,0));
    addDownPipe(Point(2*visibleSize.width/3,0));
    
    
    auto dispatcher = EventListenerTouchOneByOne::create();
    dispatcher->setSwallowTouches(true);
    dispatcher->onTouchBegan = CC_CALLBACK_2(PlayerLayer::onTouchBegan,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(dispatcher,this);
    
    auto contactListener=EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(PlayerLayer::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    return true;
}

void PlayerLayer::addStars(float dt){
    stars.pushBack(addOneStar());
}

Sprite* PlayerLayer::addOneStar(){
    
    Sprite *star = Sprite::create("star.png");
    star->setScale(2.0f);
    star->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height-150));
    
    Size starSize = star->getContentSize();
    
    PhysicsBody *starBody = PhysicsBody::createBox(starSize);
    starBody->setVelocity(Vec2(CCRANDOM_0_1() * (CCRANDOM_0_1() > 0.5?100:-100),CCRANDOM_0_1()*100));
    starBody->setAngularVelocity(2.0f);
    starBody->setCategoryBitmask(STAR_CATEGORY);
    starBody->setContactTestBitmask(0x01);
    
    star->setPhysicsBody((PhysicsBody *)starBody);
    this->addChild(star,5);

    return star;
}


void PlayerLayer::addGround(){
    /* ground sprite and physics body */
    Sprite *groundSprite = Sprite::create("ground.png");
    
    const float GROUND_SCALE_RATE = visibleSize.width / groundSprite->getContentSize().width;
    Size groundSize = groundSprite->getContentSize() * GROUND_SCALE_RATE;
    
    groundSprite->setScale(GROUND_SCALE_RATE);
    groundSprite->setPosition(Point(groundSize.width/2 + origin.x,
                                    groundSize.height/2 - visibleSize.height/10 + origin.y));
    
    PhysicsBody *bgGround = PhysicsBody::createEdgeBox(groundSprite->getContentSize()*GROUND_SCALE_RATE);
    bgGround->setCategoryBitmask(GROUND_CATEGORY);
    bgGround->setContactTestBitmask(0x01);
    
    groundSprite->setPhysicsBody(bgGround);
    this->addChild(groundSprite,3);
    
    
    /* screen edge node and physics body */
    PhysicsBody* screenBody = PhysicsBody::createEdgeBox(visibleSize);
    
    auto screenNode = Node::create();
    screenNode->setPosition(visibleSize.width/2, visibleSize.height/2);
    
    screenNode->setPhysicsBody(screenBody);
    this->addChild(screenNode);
}


void PlayerLayer::addUpPipe(Point pipePosition){
    Sprite *upPipe = Sprite::create("up_bar.png");
    upPipe->setPosition(pipePosition);
    
    PhysicsBody *pipeBody = PhysicsBody::createEdgeBox(upPipe->getContentSize());
    
    upPipe->setPhysicsBody(pipeBody);
    
    this->addChild(upPipe,1);
}


void PlayerLayer::addDownPipe(Point pipePosition){
    Sprite *downPipe = Sprite::create("down_bar.png");
    downPipe->setPosition(pipePosition);
    
    PhysicsBody *pipeBody = PhysicsBody::createEdgeBox(downPipe->getContentSize());
    
    downPipe->setPhysicsBody(pipeBody);
    
    this->addChild(downPipe,1);
}


bool PlayerLayer::onTouchBegan(Touch *touch, Event *event){
    Point touchPoint = touch->getLocationInView();
    touchPoint = Director::getInstance()->convertToGL(touchPoint);
    touchPoint = Point(touchPoint.x, touchPoint.y);
    
    for(int i=0;i<stars.size();i++){
        Sprite *s=stars.at(i);
        
        Point starPoint = s->getPosition();
        Size starSize = s->getContentSize();
        Rect starRect = Rect(starPoint.x - starSize.width,
                             starPoint.y - starSize.height,
                             starPoint.x + starSize.width,
                             starPoint.y + starSize.height); //note: star->setScale(2.0f)

        if(starRect.containsPoint(touchPoint)){
//            CCLOG("YOU CLICK IT");
            PhysicsBody *b = s->getPhysicsBody();
            
//            b->applyImpulse(Vect(100*(touchPoint.x - starPoint.x),100 * (touchPoint.y - starPoint.y)), touchPoint);
//            do not sure how impulse works
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pew-pew-lei.wav");
            Vect *v=new Vec2(-100 * (touchPoint.x - starPoint.x)/starSize.width,300.0f);
            b->setVelocity(*v);
        }
    }
    return true;
}


bool PlayerLayer::onContactBegin(PhysicsContact& contact){

    if(GOD_MODE){
        CCLOG("*****IN GOD MODE*****");
        return true;
    }
    
    int maskA=contact.getShapeA()->getBody()->getCategoryBitmask();
    int maskB=contact.getShapeB()->getBody()->getCategoryBitmask();
    CCLOG("on contact: A=%d\tB=%d",maskA,maskB);
    
    if((maskA == GROUND_CATEGORY && maskB == STAR_CATEGORY) ||
       (maskA == STAR_CATEGORY && maskB == GROUND_CATEGORY)){
        Director::getInstance()->end();
    }
    return true;
}











