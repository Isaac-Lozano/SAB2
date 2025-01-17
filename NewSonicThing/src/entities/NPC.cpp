#include <glad/glad.h>

#include "entity.hpp"
#include "../models/models.hpp"
#include "../toolbox/vector.hpp"
#include "npc.hpp"
#include "dummy.hpp"
#include "../loading/modelloader.hpp"
#include "../engineTester/main.hpp"
#include "../toolbox/maths.hpp"
#include "../toolbox/split.hpp"
#include "camera.hpp"
#include "../fontMeshCreator/guitext.hpp"
#include "controllableplayer.hpp"
#include "../guis/guimanager.hpp"
#include "../audio/audioplayer.hpp"

#include <list>
#include <iostream>
#include <cstring>
#include <string>

std::vector<TexturedModel*> NPC::models;
std::vector<TexturedModel*> NPC::modelsGlasses;
GUIText* NPC::messageGUI1 = nullptr;
GUIText* NPC::messageGUI2 = nullptr;

NPC::NPC()
{
    
}

NPC::~NPC()
{
    if (messageGUI1 != nullptr && (*messageGUI1->getTextString()) == myMessage1)
    {
        messageGUI1->deleteMe();
        delete messageGUI1; INCR_DEL("GUIText");
        messageGUI1 = nullptr;
    }
            
    if (messageGUI2 != nullptr && (*messageGUI2->getTextString()) == myMessage2)
    {
        messageGUI2->deleteMe();
        delete messageGUI2; INCR_DEL("GUIText");
        messageGUI2 = nullptr;
    }
}

NPC::NPC(float x, float y, float z, float dirX, float dirZ, int id, std::string message)
{
    position.x = x;
    position.y = y;
    position.z = z;
    rotX = 0;
    rotY = Maths::toDegrees(atan2f(-dirZ, dirX));
    rotZ = 0;
    scale = 0.8f;
    visible = true;
    this->id = id;
    updateTransformationMatrix();

    char msgBuf[512];
    memset(msgBuf, 0, 512);
    memcpy(msgBuf, message.c_str(), message.size());

    int splitLength = 0;
    char** msg = split(msgBuf, ';', &splitLength);

    myMessage1 = "";
    myMessage2 = "";

    if (splitLength == 1)
    {
        myMessage2 = msg[0];
    }
    else if (splitLength > 1)
    {
        myMessage1 = msg[0];
        myMessage2 = msg[1];
    }

    free(msg);

    std::string lookup = Global::levelNameDisplay+"_NPC_"+std::to_string(id);

    found = false;
    if (Global::gameSaveData.find(lookup) != Global::gameSaveData.end())
    {
        std::string isFound = Global::gameSaveData[lookup];
        if (isFound == "true")
        {
            found = true;
        }
    }

    glasses = new Dummy(&NPC::modelsGlasses); INCR_NEW("Entity");
    glasses->position = position;
    glasses->rotY = rotY;
    glasses->scale = scale;
    glasses->updateTransformationMatrix();
    Global::addEntity(glasses);

    if (found)
    {
        baseAlpha = 0.7f;
        glasses->baseAlpha = 0.7f;
        renderOrderOverride = 3;
        glasses->renderOrderOverride = 3;
    }

    // Don't let Tails collect NPC in levels other than cloud temple
    if (Global::currentCharacterType == Global::PlayableCharacter::Tails &&
        Global::levelId != LVL_CLOUD_TEMPLE)
    {
        Global::deleteEntity(this);
        Global::deleteEntity(glasses);
        return;
    }
}

void NPC::step()
{
    Vector3f diff = Global::gameMainPlayer->position - position;
    float mag = ((diff.x*diff.x)+(diff.z*diff.z));

    if (mag < 20*20 && diff.y > -3 && diff.y < 12)
    {
        if (!found)
        {
            AudioPlayer::play(7, &position);
            found = true;

            std::string lookup = Global::levelNameDisplay+"_NPC_"+std::to_string(id);
            Global::gameSaveData[lookup] = "true";
            Global::saveSaveData();
        }
        
        if (messageGUI1 == nullptr && myMessage1 != "")
        {
            float size = 3.0f/myMessage1.length();
            size = std::fminf(size, 0.1f);
            messageGUI1 = new GUIText(myMessage1, size, Global::fontVipnagorgialla, 0.5f, 0.75f, 4, true); INCR_NEW("GUIText");
        }
        
        if (messageGUI2 == nullptr && myMessage2 != "")
        {
            float size = 3.0f/myMessage2.length();
            size = std::fminf(size, 0.1f);
            messageGUI2 = new GUIText(myMessage2, size, Global::fontVipnagorgialla, 0.5f, 0.85f, 4, true); INCR_NEW("GUIText");
        }
    }
    else
    {
        if (messageGUI1 != nullptr && (*messageGUI1->getTextString()) == myMessage1)
        {
            messageGUI1->deleteMe();
            delete messageGUI1; INCR_DEL("GUIText");
            messageGUI1 = nullptr;
        }
            
        if (messageGUI2 != nullptr && (*messageGUI2->getTextString()) == myMessage2)
        {
            messageGUI2->deleteMe();
            delete messageGUI2; INCR_DEL("GUIText");
            messageGUI2 = nullptr;
        }
    }
}

std::vector<TexturedModel*>* NPC::getModels()
{
    return &NPC::models;
}

void NPC::loadStaticModels()
{
    if (NPC::models.size() > 0)
    {
        return;
    }

    #ifdef DEV_MODE
    printf("Loading NPC static models...\n");
    #endif

    ModelLoader::loadModel(&NPC::models,        "res/Models/Objects/NPC/", "NPC");
    ModelLoader::loadModel(&NPC::modelsGlasses, "res/Models/Objects/NPC/", "Glasses");

    setModelsRenderOrder(&NPC::modelsGlasses, 1);
}

void NPC::deleteStaticModels()
{
    #ifdef DEV_MODE
    printf("Deleting NPC static models...\n");
    #endif

    Entity::deleteModels(&NPC::models);
    Entity::deleteModels(&NPC::modelsGlasses);

    if (messageGUI1 != nullptr)
    {
        messageGUI1->deleteMe();
        delete messageGUI1; INCR_DEL("GUIText");
        messageGUI1 = nullptr;
    }

    if (messageGUI2 != nullptr)
    {
        messageGUI2->deleteMe();
        delete messageGUI2; INCR_DEL("GUIText");
        messageGUI2 = nullptr;
    }
}
