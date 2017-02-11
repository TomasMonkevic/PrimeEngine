#include <iostream>
#include <Core\Math.h>
#include <Graphics\Window.h>
#include <Input.h>
#include <Utilities\Time.h>
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
		gameWindow->SetColor(Vector4(0.3f, 0.6f, 1.0f, 1.0f));
		gameWindow->Initialize();

		Matrix4x4 ortho = Matrix4x4::Orthographic(0.0f, 16, 0.0f, 9, -1.0f, 1.0f);

		Shader myshader("..\\..\\PrimeEngine\\PrimeEngine\\Shaders\\standard.vert",
			"..\\..\\PrimeEngine\\PrimeEngine\\Shaders\\standard.frag");
		myshader.Enable();

		myshader.SetUniform("pr_matrix", ortho);
		myshader.SetUniform("lightPosition", Vector2(8, 4.5f));
		Vector3 position(8, 4.5f, 0.15f);
		Vector3 scale = Vector3::one;

		Renderable2D backGround(Vector3(5, 4.5f, 0.1f), Vector2(100, 100), Vector4(1, 0.5f, 0, 1), myshader);
		Renderable2D sprite1(Vector3(5, 4.5f, 0.1f), Vector2(1, 2), Vector4(1, 1, 0, 1), myshader);
		Renderable2D sprite2(Vector3(10, 4.5f, 0.2f), Vector2(2, 1), Vector4(1, 0, 0, 1), myshader);
		Renderable2D sprite4(Vector3(1, 1, 0.2f), Vector2(1, 1), Vector4(0, 1, 0, 1), myshader);
		Renderable2D sprite3(position, Vector2(1, 1), Vector4(0.5f, 0.5f, 0.2f, 1), myshader);
		SimpleRenderer2D renderer;
		
		float speed = 0.1f, scaleSpeed = 0.005f;;
		PrimeEngine::Time timer;
		unsigned int fpsCounter = 0;
		while (!gameWindow->Closed())
		{
			gameWindow->Clear();
			renderer.Submit(&backGround);
			renderer.Submit(&sprite1);
			renderer.Submit(&sprite2);
			renderer.Submit(&sprite3);
			renderer.Submit(&sprite4);
			//myshader.SetUniform("lightPosition", Input::GetMousePosition());
			if (Input::KeyPressed('W'))
			{
				position += (Vector3::up * speed);
				scale += Vector3(1, 1, 0) * scaleSpeed;
			}
			else if (Input::KeyPressed('S'))
			{
				position += (Vector3::down * speed);
				scale += Vector3(1, 1, 0) * scaleSpeed;
			}
			if (Input::KeyPressed('D'))
			{
				position += (Vector3::right * speed);
				scale += Vector3(1, 1, 0) * scaleSpeed;
			}
			else if (Input::KeyPressed('A'))
			{
				position += (Vector3::left * speed);
				scale += Vector3(1, 1, 0) * scaleSpeed;
			}
			if (Input::KeyPressed(256)) //esc
			{
				gameWindow->Close();
			}
			//std::cout << Input::GetMousePosition() << std::endl;
			sprite2.Rotate(0.1f, Vector3::forward);
			sprite3.Rotate(0.1f, Vector3::left);
			sprite1.Rotate(0.1f, Vector3::up);
			sprite3.SetScale(scale);
			sprite3.SetPosition(position);
			renderer.Flush();
			gameWindow->Update();
			//printf("%f ms\n",timer.Elapsed() * 1000.0f);
			fpsCounter++;
			if (timer.Elapsed() >= 1.0f)
			{
				printf("%u fps\n", fpsCounter);
				fpsCounter = 0;
				timer.Reset();
			}
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