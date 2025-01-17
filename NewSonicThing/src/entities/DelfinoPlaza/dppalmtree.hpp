#ifndef DPPALMTREE_H
#define DPPALMTREE_H

class TexturedModel;

#include <list>
#include "../entity.hpp"
#include "../collideableobject.hpp"

class DP_Palmtree : public CollideableObject
{
private:
    static std::vector<TexturedModel*> models;
    static CollisionModel* cmOriginal;

public:
    DP_Palmtree();
    DP_Palmtree(float x, float y, float z, float rotY);

    void step();

    std::vector<TexturedModel*>* getModels();

    static void loadStaticModels();

    static void deleteStaticModels();
};
#endif
