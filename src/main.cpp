#include <GL/glew.h>
#include <iostream>
#include "World/WorldCamera.h"
#include "Windowing/EngineWindow.h"
#include "Events/Event.h"
#include "Loaders/AssetLoader.h"
#include "Renderer/Mesh.h"
#include "Renderer/GL/GLRenderer.h"
#include "Events/EventManager.h" 

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>


#include "TestListener.hpp"

void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}



int main()
{
	EngineWindow window;
	window.Initialize(0, 0, 1920, 1080);

	EventManager &eventManager = EventManager::GetInstance();
	TestListener listener;

	eventManager.SubscribeToEvent("MouseMoved", &listener);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << glewGetErrorString(err);
		exit(1);
	}

	AssetLoader &loader = AssetLoader::GetInstance();
	Mesh cube = loader.LoadVerticesFromFile("assets/chickenV2.obj");
	
	WorldCamera camera;

	GLRenderer renderer;
	renderer.SetWorldCamera(&camera);
	renderer.AddToRenderList(cube);

	std::string vShaderSrc = loader.LoadShaderFromFile("assets/vertex.glsl");
	GLShader vertexShader(GL_VERTEX_SHADER);
	vertexShader.SourceShader(vShaderSrc);
	vertexShader.Compile();

	std::string fShaderSrc = loader.LoadShaderFromFile("assets/fragment.glsl");
	GLShader fragmentShader(GL_FRAGMENT_SHADER);
	fragmentShader.SourceShader(fShaderSrc);
	fragmentShader.Compile();

	GLShaderProgram m_ShaderProgram;

	m_ShaderProgram.SetShader(vertexShader);
	m_ShaderProgram.SetShader(fragmentShader);
	m_ShaderProgram.Use();

	unsigned int projMatId = m_ShaderProgram.GetUniformLocation("projection");
	glm::mat4 projMat = glm::mat4(1.0f);
	projMat = glm::perspective(camera.m_FOV, camera.m_AspectRatio, camera.m_NearPlane, camera.m_FarPlane);
	glUniformMatrix4fv(projMatId, 1, GL_FALSE, glm::value_ptr(projMat));

	unsigned int modelMatId = m_ShaderProgram.GetUniformLocation("model");
	glm::mat4 modelMat = glm::mat4(1.0f);
	modelMat = glm::translate(modelMat, glm::vec3(0, 5, -10.5f));
	modelMat = glm::rotate(modelMat, 3.14159265f, glm::vec3(1, 0, 0));
	glUniformMatrix4fv(modelMatId, 1, GL_FALSE, glm::value_ptr(modelMat));
	

	// Event event = window.GetNextEvent();
	// event = window.GetNextEvent();
	// event = window.GetNextEvent();

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEPTH_TEST);
	glDebugMessageCallback(MessageCallback, 0);


	while(1)
	{
		window.CheckNextEvent();
		modelMat = glm::rotate(modelMat, 1 * 3.14159265f/180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelMatId, 1, GL_FALSE, glm::value_ptr(modelMat));
		renderer.Render();
		window.SwapBuffers();
	}


	return 0;
}