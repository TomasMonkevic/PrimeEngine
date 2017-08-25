#include "Sprite.h"
#include "Renderer2D.h"

namespace PrimeEngine { namespace Graphics {

	Sprite::Sprite(const Math::Vector2& size, const Color& color) //might not be needed
		: Sprite(size, NULL, color)
	{

	}

	Sprite::Sprite(const Math::Vector2& size, const char* texturePath, const Color& color)
		: _size(size), _color(color)
	{
		_texture = texturePath ? new Texture(texturePath) : NULL;
		SetTextureCords();
		AddType<Sprite>();
	}

	Sprite::Sprite(const Sprite& right)
		: _size(right._size), _color(right._color)
	{
		_texture = new Texture(right._texture->GetPath());
		for (unsigned i = 0; i < 4; i++)
		{
			_textureCord[i] = right._textureCord[i];
		}
	}

	Sprite::~Sprite()
	{
		delete _texture;
	}

	void Sprite::Submit(Renderer2D* renderer) const
	{
		renderer->Submit(this);
	}
}}