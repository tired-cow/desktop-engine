#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include "World/WorldCamera.h"
#include "Windowing/EngineWindow.h"
#include "Events/Event.h"
#include "Loaders/AssetLoader.h"
#include "Renderer/Mesh.h"
#include "Renderer/GL/GLMeshShader.h"
#include "Renderer/GL/GLRenderer.h"
#include "Events/EventManager.h" 

#include <stb/stb_image.h>

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

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << glewGetErrorString(err);
		exit(1);
	}

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEPTH_TEST);
	glDebugMessageCallback(MessageCallback, 0);

	AssetLoader &loader = AssetLoader::GetInstance();
	Mesh chickMesh = loader.LoadMeshFromFile("assets/untitled.obj");
	
	WorldCamera camera;
	GLRenderer renderer;
	renderer.SetWorldCamera(&camera);

	GLMeshShader meshShader;
	meshShader.SetShader(GL_VERTEX_SHADER, "assets/vertex.glsl");
	meshShader.SetShader(GL_FRAGMENT_SHADER, "assets/fragment.glsl");

	WorldObject chick1;
	chick1.m_Mesh = chickMesh;
	chick1.m_Position.z = -15.f;
	chick1.m_Position.y = -3.5f;
	chick1.m_Rotation.x = 180.0f;

	WorldObject chick2;
	chick2.m_Mesh = chickMesh;
	chick2.m_Position.z = -15.f;
	chick2.m_Position.x = -15.f;
	chick2.m_Position.y = -3.5f;
	chick2.m_Rotation.x = 180.0f;


	renderer.AddToRenderList(chick1, meshShader);
	renderer.AddToRenderList(chick2, meshShader);
	//Textures
	stbi_set_flip_vertically_on_load(1);
	unsigned char* pixelBuff;
	int w, h, bpp;
	pixelBuff = stbi_load("assets/Block.png", &w, &h, &bpp, 4);

	unsigned int tId;
	glCreateTextures(GL_TEXTURE_2D, 1, &tId);
	
	// INTERNAL FORMAT IS RGBA8
	glTextureStorage2D(tId, 1, GL_RGBA8, w, h);
	
	// EXTERNAL FORMAT IS RGBA
	glTextureSubImage2D(tId, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, pixelBuff);
	
	unsigned int sampler;
	
	glCreateSamplers(1, &sampler);
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glBindSampler(0, sampler);

	stbi_image_free(pixelBuff);

	float inc = 1;
	while(1)
	{
		// // camera.m_Rotation.y += 1;

		// if (chick1.m_Position.y >= 10)
		// 	inc = -1;
		// else if (chick1.m_Position.y <= -10)
		// 	inc = 1;
		
		// // camera.m_Position.y += inc * .1;
		chick1.m_Rotation.y += 1;


		window.CheckNextEvent();
		glBindTexture(GL_TEXTURE_2D, tId);
		renderer.Render();
		window.SwapBuffers();
	}


	return 0;
}