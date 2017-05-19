#ifndef BATCH_RENDERER2D
#define BATCH_RENDERER2D

#include <freetype-gl\freetype-gl.h>
#include "Renderer2D.h"
#include "Renderable2D.h"
#include <queue>
#include "Buffers\IndexBuffer.h"
#include "..\DllExport.h"

#define RENDERER_MAX_OBJECT_COUNT	10000
#define RENDERER_VERTEX_SIZE		sizeof(VertexData)
#define RENDERER_OBJECT_SIZE		RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE		RENDERER_OBJECT_SIZE * RENDERER_MAX_OBJECT_COUNT
#define RENDERER_INDECIES_SIZE		RENDERER_MAX_OBJECT_COUNT * 6

#define SHADER_POSITION_INDEX		0
#define SHADER_COLOR_INDEX			1
#define SHADER_TEXTURE_CORD_INDEX	2
#define SHADER_TEXTURE_INDEX		3

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI BatchRenderer2D : public Renderer2D
	{
	private:
		VertexData* _buffer;
		IndexBuffer* _ibo;
		GLuint _vao;
		GLuint _vbo;
		GLsizei _indexCount;
		std::vector<GLuint>* _textureSlots;
		ftgl::texture_atlas_t* _atlas;
		ftgl::texture_font_t* _font;

	public:
		BatchRenderer2D();
		~BatchRenderer2D();
		void Begin();
		void Submit(const Renderable2D* renderable2D) override;
		void DrawLabel(const std::string& text, const Math::Vector3& position, const Math::Vector4& color) override;
		void End();
		void Flush() override;
	};
}}

#endif // !BATCH_RENDERER2D