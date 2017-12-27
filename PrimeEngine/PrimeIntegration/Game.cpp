#define P_LOG_LEVEL 2

#include "Game.h"
#include <time.h>

void TestGame::Awake()
{
	//make a method in the engine?
	//ShowWindow(GetConsoleWindow(), SW_HIDE);

	CreateWin("3D Rendering test", 1366, 768);
	//CreateWin("3D Rendering test");
	GetWindow()->EnableVSync(true);
	GetWindow()->SetColor(Color::black);

	//Matrix4x4 pr = Matrix4x4::Orthographic(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f);
	Matrix4x4 pr = Matrix4x4::Perspective(45.0f, 16.0f / 9.0f, -1.5f, 1.5f);

	mainCamera = new Camera(ShaderManagerI.CreateShader("gameShader", Shader::phong), pr);

	Vector3 cameraPosition(Vector3(0.0f, 0.0f, -10.0f)); //projection
	//Vector3 cameraPosition(Vector3(0, 0, 0.0f)); //ortho
	mainCamera->GetTransform().Position = cameraPosition;
	mainCamera->AddComponent(new FpsCamera());

	//gameLayer = new GameLayer(mainCamera);

	//player = new GameObject();
	//player->AddComponent(new Sprite (Vector2(17, 12) / 5, "Resources\\Textures\\bird1.png"));
	//gameLayer->Submit(player);
	TempVertexData vertecies[] = {
		{Vector3(-0.500000, -0.500000,  0.500000) * 3, 0xff0000ff },
		{Vector3( 0.500000, -0.500000,  0.500000) * 3, 0xff0000ff },
		{Vector3(-0.500000,  0.500000,  0.500000) * 3, 0xff0000ff },
		{Vector3( 0.500000,  0.500000,  0.500000) * 3, 0xff0000ff },
		{Vector3(-0.500000,  0.500000, -0.500000) * 3, 0xffffffff },
		{Vector3( 0.500000,  0.500000, -0.500000) * 3, 0xffffffff },
		{Vector3(-0.500000, -0.500000, -0.500000) * 3, 0xffffffff },
		{Vector3( 0.500000, -0.500000, -0.500000) * 3, 0xffffffff }
	};

	_vbo = new VertexBuffer(vertecies, sizeof(TempVertexData) * 8, GL_STATIC_DRAW);
	_vbo->Bind();

	_vao = new VertexArray();
	_vao->Bind();
	mainCamera->_shader->Enable();


	_vao->AddAttribute(0, 3, GL_FLOAT, false, sizeof(TempVertexData), (const GLvoid*)(offsetof(TempVertexData, TempVertexData::position)));
	_vao->AddAttribute(1, 4, GL_UNSIGNED_BYTE, true, sizeof(TempVertexData), (const GLvoid*)(offsetof(TempVertexData, TempVertexData::color32)));

	_vbo->Unbind();
	mainCamera->_shader->Disable();
	_vao->Unbind();

	GLushort indecies[] = {
		0, 1, 2,
		2, 1, 3,

		2, 3, 4,
		4, 3, 5,

		4, 5, 6,
		6, 5, 7,

		6, 7, 0,
		0, 7, 1,

		1, 7, 3,
		3, 7, 5,

		6, 0, 4,
		4, 0, 2
	};
	_ibo = new IndexBuffer(indecies, 36);
}

void TestGame::Update()
{
	//TODO could be called automaticaly when scene is implemented
	mainCamera->GetComponent<FpsCamera>()->Update(GetDeltaTime());
	if (InputPC::GetKeyDown(256)) //esc
	{
		GetWindow()->Close();
	}
}

void TestGame::Tick()
{
	PRIME_INFO(GetFPS(), " fps \n");
}

void TestGame::Render()
{
	//mainCamera->Render();
	//gameLayer->Render();

	mainCamera->Render();
	mainCamera->_shader->Enable();

	_vao->Bind();
	_ibo->Bind();
	glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_SHORT, NULL);
	_ibo->Unbind();
	_vao->Unbind();

	mainCamera->_shader->Disable();

}