#ifndef CHAOSEMERALD_H
#define CHAOSEMERALD_H

class TexturedModel;

#include <list>
#include "entity.h"

class ChaosEmerald : public Entity
{
private:
    static std::list<TexturedModel*> models;

    bool found = false;
    int id = 0;
    float bobTimer = 0.0f;

public:
    ChaosEmerald();
    ChaosEmerald(float x, float y, float z, int id);

    void step();

    std::list<TexturedModel*>* getModels();

    static void loadStaticModels();

    static void deleteStaticModels();
};
#endif
