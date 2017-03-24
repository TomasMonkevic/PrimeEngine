#include <iostream>
#include <Utilities\Time.h>
#include <Core\Math.h>
#include <Graphics\Window.h>
#include <Input.h>
#include <Graphics\Shader.h>
#include <Graphics\Camera.h>
#include <Graphics\Renderable2D.h>
#include <Graphics\SimpleRenderer2D.h>
#include <Graphics\SimpleSprite.h>
#include <Graphics\BatchRenderer2D.h>
#include <Graphics\Sprite.h>
#include <PrimeException.h>
#include <Graphics\Layers\Layer.h>

using namespace PrimeEngine::Math;
using namespace PrimeEngine::Graphics;
using namespace PrimeEngine::Input;

#define MOVE_CAMERA false
#define BATCH_RENDERER true;


class FakeUILayer : public Layer
{
public:
	FakeUILayer(Shader* shader) :
		Layer(new BatchRenderer2D(), new Camera(shader, Matrix4x4::Orthographic(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f)))
	{
		camera->SetPosition(Vector3::zero);
		camera->LookAt(camera->GetPosition() + Vector3::back);
	}
};

class GameLayer : public Layer
{
public:
	GameLayer(Camera* camera) :
		Layer(new BatchRenderer2D(), camera)
	{

	}
};

