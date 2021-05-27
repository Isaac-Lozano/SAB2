#include "dlpot.h"
#include "../entity.h"
#include "../camera.h"
#include "../../engineTester/main.h"
#include "../../models/models.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../toolbox/maths.h"
#include "../../collision/collisionmodel.h"
#include "../../collision/collisionchecker.h"
#include "../controllableplayer.h"
#include "../../particles/particleresources.h"
#include "../../particles/particle.h"
#include "../../particles/particlemaster.h"

std::list<TexturedModel*> DL_Pot::models;
CollisionModel* DL_Pot::cmOriginal = nullptr;

DL_Pot::DL_Pot(float x, float y, float z, float rot)
{
    position.set(x, y, z);
    rotX = 0;
    rotY = rot;
    rotZ = 0;

    scale = 1;
    visible = true;

    updateTransformationMatrix();

    collideModelOriginal = DL_Pot::cmOriginal;
    collideModelTransformed = collideModelOriginal->duplicateMe();

    CollisionChecker::addCollideModel(collideModelTransformed);

    updateCollisionModel();
}

void DL_Pot::step()
{
    if (Global::gameMainPlayer->canBreakObjects())
    {
        collideModelTransformed->tangible = false;

        const float hitPad = 5.0f;

        Vector3f diff = Global::gameMainPlayer->getCenterPosition() - position;
        if (fabsf(diff.x) <= 10 + hitPad &&
            fabsf(diff.z) <= 10 + hitPad &&
                  diff.y  <= 20 + hitPad &&
                  diff.y  >=  0 - hitPad)
        {
            //explode and die

            const float height = 10.0f;
            const float spread = 20.0f;

            Vector3f spd(0, 0, 0);

            for (int i = 12; i != 0; i--)
            {
                Vector3f pos(
                    getX() + spread*(Maths::random() - 0.5f),
                    getY() + spread*(Maths::random() - 0.5f) + height,
                    getZ() + spread*(Maths::random() - 0.5f));

                ParticleMaster::createParticle(ParticleResources::textureExplosion1, &pos, &spd, 0, 1.55f, 0, 3*Maths::random() + 8, 0, false, false, 1.0f, true);
            }

            CollisionChecker::deleteCollideModel(collideModelTransformed);
            Global::deleteChunkedEntity(this);
            collideModelTransformed = nullptr;
            visible = false;
            Global::gameMainPlayer->vel.scale(0.8f);
        }
    }
    else
    {
        collideModelTransformed->tangible = true;
    }
}

std::list<TexturedModel*>* DL_Pot::getModels()
{
    return &DL_Pot::models;
}

void DL_Pot::loadStaticModels()
{
    if (DL_Pot::models.size() > 0)
    {
        return;
    }

    #ifdef DEV_MODE
    std::fprintf(stdout, "Loading DL_Pot static models...\n");
    #endif

    ObjLoader::loadModel(&DL_Pot::models, "res/Models/Levels/DryLagoon/Objects/", "Pot");

    if (DL_Pot::cmOriginal == nullptr)
    {
        DL_Pot::cmOriginal = ObjLoader::loadCollisionModel("Models/Levels/DryLagoon/Objects/", "PotCollision");
    }
}

void DL_Pot::deleteStaticModels()
{
    #ifdef DEV_MODE
    std::fprintf(stdout, "Deleting DL_Pot static models...\n");
    #endif

    Entity::deleteModels(&DL_Pot::models);
    Entity::deleteCollisionModel(&DL_Pot::cmOriginal);
}