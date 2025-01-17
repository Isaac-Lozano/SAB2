#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

class Entity;
class Matrix4f;
class Light;
class Camera;
class EntityShader;
class EntityRenderer;
class TexturedModel;

#include <glad/glad.h>
#include <unordered_map>
#include <vector>
#include <list>

class MasterRenderer
{
private:
    static EntityShader* entityShader;
    static EntityRenderer* entityRenderer;

    static std::unordered_map<TexturedModel*, std::vector<Entity*>> entitiesMap;
    static std::unordered_map<TexturedModel*, std::vector<Entity*>> entitiesMapPass2;
    static std::unordered_map<TexturedModel*, std::vector<Entity*>> entitiesMapPass3;
    static std::unordered_map<TexturedModel*, std::vector<Entity*>> entitiesMapNoDepth;
    static std::unordered_map<TexturedModel*, std::vector<Entity*>> entitiesMapTransparent;
    static std::unordered_map<TexturedModel*, std::vector<Entity*>> entitiesMapPass6;

    static GLuint transparentFrameBuffer;
    static GLuint transparentDepthTexture;

    static void prepareNormalRender();

    static void prepareTransparentRender();

    static void prepareRenderDepthOnly();

public:
    static constexpr float NEAR_PLANE = 1.5f;
    static float FAR_PLANE;
    static float VFOV_BASE; // Vertical Field of View
    static float VFOV_ADDITION; // Additional Field of View from kart speed

    static Matrix4f* projectionMatrix;

    static GLuint currentBoundFramebuffer;

    static void init();

    static void render(Camera* camera, float clipX, float clipY, float clipZ, float clipW, float waterBlendAmount);

    static void cleanUp();

    static void processEntity(Entity* entity);

    static void clearAllEntities();

    // Add the models to the model->entities map and reserves 1000 entities per model.
    static void addTexturedModels(std::vector<TexturedModel*>* models);

    static void removeTexturedModels(std::vector<TexturedModel*>* models);

    static void clearAllTexturedModels();

    static void enableCulling();

    static void disableCulling();

    static void makeProjectionMatrix();

    static float getVFOV();
};
#endif
