#include <glad/glad.h>

#include <list>
#include <unordered_map>

#include "fontrenderer.hpp"
#include "../fontMeshCreator/fonttype.hpp"
#include "../fontMeshCreator/guitext.hpp"
#include "../fontMeshCreator/guinumber.hpp"
#include "fontshader.hpp"
#include "../engineTester/main.hpp"

FontRenderer::FontRenderer()
{
    shader = new FontShader("res/Shaders/fontRendering/FontVert.glsl", "res/Shaders/fontRendering/FontFrag.glsl"); INCR_NEW("FontShader");
}

void FontRenderer::render(
    std::unordered_map<FontType*, std::list<GUIText*>>* texts, 
    std::unordered_map<FontType*, std::list<GUINumber*>>* numbers)
{
    prepare();
    for (auto it = texts->cbegin(); it != texts->cend(); it++)
    {
        //auto kv = it._Ptr->_Myval;
        FontType* font = it->first;
        std::list<GUIText*> listOfTexts = it->second; //todo is this creating a local copy of the list?
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, font->getTextureAtlas());
        for (GUIText* text : listOfTexts)
        {
            if (text->visible)
            {
                renderText(text);
            }
        }
    }
    for (auto it = numbers->cbegin(); it != numbers->cend(); it++)
    {
        //auto kv = it._Ptr->_Myval;
        FontType* font = it->first;
        std::list<GUINumber*> listOfNumbers = it->second;
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, font->getTextureAtlas());
        for (GUINumber* number : listOfNumbers)
        {
            if (number->visible)
            {
                renderNumber(number);
            }
        }
    }
    endRendering();
}

void FontRenderer::cleanUp()
{
    shader->cleanUp();
}

void FontRenderer::prepare()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    shader->start();
}

void FontRenderer::renderText(GUIText* text)
{
    glBindVertexArray(text->getMesh());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    //shader->loadScale(text->getFontSize());
    shader->loadScale(1.0f);
    shader->loadColor(text->getColor());
    shader->loadTranslation(text->getPosition());
    glDrawArrays(GL_TRIANGLES, 0, text->getVertexCount());
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}

void FontRenderer::renderNumber(GUINumber* number)
{
    int numChars = (int)number->meshIds.size();
    shader->loadScale(number->size);
    for (int i = 0; i < numChars; i++)
    {
        glBindVertexArray(number->meshIds[i]);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        shader->loadColor(&number->colors[i]);
        shader->loadTranslation(&number->meshPositions[i]);
        glDrawArrays(GL_TRIANGLES, 0, number->meshVertexCounts[i]);
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}

void FontRenderer::endRendering()
{
    shader->stop();
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}
