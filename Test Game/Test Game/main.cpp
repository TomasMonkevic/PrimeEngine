#include <iostream>
#include <Core/Math.h>
#include <Graphics/Window.h>
#include <Input.h>
//#include <Utilities/File.h>
#include <Graphics/Shader.h>
#include <GL/glew.h>
//#include <GLFW/glfw3.h>

using namespace PrimeEngine::Math;
using namespace PrimeEngine::Graphics;
using namespace PrimeEngine::Input;

int main()
{
	try
	{
		//Window::SetWindow("Test Game", 1366, 768);
		Window::SetWindow("Test Game", 800, 600);
		//Window::SetWindow("Test Game Full");
		Window* gameWindow = Window::GetWindow();
		gameWindow->Initialize();

		GLfloat vertices[] = {
			0,0,0,
			25,0,0,
			0,25,0
		}; 
		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		Matrix4x4 ortho = Matrix4x4::Orthographic(0.0f, 100, 0.0f, 100, -1.0f, 1.0f);
		std::cout << ortho << std::endl;

		Shader myshader("..\\..\\PrimeEngine\\PrimeEngine\\Shaders\\standart.vert",
			"..\\..\\PrimeEngine\\PrimeEngine\\Shaders\\standart.frag");
		myshader.Enable();
		glUniformMatrix4fv(glGetUniformLocation(myshader._shaderID, "pr_matrix"), 1, GL_FALSE, (float*)ortho._matrix);
		
		Matrix4x4 position = Matrix4x4::Transform(Vector3(0, 0, 0));
		//position *= Matrix4x4::Transform(Vector3(25, 25, 0));

		glUniformMatrix4fv(glGetUniformLocation(myshader._shaderID, "model_matrix"), 1, GL_FALSE, (float*)position._matrix);

		//glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

		//glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO

		

		
		while (!gameWindow->Closed())
		{
			gameWindow->Clear();
			if (Input::KeyPressed('W'))
			{
				std::cout << "key pressed" << std::endl;
			}
			glDrawArrays(GL_TRIANGLES, 0, 3);
			position *= Matrix4x4::Transform(Vector3(0.1f, 0.1f, 0));
			glUniformMatrix4fv(glGetUniformLocation(myshader._shaderID, "model_matrix"), 1, GL_FALSE, (float*)position._matrix);

			gameWindow->Update();
		}
		gameWindow->Destroy();
	}
	catch (const char* msg)
	{
		std::cout << msg << std::endl;
		system("PAUSE");
	}
	return 0;
}