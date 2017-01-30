#include <iostream>
#include <Core/Math.h>
#include <Graphics/Window.h>
#include <Input.h>
//#include <Utilities/File.h>
#include <Graphics/Shader.h>
#include <GL/glew.h>

using namespace PrimeEngine::Math;
using namespace PrimeEngine::Graphics;
using namespace PrimeEngine::Input;

int main()
{
	Window* gameWindow = NULL;
	try
	{
		//Window::SetWindow("Test Game", 1366, 768);
		//Window::SetWindow("Test Game", 800, 600);
		Window::SetWindow("Test Game Full");
		gameWindow = Window::GetWindow();
		gameWindow->Initialize();

		GLfloat vertices[] = {
			0,0,0,
			1,0,0,
			0,1,0
		}; 
		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		Matrix4x4 ortho = Matrix4x4::Orthographic(0.0f, 16, 0.0f, 9, -1.0f, 1.0f);

		Shader myshader("..\\..\\PrimeEngine\\PrimeEngine\\Shaders\\standart.vert",
			"..\\..\\PrimeEngine\\PrimeEngine\\Shaders\\standart.frag");
		myshader.Enable();
		glUniformMatrix4fv(glGetUniformLocation(myshader._shaderID, "pr_matrix"), 1, GL_FALSE, (float*)ortho.GetElements());
		Matrix4x4 position = Matrix4x4::Transform(Vector3(0, 0, 0));
		glUniformMatrix4fv(glGetUniformLocation(myshader._shaderID, "model_matrix"), 1, GL_FALSE, (float*)position.GetElements());

		float speed = 2.0f;
		while (!gameWindow->Closed())
		{
			gameWindow->Clear();
			if (Input::KeyPressed('W'))
			{
				position *= Matrix4x4::Transform(Vector3(0, 0.01f, 0) * speed);
				glUniformMatrix4fv(glGetUniformLocation(myshader._shaderID, "model_matrix"), 1, GL_FALSE, (float*)position.GetElements());
			}
			if (Input::KeyPressed('S'))
			{
				position *= Matrix4x4::Transform(Vector3(0, -0.01f, 0) * speed);
				glUniformMatrix4fv(glGetUniformLocation(myshader._shaderID, "model_matrix"), 1, GL_FALSE, (float*)position.GetElements());
			}
			if (Input::KeyPressed('D'))
			{
				position *= Matrix4x4::Transform(Vector3(0.01f, 0, 0) * speed);
				glUniformMatrix4fv(glGetUniformLocation(myshader._shaderID, "model_matrix"), 1, GL_FALSE, (float*)position.GetElements());
			}
			if (Input::KeyPressed('A'))
			{
				position *= Matrix4x4::Transform(Vector3(-0.01f, 0, 0) * speed);
				glUniformMatrix4fv(glGetUniformLocation(myshader._shaderID, "model_matrix"), 1, GL_FALSE, (float*)position.GetElements());
			}
			if (Input::KeyPressed(256))
			{
				gameWindow->Close();
			}
			glDrawArrays(GL_TRIANGLES, 0, 3);
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