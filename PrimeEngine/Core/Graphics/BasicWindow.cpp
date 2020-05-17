#pragma once

#include <Graphics/BasicWindow.h>
#include <Graphics/OpenGL.h>

namespace PrimeEngine
{
	namespace Graphics
	{
        void BasicWindow::Clear() {
            GlCall(glClearColor(_color[0], _color[1], _color[2], _color[3]));
			GlCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        }

        void BasicWindow::SetSize(int width, int height) {
			_width = width;
			_height = height;
        }

        Math::Vector2 BasicWindow::GetSize() const {
			return Math::Vector2((float)_width, (float)_height);
        }

        void BasicWindow::SetColor(const Color& color) {
            _color = color;
        }

        const Color& BasicWindow::GetColor() const {
            return _color;
        }
	}
}