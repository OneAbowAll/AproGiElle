#pragma once
#define DEBUG 1

#include <GL/glew.h>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) if(DEBUG){ GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__));}

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};