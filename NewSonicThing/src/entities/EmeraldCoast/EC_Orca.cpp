#include <glad/glad.h>

#include "../entity.hpp"
#include "../../models/models.hpp"
#include "../../toolbox/vector.hpp"
#include "ecorca.hpp"
#include "../../loading/modelloader.hpp"
#include "../../engineTester/main.hpp"
#include "../../entities/playersonic.hpp"
#include "../../toolbox/maths.hpp"
#include "../camera.hpp"
#include "../../audio/audioplayer.hpp"
#include "../../particles/particle.hpp"
#include "../../particles/particlemaster.hpp"
#include "../../particles/particleresources.hpp"

#include <list>
#include <iostream>
#include <cmath>

std::vector<TexturedModel*> EC_Orca::models;

EC_Orca::EC_Orca()
{
    position.x = 1115.56f;
    position.y = -50.0f;
    position.z = 1390.38f;
    initX = position.x;
    initY = position.y;
    initZ = position.z;
    visible = false;
    seeTimer = 0.0f;
    inWaterPrevious = true;
    updateTransformationMatrix();
}

extern float dt;

void EC_Orca::step()
{
    if (seeTimer == 0.0f)
    {
        Vector3f playerPos = Global::gameMainPlayer->position;
        if (playerPos.x >    0.0f && playerPos.x <  824.0f &&
            playerPos.z > 1277.0f && playerPos.z < 1487.0f &&
            playerPos.y < 90.0f)
        {
            seeTimer = 0.000001f;
            setPosition(initX, initY, initZ);
            xVel = 0;
            yVel = 0;
            zVel = 0;
        }
    }

    visible = false;

    if (seeTimer > 0.0f)
    {
        seeTimer += dt;

        visible = true;

        float xDiff = Global::gameMainPlayer->position.x - position.x;
        float yDiff = 0 - position.y;
        float zDiff = Global::gameMainPlayer->position.z - position.z;

        float diffAng = atan2f(-zDiff, xDiff);

        float hSpd = sqrtf(xDiff*xDiff + zDiff*zDiff);

        float factor = 3*hSpd;

        if (factor < 5.25f*60)
        {
            xVel =  5.25f*60*cos(diffAng);
            zVel = -5.25f*60*sin(diffAng);
        }
        else
        {
            xVel =  factor*cos(diffAng);
            zVel = -factor*sin(diffAng);
        }
        
        if (yDiff > 0.0f)
        {
            yVel += 0.5f*60*60*dt;

            if (inWaterPrevious == false)
            {
                AudioPlayer::play(5, &position);
                Vector3f pos(position.x, 25, position.z);
                ParticleMaster::createParticle(ParticleResources::textureSplash, &pos, 40.0f/60, 40, false, true);
            }

            inWaterPrevious = true;
        }
        else
        {
            yVel -= 0.5f*60*60*dt;

            if (inWaterPrevious)
            {
                AudioPlayer::play(5, &position);
                Vector3f pos(position.x, 25, position.z);
                ParticleMaster::createParticle(ParticleResources::textureSplash, &pos, 40.0f/60, 40, false, true);
            }

            inWaterPrevious = false;
        }

        if (yVel > 10*60)
        {
            yVel = 10*60;
        }
        if (yVel < -10*60)
        {
            yVel = -10*60;
        }

        float spd = sqrtf(xVel*xVel + zVel*zVel);
        float newRotZ = atan2f(yVel, spd);

        rotY = (Maths::toDegrees(diffAng));//+5*cosf(seeTimer/10.0f));
        rotZ = (Maths::toDegrees(newRotZ));

        increasePosition(xVel*dt, yVel*dt, zVel*dt);
        updateTransformationMatrix();

        if (position.x < -630.0f)
        {
            seeTimer = -0.0001f;
        }

        if (Global::gameMainPlayer->position.y > 90.0f)
        {
            seeTimer = -0.0001f;
        }

        xDiff = Global::gameMainPlayer->position.x - position.x;
        yDiff = Global::gameMainPlayer->position.y - position.y;
        zDiff = Global::gameMainPlayer->position.z - position.z;

        float distSquared = (xDiff*xDiff + yDiff*yDiff + zDiff*zDiff);

        if (distSquared < 60*60)
        {
            Global::gameMainPlayer->takeDamage(&position);
            seeTimer = -0.0001f;
        }
    }
    else if (seeTimer < 0.0f) //running away under the water.
    {
        seeTimer -= dt;

        visible = true;

        yVel -= 0.5f*60*60*dt;

        if (yVel < -10*60)
        {
            yVel = -10*60;
        }

        if (position.y < 0.0f && !inWaterPrevious)
        {
            AudioPlayer::play(5, &position);
            Vector3f pos(position.x, 25, position.z);
            ParticleMaster::createParticle(ParticleResources::textureSplash, &pos, 40.0f/60, 40, false, true);

            inWaterPrevious = true;
        }

        float spd = sqrtf(xVel*xVel + zVel*zVel);
        float newRotZ = atan2f(yVel, spd);

        rotZ = (Maths::toDegrees(newRotZ));

        increasePosition(xVel*dt, yVel*dt, zVel*dt);
        updateTransformationMatrix();

        if (position.y < -350.0f)
        {
            seeTimer = 0.0f;
        }
    }
}

std::vector<TexturedModel*>* EC_Orca::getModels()
{
    return &EC_Orca::models;
}

void EC_Orca::loadStaticModels()
{
    if (EC_Orca::models.size() > 0)
    {
        return;
    }

    #ifdef DEV_MODE
    printf("Loading EC_Orca static models...\n");
    #endif

    ModelLoader::loadModel(&EC_Orca::models, "res/Models/Levels/EmeraldCoast/Orca/", "Orca");
}

void EC_Orca::deleteStaticModels()
{
    #ifdef DEV_MODE
    printf("Deleting EC_Orca static models...\n");
    #endif
    
    Entity::deleteModels(&EC_Orca::models);
}
