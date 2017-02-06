#include <iostream>
#include <Core\Math.h>
#include <Graphics\Window.h>
#include <Input.h>
//#include <Utilities/File.h>
#include <Graphics\Shader.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <Graphics\Renderable2D.h>
#include <Graphics\SimpleRenderer2D.h>

using namespace PrimeEngine::Math;
using namespace PrimeEngine::Graphics;
using namespace PrimeEngine::Input;

int main()
{
	Window* gameWindow = NULL;
	try
	{
		Window::SetWindow("Test Game", 1366, 768);
		//Window::SetWindow("Test Game", 800, 600);
		//Window::SetWindow("Test Game Full");
		gameWindow = Window::GetWindow();
		gameWindow->Initialize();

		Matrix4x4 ortho = Matrix4x4::Orthographic(0.0f, 16, 0.0f, 9, -1.0f, 1.0f);

		Shader myshader("..\\..\\PrimeEngine\\PrimeEngine\\Shaders\\standard.vert",
			"..\\..\\PrimeEngine\\PrimeEngine\\Shaders\\standard.frag");
		myshader.Enable();

		myshader.SetUniform("pr_matrix", ortho);

		Vector3 position(8, 4.5f, 0.15f);

		Renderable2D sprite1(Vector3(5, 4.5f, 0.1f), Vector2(1, 2), Vector4(1, 1, 0, 1), myshader);
		Renderable2D sprite2(Vector3(10, 4.5f, 0.2f), Vector2(2, 1), Vector4(1, 0, 0, 1), myshader);
		Renderable2D sprite3(position, Vector2(1, 1), Vector4(1, 0.5f, 0, 1), myshader);
		SimpleRenderer2D renderer;
		
		float speed = 0.01f;
		while (!gameWindow->Closed())
		{
			gameWindow->Clear();
			renderer.Submit(&sprite1);
			renderer.Submit(&sprite2);
			renderer.Submit(&sprite3);
			if (Input::KeyPressed('W'))
			{
				position += (Vector3::up * speed);
			}
			if (Input::KeyPressed('S'))
			{
				position += (Vector3::down * speed);
			}
			if (Input::KeyPressed('D'))
			{
				position += (Vector3::right * speed);
			}
			if (Input::KeyPressed('A'))
			{
				position += (Vector3::left * speed);
			}
			if (Input::KeyPressed(256)) //esc
			{
				gameWindow->Close();
			}
			sprite3.SetPosition(position);
			renderer.Flush();
			gameWindow->Update();
		}
		gameWindow->Destroy();
	}
	catch (const char* msg)
	{
		if (gameWindow)
		{
			gameWindow->Destroy();
		}
		std::cout << msg << std::endl;
		system("PAUSE");
	}
	return 0;
}