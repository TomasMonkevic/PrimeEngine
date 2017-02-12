#include <iostream>
#include <Core\Math.h>
#include <Graphics\Window.h>
#include <Input.h>
#include <Utilities\Time.h>
#include <Graphics\Shader.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <Graphics\Camera.h>

#include <Graphics\Renderable2D.h>
#include <Graphics\SimpleRenderer2D.h>

using namespace PrimeEngine::Math;
using namespace PrimeEngine::Graphics;
using namespace PrimeEngine::Input;

#define MOVE_CAMERA 1

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

		//Matrix4x4 pr = Matrix4x4::Orthographic(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f);
		Matrix4x4 pr = Matrix4x4::Perspective(45.0f, 16.0f / 9.0f, -1.5f, 1.5f);


		Shader myshader("..\\..\\PrimeEngine\\PrimeEngine\\Shaders\\standard.vert",
			"..\\..\\PrimeEngine\\PrimeEngine\\Shaders\\standard.frag");
		myshader.Enable();

		Camera mainCamera(myshader, pr);
		Vector3 cameraPosition(Vector3(9, 4.5f, -0.9f));
		mainCamera.SetPosition(cameraPosition);
		//myshader.SetUniform("pr_matrix", ortho);
		myshader.SetUniform("lightPosition", Vector2(8, 4.5f));
		Vector3 position(4, 4.5f, 0.15f);
		Vector3 scale = Vector3::one;

		Renderable2D backGround(Vector3(5, 4.5f, 0.1f), Vector2(100, 100), Vector4(1, 0.5f, 0, 1), myshader);
		Renderable2D sprite1(Vector3(5, 4.5f, 0.1f), Vector2(1, 2), Vector4(1, 1, 0, 1), myshader);
		Renderable2D sprite2(Vector3(10, 4.5f, 0.2f), Vector2(2, 1), Vector4(1, 0, 0, 1), myshader);
		Renderable2D sprite4(Vector3(1, 1, 0.2f), Vector2(1, 1), Vector4(0, 1, 0, 1), myshader);
		Renderable2D sprite3(position, Vector2(1, 1), Vector4(0.5f, 0.5f, 0.2f, 1), myshader);
		SimpleRenderer2D renderer;
		
		float speed = 0.1f, scaleSpeed = 0.005f, cameraSpeed = 0.05f;
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
#ifdef MOVE_CAMERA
				cameraPosition += Vector3::forward * cameraSpeed;
#else // MOVE_CAMERA
				position += (Vector3::up * speed);
				scale += Vector3(1, 1, 0) * scaleSpeed;
#endif
			}
			else if (Input::KeyPressed('S'))
			{
#ifdef MOVE_CAMERA
				cameraPosition += Vector3::back * cameraSpeed;
#else // MOVE_CAMERA
				position += (Vector3::down * speed);
				scale += Vector3(1, 1, 0) * scaleSpeed;
#endif
			}
			if (Input::KeyPressed('D'))
			{
#ifdef MOVE_CAMERA
				cameraPosition += Vector3::Cross(Vector3::back, Vector3::up).Normalized() * cameraSpeed;
#else // MOVE_CAMERA
				position += (Vector3::right * speed);
				scale += Vector3(1, 1, 0) * scaleSpeed;
#endif
			}
			else if (Input::KeyPressed('A'))
			{
#ifdef MOVE_CAMERA
				cameraPosition -= Vector3::Cross(Vector3::back, Vector3::up).Normalized() * cameraSpeed;
#else // MOVE_CAMERA
				position += (Vector3::left * speed);
				scale += Vector3(1, 1, 0) * scaleSpeed;
#endif
			}
			if (Input::KeyPressed('Q'))
			{
#ifdef MOVE_CAMERA
				cameraPosition += Vector3::up * cameraSpeed;
#endif // MOVE_CAMERA
			}
			else if (Input::KeyPressed('E'))
			{
#ifdef MOVE_CAMERA
				cameraPosition += Vector3::down * cameraSpeed;
#endif // MOVE_CAMERA
			}
			if (Input::KeyPressed(256)) //esc
			{
				gameWindow->Close();
			}
			mainCamera.SetPosition(cameraPosition);
			//std::cout << Input::GetMousePosition() << std::endl;
			//backGround.Rotate(0.1f, Vector3::left);
			sprite2.Rotate(0.1f, Vector3::forward);
			sprite3.Rotate(0.1f, Vector3::left);
			sprite1.Rotate(0.1f, Vector3::up);
			sprite3.SetScale(scale);
			sprite3.SetPosition(position);
			renderer.Flush();
			mainCamera.LookAt(mainCamera.GetPosition() + Vector3::back);
			mainCamera.Render();
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