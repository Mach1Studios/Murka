#pragma once

#include "MurVbo.h"
#include "MurTexture.h"
#include "MurImage.h"
#include "MurkaTypes.h"
#include "MurkaAssets.h"

class MurkaRendererBase: public murka::MurkaAssets {
public:
    
    // Object drawing
    virtual void draw(const MurImage & image, float x, float y, float z, float w, float h, float sx, float sy, float sw, float sh) const = 0;
    virtual void draw(const MurTexture & texture, float x, float y, float z, float w, float h, float sx, float sy, float sw, float sh) const = 0;
    virtual void draw(const MurVbo & vbo, GLuint drawMode, int first, int total) const = 0;
    
    // Textures binding
    virtual void bind(const MurTexture & texture, int location) = 0;
    virtual void unbind(const MurTexture & texture, int location) = 0;
    
    // transformations
    virtual void pushView() = 0;
    virtual void popView() = 0;

    // setup matrices and viewport (upto you to push and pop view before and after)
    virtual void viewport(MurkaShape viewport) = 0;
    virtual void viewport(float x = 0, float y = 0, float width = -1, float height = -1, bool vflip=true) = 0;

    // rendering setup
    virtual void setLineWidth(float lineWidth) = 0;
    virtual void enableFill() = 0;
    virtual void disableFill() = 0;
    virtual void setLineSmoothing(bool smooth) = 0;
    virtual void enableAntiAliasing() = 0;
    virtual void disableAntiAliasing() = 0;
    virtual void pushStyle() = 0;
    virtual void popStyle() = 0;
    
    // color options
    virtual void setColor(int r, int g, int b) = 0; // 0-255
    virtual void setColor(int r, int g, int b, int a) = 0; // 0-255
    virtual void setColor(const MurkaColor & color) = 0;
    virtual void setColor(const MurkaColor & color, int _a) = 0;
    virtual void setColor(float gray) = 0; // new set a color as grayscale with one argument

    virtual void clear() = 0;
    virtual void clear(float r, float g, float b, float a=0) = 0;
    virtual void clear(float brightness, float a=0) = 0;
};