int main()
{
	Window* gameWindow = NULL;
	try
	{
		//Window::SetWindow("Test Game", 1366, 768);
		Window::SetWindow("Test Game", 800, 600);
		//Window::SetWindow("Test Game Full");
		gameWindow = Window::GetWindow();
		gameWindow->SetColor(Vector4(0.3f, 0.6f, 1.0f, 1.0f));
		gameWindow->Initialize();

		Matrix4x4 pr = Matrix4x4::Orthographic(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f);
		//Matrix4x4 pr = Matrix4x4::Perspective(45.0f, 16.0f / 9.0f, -1.5f, 1.5f);


		Shader* myshader = new Shader("..\\..\\PrimeEngine\\PrimeEngine\\Shaders\\standard.vert",
			"..\\..\\PrimeEngine\\PrimeEngine\\Shaders\\standard.frag");
		Shader* myshader2 = new Shader("..\\..\\PrimeEngine\\PrimeEngine\\Shaders\\standard.vert",
			"..\\..\\PrimeEngine\\PrimeEngine\\Shaders\\standard.frag");
		//myshader->Enable();
		//myshader2->Enable();

		Camera* mainCamera = new Camera(myshader, pr);
		//Vector3 cameraPosition(Vector3(9, 4.5f, -6.0f)); //projection
		Vector3 cameraPosition(Vector3(0, 0, 0.0f)); //ortho
		mainCamera->SetPosition(cameraPosition);
		//myshader.SetUniform("pr_matrix", ortho);
		//myshader2->SetUniform("lightPosition", Vector2(0, 0));
		Vector3 position(0, 0.0f, 0.0f);
		Vector3 scale = Vector3::one;

#if BATCH_RENDERER
		Sprite backGround(Vector3(5, 4.5f, 0.1f), Vector2(100, 100), Vector4(1, 0.5f, 0, 1));
		Sprite sprite1(Vector3(5, 4.5f, 0.1f), Vector2(1, 2), Vector4(1, 1, 0, 1));
		Sprite sprite2(Vector3(1, 1, 0), Vector2(2, 1), Vector4(1, 0, 0, 1));
		Sprite sprite4(Vector3(0, 0, 0.2f), Vector2(1, 1), Vector4(0, 1, 0, 1));
		Sprite sprite3(Vector3(2, 2, 0.0f), Vector2(1, 1), Vector4(0.5f, 0.5f, 0.2f, 1));
		BatchRenderer2D renderer;
#else
		SimpleSprite backGround(Vector3(5, 4.5f, 0.1f), Vector2(100, 100), Vector4(1, 0.5f, 0, 1),myshader);
		SimpleSprite sprite1(Vector3(5, 4.5f, 0.1f), Vector2(1, 2), Vector4(1, 1, 0, 1), myshader);
		SimpleSprite sprite2(Vector3(10, 4.5f, 0.2f), Vector2(2, 1), Vector4(1, 0, 0, 1), myshader);
		SimpleSprite sprite4(Vector3(1, 1, 0.2f), Vector2(1, 1), Vector4(0, 1, 0, 1), myshader);
		SimpleSprite sprite3(position, Vector2(1, 1), Vector4(0.5f, 0.5f, 0.2f, 1), myshader);
		SimpleRenderer2D renderer;
#endif
		GameLayer gameLayer(mainCamera);
		gameLayer.Submit(&backGround);
		gameLayer.Submit(&sprite1);
		gameLayer.Submit(&sprite2);
		gameLayer.Submit(&sprite3);
		gameLayer.Submit(&sprite4);
		Sprite uiEl(Vector3(0, 0, 0), Vector2(1, 1), Vector4(0.5f, 0.5f, 0.2f, 1));
		FakeUILayer ui(myshader2); //somethings's up with the shader
		ui.Submit(&uiEl);
		float speed = 0.1f, scaleSpeed = 0.005f, cameraSpeed = 0.05f;
		PrimeEngine::Time timer;
		unsigned int fpsCounter = 0;
		while (!gameWindow->Closed())
		{
			gameWindow->Clear();
//#if BATCH_RENDERER
//			renderer.Begin();
//#endif
//			renderer.Submit(&backGround);
//			renderer.Submit(&sprite1);
//			renderer.Submit(&sprite2);
//			renderer.Submit(&sprite3);
//			renderer.Submit(&sprite4);
//#if BATCH_RENDERER
//			renderer.End();
//#endif
			Vector3 opa = mainCamera->ScreenToWorldPoint(Input::GetMousePosition());
			myshader->SetUniform("lightPosition", Vector2(opa.x, opa.y));
			if (Input::KeyPressed('W'))
			{
#if MOVE_CAMERA
				cameraPosition += Vector3::forward * cameraSpeed;
#else // MOVE_CAMERA
				position += (Vector3::up * speed);
				scale += Vector3(1, 1, 0) * scaleSpeed;
#endif
			}
			else if (Input::KeyPressed('S'))
			{
#if MOVE_CAMERA
				cameraPosition += Vector3::back * cameraSpeed;
#else // MOVE_CAMERA
				position += (Vector3::down * speed);
				scale += Vector3(1, 1, 0) * scaleSpeed;
#endif
			}
			if (Input::KeyPressed('D'))
			{
#if MOVE_CAMERA
				cameraPosition += Vector3::Cross(Vector3::back, Vector3::up).Normalized() * cameraSpeed;
#else // MOVE_CAMERA
				position += (Vector3::right * speed);
				scale += Vector3(1, 1, 0) * scaleSpeed;
#endif
			}
			else if (Input::KeyPressed('A'))
			{
#if MOVE_CAMERA
				cameraPosition -= Vector3::Cross(Vector3::back, Vector3::up).Normalized() * cameraSpeed;
#else // MOVE_CAMERA
				position += (Vector3::left * speed);
				scale += Vector3(1, 1, 0) * scaleSpeed;
#endif
			}
			if (Input::KeyPressed('Q'))
			{
#if MOVE_CAMERA
				cameraPosition += Vector3::up * cameraSpeed;
#endif // MOVE_CAMERA
			}
			else if (Input::KeyPressed('E'))
			{
#if MOVE_CAMERA
				cameraPosition += Vector3::down * cameraSpeed;
#endif // MOVE_CAMERA
			}
			if (Input::KeyPressed(256)) //esc
			{
				gameWindow->Close();
			}
			mainCamera->SetPosition(cameraPosition);
			//std::cout << Input::GetMousePosition() << std::endl;
			//backGround.Rotate(0.1f, Vector3::left);
#if BATCH_RENDERER
			sprite2.Rotate(0.1f, Vector3::forward);
			sprite3.Rotate(0.1f, Vector3::left);
			sprite1.Rotate(0.1f, Vector3::up);
			//sprite4.SetScale(scale);
			sprite4.SetPosition(position);
			std::cout << sprite4.GetPosition() << std::endl;
#endif
			//renderer.Flush();
			mainCamera->LookAt(mainCamera->GetPosition() + Vector3::back);
			//mainCamera->Render();
			gameLayer.Render();
			ui.Render();
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
	catch (const PrimeEngine::PrimeException& ex)
	{
		if (gameWindow)
		{
			gameWindow->Destroy();
		}
		std::cout << ex.what() << " " << ex.GetErrorCode() << std::endl;
		system("PAUSE");
	}
	return 0;
}