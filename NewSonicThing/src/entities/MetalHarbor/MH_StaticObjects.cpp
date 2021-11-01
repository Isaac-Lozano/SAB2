#include "mhstaticobjects.h"
#include "../entity.h"
#include "../camera.h"
#include "../../engineTester/main.h"
#include "../../models/models.h"
#include "../../loading/modelloader.h"
#include "../../toolbox/maths.h"
#include "../../collision/collisionmodel.h"
#include "../../collision/collisionchecker.h"
#include "../dummy.h"

std::list<TexturedModel*> MH_StaticObjects::models;
std::list<TexturedModel*> MH_StaticObjects::modelsVertexColours;
std::list<TexturedModel*> MH_StaticObjects::modelsTransparent;
CollisionModel* MH_StaticObjects::cmOriginal;

MH_StaticObjects::MH_StaticObjects()
{
    position.x = 0;
    position.y = 0;
    position.z = 0;
    rotX = 0;
    rotY = 0;
    rotZ = 0;

    scale = 1;
    visible = true;
    
    setupModelVertexColours();
    setupModelTransparent();

    updateTransformationMatrix();

    collideModelOriginal = MH_StaticObjects::cmOriginal;
    collideModelTransformed = collideModelOriginal->duplicateMe();

    CollisionChecker::addCollideModel(collideModelTransformed);

    updateCollisionModel();
}

void MH_StaticObjects::step() {}

std::list<TexturedModel*>* MH_StaticObjects::getModels()
{
    return &MH_StaticObjects::models;
}

void MH_StaticObjects::loadStaticModels()
{
    if (MH_StaticObjects::models.size() > 0)
    {
        return;
    }

    #ifdef DEV_MODE
    std::fprintf(stdout, "Loading MH_StaticObjects static models...\n");
    #endif

    ModelLoader::loadModel(&MH_StaticObjects::models, "res/Models/Objects/MetalHarbor/StaticObjects/", "StaticObjects");
    ModelLoader::loadModel(&MH_StaticObjects::modelsVertexColours, "res/Models/Objects/MetalHarbor/StaticObjects/", "StaticObjectsVertexColours");
    ModelLoader::loadModel(&MH_StaticObjects::modelsTransparent, "res/Models/Objects/MetalHarbor/StaticObjects/", "StaticObjectsTransparent");

    setModelsRenderOrder(&MH_StaticObjects::modelsTransparent, 1);

    if (MH_StaticObjects::cmOriginal == nullptr)
    {
        MH_StaticObjects::cmOriginal = ModelLoader::loadCollisionModel("Models/Objects/MetalHarbor/StaticObjects/", "StaticObjectsCollision");
    }
}

void MH_StaticObjects::deleteStaticModels()
{
    #ifdef DEV_MODE
    std::fprintf(stdout, "Deleting MH_StaticObjects static models...\n");
    #endif

    Entity::deleteModels(&MH_StaticObjects::models);
    Entity::deleteModels(&MH_StaticObjects::modelsVertexColours);
    Entity::deleteModels(&MH_StaticObjects::modelsTransparent);
    Entity::deleteCollisionModel(&MH_StaticObjects::cmOriginal);
}

void MH_StaticObjects::setupModelVertexColours()
{
    modelVertexColours = new Dummy(&MH_StaticObjects::modelsVertexColours);
    modelVertexColours->setVisible(true);
    INCR_NEW("Entity");
    Global::addEntity(modelVertexColours);
}

void MH_StaticObjects::setupModelTransparent()
{
    modelTransparent = new Dummy(&MH_StaticObjects::modelsTransparent);
    modelTransparent->setVisible(true);
    INCR_NEW("Entity");
    Global::addEntity(modelTransparent);
}
