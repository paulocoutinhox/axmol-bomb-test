#include "MainScene.h"

USING_NS_AX;

Sprite *MainScene::createBomb()
{
    // create frames
    Vector<SpriteFrame *> animFrames;
    auto numFrames = 4;
    animFrames.reserve(numFrames);

    auto texture = Director::getInstance()->getTextureCache()->addImage("bomb.png");

    for (int i = 1; i < numFrames; i++)
    {
        auto frame = SpriteFrame::createWithTexture(texture, Rect(i * 78, 0, 78, 64));
        animFrames.pushBack(frame);
    }

    Sprite *bomb = Sprite::createWithSpriteFrame(animFrames.front());

    bomb->setName("shoot");
    bomb->setContentSize(Vec2(78, 64));
    bomb->setScale(0.5f);

    // create frame animation
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
    auto animate = Animate::create(animation);
    bomb->runAction(RepeatForever::create(animate));

    return bomb;
}

bool MainScene::init()
{
    if (!Scene::init())
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
