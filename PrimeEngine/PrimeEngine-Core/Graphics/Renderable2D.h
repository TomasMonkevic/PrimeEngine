#ifndef PRIME_RENDERABLE2D
#define PRIME_RENDERABLE2D

#include <GL\glew.h>
#include <Math/Math.h>
#include "Color.h"
#include "Renderer2D.h"
#include "Texture.h"
#include "..\DllExport.h"

namespace PrimeEngine { namespace Graphics {

	struct VertexData
	{
		Math::Vector3 position;
		unsigned color32;
		Math::Vector2 textureCord;
		float texture;
	};

	//also probably not needed
	class PRIMEENGINEAPI Renderable2D //should probably be a component or sprite is enough
	{
	protected:
		Math::Vector2 _size;
		Color _color = Color::white;
		Math::Vector2 _textureCord[4];
		Texture* _texture;

	private:
		void SetTextureCords()
		{
			_textureCord[0] = Math::Vector2(0, 1);
			_textureCord[1] = Math::Vector2(1, 1);
			_textureCord[2] = Math::Vector2(1, 0);
			_textureCord[3] = Math::Vector2(0, 0);
		}

	public:
		Renderable2D(const Math::Vector2& size, Texture* texture, const Color& color) //change the same as sprite constructor
			: _size(size), _texture(texture), _color(color)
		{
			SetTextureCords();
		}

		virtual ~Renderable2D()
		{

		}

		virtual void Submit(Renderer2D* renderer) const
		{
			renderer->Submit(this);
		}

		inline const Math::Vector2& GetSize() const
		{
			return _size;
		}

		inline const Color& GetColor() const
		{
			return _color;
		}

		inline const Math::Vector2& GetTextureCords(unsigned index) const
		{
			return _textureCord[index];
		}

		inline const GLuint GetTextureId() const
		{
			return _texture ? _texture->GetId() : 0;
		}
	};
}}

#endif // !PRIME_RENDERABLE2D