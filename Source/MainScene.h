#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "axmol.h"

class MainScene : public ax::Scene
{
public:
    bool init() override;

private:
    ax::Sprite *createBomb();
};

#endif // __MAIN_SCENE_H__
