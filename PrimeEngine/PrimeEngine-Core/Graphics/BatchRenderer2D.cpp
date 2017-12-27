#include "BatchRenderer2D.h"
#include <Utilities/Log.h>
#include <Graphics\Window.h>
#include <Graphics\Sprite.h>

namespace PrimeEngine { namespace Graphics {

	BatchRenderer2D::BatchRenderer2D()
	{
		_indexCount = 0;
		_textureSlots = new std::vector<GLuint>;
		_vbo = new VertexBuffer(NULL, RENDERER_BUFFER_SIZE, GL_DYNAMIC_DRAW);
		_vbo->Bind();

		_vao = new VertexArray();
		_vao->Bind();

		_vao->AddAttribute(SHADER_POSITION_INDEX, 3, GL_FLOAT, false, sizeof(VertexData), (const GLvoid*)(offsetof(VertexData, VertexData::position)));
		_vao->AddAttribute(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, true, sizeof(VertexData), (const GLvoid*)(offsetof(VertexData, VertexData::color32)));
		_vao->AddAttribute(SHADER_TEXTURE_CORD_INDEX, 2, GL_FLOAT, false, sizeof(VertexData), (const GLvoid*)(offsetof(VertexData, VertexData::textureCord)));
		_vao->AddAttribute(SHADER_TEXTURE_INDEX, 1, GL_FLOAT, false, sizeof(VertexData), (const GLvoid*)(offsetof(VertexData, VertexData::texture)));

		_vbo->Unbind();
		_vao->Unbind();

		GLushort* indecies = new GLushort[RENDERER_INDECIES_SIZE];
		int offset = 0;
		for (size_t i = 0; i < RENDERER_INDECIES_SIZE; i+=6)
		{
			indecies[i] = offset;
			indecies[i + 1] = offset + 1;
			indecies[i + 2] = offset + 2;
			indecies[i + 3] = offset + 2;
			indecies[i + 4] = offset + 3;
			indecies[i + 5] = offset;
			offset += 4;
		}
		_ibo = new IndexBuffer(indecies, RENDERER_INDECIES_SIZE);
		delete[] indecies;
	}

	BatchRenderer2D::~BatchRenderer2D()
	{
		delete _ibo;
		delete _textureSlots;
		delete _vbo;
		delete _vao;
	}

