#ifndef MAINMENU_H
#define MAINMENU_H

class GUIText;
class Button;

#include <glad/glad.h>
#include <vector>
#include "../guis/guitexture.hpp"
#include "menu.hpp"

class MainMenu : public Menu
{
private:
    enum ButtonId { arcade, mission, extra, config, exit };

    int menuSelectionId;    // Current menu selection highlighted

    // Title card text graphics
    GLuint textureParallelogram; // Texture for button
    GLuint textureParallelogramBackdrop; // Texture for button highlight
    GLuint textureLogo; // Texture for logo

    GuiTexture logo;

    std::vector<Button*> menuButtons;

    int buttonCount;

    float aspectRatio;

    bool visible;

    // Animation
    int oldSelection;
    float animationTime;
    bool animating;
    int animationDirection;
    void resetAnimation();

    void unloadResources();

    void loadResources();

    void setVisible(bool visibleStatus);

public:
    MainMenu();

    ~MainMenu();

    Menu* step();

    void draw();
};

#endif