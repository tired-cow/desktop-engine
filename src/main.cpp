#include <GL/glew.h>
#include <iostream>
#include "World/WorldCamera.h"
#include "Windowing/EngineWindow.h"
#include "Events/Event.h"
#include "Loaders/AssetLoader.h"
#include "Renderer/Mesh.h"
#include "Renderer/GL/GLRenderer.h"


#include "Math/Vector4.hpp"
#include "Math/Matrix4x4.hpp"

int main()
{
	EngineWindow window;
	window.Initialize(0, 0, 1920, 1080);

	GLenum err = glewInit();
	if (GLEW_OK != err)
		throw glewGetErrorString(err);
	
	// float vertexPos[] = {
	// 	-0.5, -0.5,
	// 	 0.5, -0.5,
	// 	 0.0,  0.5
	// };

	AssetLoader &loader = AssetLoader::GetInstance();
	Mesh *cube = loader.LoadVerticesFromFile("test.obj");

	WorldCamera camera;
	GLRenderer renderer;
	renderer.SetWorldCamera(&camera);
	renderer.SetShaderProgram();

	std::cout << cube->GetVertices().size() << " " << cube->GetIndices().size() << std::endl;

	// unsigned int vertexBuffer;
	// glCreateBuffers( 1, &vertexBuffer );
	// glNamedBufferStorage( vertexBuffer, sizeof(float) * 6, vertexPos, 0 );

	// unsigned int vertexArr;
	// glGenVertexArrays(1, &vertexArr);
	// glBindVertexArray(vertexArr);
	// glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	// glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);
	// glEnableVertexAttribArray(0);

	while(1)
	{
		Event event = window.GetNextEvent();
		//glDrawArrays(GL_TRIANGLES, 0, 3);


		renderer.Render(*cube);
		window.SwapBuffers();
	}

	return 0;
}