	void BatchRenderer2D::Begin()
	{
		_vbo->Bind();
		_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void BatchRenderer2D::Submit(const Sprite* renderable2D)
	{
		const Color& color = renderable2D->GetColor();
		const Math::Vector2& size = renderable2D->GetSize();
		const GLuint textureId = renderable2D->GetTextureId();
		const Transform& transform = renderable2D->GetGameObject()->GetTransform();
		float activeTexture = 0.0f;

		if (textureId > 0)
		{
			//find the texture
			bool isTextureFound = false;
			unsigned i = 0;
			while (i < _textureSlots->size())
			{
				if ((*_textureSlots)[i] == textureId)
				{
					activeTexture = (float)(i + 1);
					isTextureFound = true;
					break;
				}
				i++;
			}
			if (!isTextureFound)
			{
				//need to test this
				if (_textureSlots->size() >= MAX_TEXTURE_COUNT)
				{
					End();
					Flush();
					Begin();
					_textureSlots->clear();
				}
				_textureSlots->push_back(textureId);
				activeTexture = (float)_textureSlots->size();
			}
		}

		_buffer->position = *_transformationStackBack * transform.GetModelMatrix() * Math::Vector3(-size.x / 2.0f, size.y / 2.0f, 0);
		_buffer->color32 = color.ToColor32();
		_buffer->textureCord = renderable2D->GetTextureCords(0);
		_buffer->texture = activeTexture;
		_buffer++;

		_buffer->position = *_transformationStackBack * transform.GetModelMatrix() * Math::Vector3(size.x / 2.0f,  size.y / 2.0f, 0);
		_buffer->color32 = color.ToColor32();
		_buffer->textureCord = renderable2D->GetTextureCords(1);
		_buffer->texture = activeTexture;
		_buffer++;

		_buffer->position = *_transformationStackBack * transform.GetModelMatrix() * Math::Vector3(size.x / 2.0f, -size.y / 2.0f, 0);
		_buffer->color32 = color.ToColor32();
		_buffer->textureCord = renderable2D->GetTextureCords(2);
		_buffer->texture = activeTexture;
		_buffer++;

		_buffer->position = *_transformationStackBack * transform.GetModelMatrix() * Math::Vector3(-size.x / 2.0f, -size.y / 2.0f, 0);
		_buffer->color32 = color.ToColor32();
		_buffer->textureCord = renderable2D->GetTextureCords(3);
		_buffer->texture = activeTexture;
		_buffer++;

		_indexCount += 6;

		//if buffer is overflowed render the buffer and move on
		if (_indexCount >= RENDERER_INDECIES_SIZE)
		{
			End();
			Flush();
			Begin();
		}
	}

	void BatchRenderer2D::DrawLabel(const std::string& text, const  Math::Vector3& position, const Font& font)
	{
		using namespace ftgl;
		float activeTexture = 0.0f;

		//_font = texture_font_new_from_file(_atlas, font.size, font.fontName);

		//find the texture
		bool isTextureFound = false;
		unsigned i = 0;
		while (i < _textureSlots->size())
		{
			if ((*_textureSlots)[i] == font.atlas->id)
			{
				activeTexture = (float)(i + 1);
				isTextureFound = true;
				break;
			}
			i++;
		}
		if (!isTextureFound)
		{
			//need to test this
			if (_textureSlots->size() >= MAX_TEXTURE_COUNT)
			{
				End();
				Flush();
				Begin();
				_textureSlots->clear();
			}
			_textureSlots->push_back(font.atlas->id);
			activeTexture = (float)_textureSlots->size();
		}

		float x = position.x;

		float xScale = Window::GetWindow()->GetSize().x / 16.0f; //fix the hardcoded resolution
		float yScale = Window::GetWindow()->GetSize().y / 9.0f;

		for (int i = 0; i < text.size(); i++)
		{
			const char& c = text[i];
			texture_glyph_t* glyph = texture_font_get_glyph(font.font, c);

			if (glyph)
			{
				float x0 = x;
				float x1 = x0 + (float)glyph->width / xScale;
				float y0 = ((float)glyph->offset_y - (float)glyph->height) / yScale + position.y;
				float y1 = y0 + (float)glyph->offset_y / yScale;

				_buffer->position = *_transformationStackBack * Math::Vector3(x0, y0, 0);
				_buffer->textureCord = Math::Vector2(glyph->s0, glyph->t1);
				_buffer->texture = activeTexture;
				_buffer->color32 = font.color.ToColor32();
				_buffer++;

				_buffer->position = *_transformationStackBack * Math::Vector3(x0, y1, 0);
				_buffer->textureCord = Math::Vector2(glyph->s0, glyph->t0);
				_buffer->texture = activeTexture;
				_buffer->color32 = font.color.ToColor32();
				_buffer++;

				_buffer->position = *_transformationStackBack * Math::Vector3(x1, y1, 0);
				_buffer->textureCord = Math::Vector2(glyph->s1, glyph->t0);
				_buffer->texture = activeTexture;
				_buffer->color32 = font.color.ToColor32();
				_buffer++;

				_buffer->position = *_transformationStackBack * Math::Vector3(x1, y0, 0);
				_buffer->textureCord = Math::Vector2(glyph->s1, glyph->t1);
				_buffer->texture = activeTexture;
				_buffer->color32 = font.color.ToColor32();
				_buffer++;

				_indexCount += 6;
				x += (glyph->advance_x / xScale);
			}
		}
	}

	void BatchRenderer2D::End()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		_vbo->Unbind();
	}

	void BatchRenderer2D::Flush()
	{
		for (unsigned i = 0; i < _textureSlots->size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, (*_textureSlots)[i]);
		}

		_vao->Bind();
		_ibo->Bind();
		glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_SHORT, NULL);
		_ibo->Unbind();
		_vao->Unbind();
		_indexCount = 0;
	}
}}