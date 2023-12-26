#include "MainScene.h"
#include <string>

USING_NS_AX;

Sprite *MainScene::createBomb()
{
    // create animation
    auto spriteFrameCache = SpriteFrameCache::getInstance();
    spriteFrameCache->addSpriteFramesWithFile("animation.plist", "bomb.png");

    // create sprites
    Vector<SpriteFrame*> frames;
    char frameName[100];

    for(int i = 1; i <= 4; i++) {
        sprintf(frameName, "frame%d.png", i);

        SpriteFrame* frame = spriteFrameCache->getSpriteFrameByName(frameName);

        if(frame) {
            frames.pushBack(frame);
        }
    }

    // create animation
    auto animation = Animation::createWithSpriteFrames(frames, 0.1f);
    auto animate = Animate::create(animation);

    auto bomb = Sprite::create();
    bomb->runAction(RepeatForever::create(animate));

    bomb->setName("shoot");
    bomb->setContentSize(Vec2(78, 64));

    // setup the physical body
    auto physicsBody = PhysicsBody::createCircle(bomb->getContentSize().width / 2, PhysicsMaterial(1.0f, 0.1f, 0.8f));
    physicsBody->setMass(1.0f);
    bomb->setPhysicsBody(physicsBody);

    return bomb;
}

bool MainScene::init()
{
    if (!Scene::initWithPhysics())
    {
        return false;
    }

    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    auto safeArea = _director->getSafeAreaRect();
    auto safeOrigin = safeArea.origin;

    // create the bomb
    auto bomb = createBomb();
    bomb->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    addChild(bomb);

    // scheduleUpdate() is required to ensure update(float) is called on every loop
    scheduleUpdate();

    return true;
}
