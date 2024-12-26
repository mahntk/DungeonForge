#include "../framework/Window.h"
#include <iostream>
#include "../framework/VertexArrayObject.h"
#include "../framework/Program.h"
#include "../framework/error.h"
#include "../framework/Timer.h"
#include "../framework/Texture2D.h"
#include "../framework/Model.h"
#include "Camera.h"
#include "Dungeon.h"


using namespace glm;

int main()
{
	try
	{
		Window wnd = Window(1280, 720, "Hardware Renderer");

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_DEPTH_TEST);

		bool cursorDisabled = true;
		wnd.changeMouseMode(cursorDisabled);

		// setup camera
		Camera cam(float(wnd.getWidth()) / float(wnd.getHeight()));
		wnd.setSizeChangeCallback([&cam](int width, int height)
		{
				cam.setAspect(float(width) / float(height));
		});
		bool camRotation = false;
		wnd.setMouseDownCallback([&camRotation](Window::Button, float, float)
		{
			camRotation = true;
		});
		wnd.setMouseUpCallback([&camRotation](Window::Button, float, float)
		{
			camRotation = false;
		});
		wnd.setMouseMoveCallback([&cam, &camRotation, &cursorDisabled](float, float, float dx, float dy)
		{
			if (!cursorDisabled && !camRotation) return;
			cam.rotate(dx, cursorDisabled ?  dy : -1.f * dy);
		});


		int gammaCorrect = 1;
		bool closeWindow = false;
		wnd.setKeyDownCallback([&](Window::Key key)
		{
			switch(key)
			{
			case Window::Key::G:
				gammaCorrect = !gammaCorrect;
				std::cerr << "gamma correction is " << (gammaCorrect ? "on" : "off") << '\n';
				break;
			case Window::Key::M:
				cursorDisabled = !cursorDisabled;
				wnd.changeMouseMode(cursorDisabled);
				break;
			case Window::Key::ESCAPE:
				closeWindow = true;
				break;
			default:;
			}
			cam.handleKeyInput(key, true);
		});

		wnd.setKeyUpCallback([&cam](Window::Key key) {
			cam.handleKeyInput(key, false);
		});


		// setup shader
		Program program;
		program
			.attach(Shader(GL_VERTEX_SHADER).loadFromFile("shader/phong.vert"))
			.attach(Shader(GL_FRAGMENT_SHADER).loadFromFile("shader/phong.frag"))
			.link();

		// uniforms
		Uniform<mat4> modelMatrix = program.getUniform("model", mat4(1.0),true);
		Uniform<mat4> viewMatrix = program.getUniform("view", mat4(1.0), true);
		Uniform<mat4> projectionMatrix = program.getUniform("projection", mat4(1.0), true);
		Uniform<vec3> camPosition = program.getUniform("cameraPosition", vec3(0.0f), true);
		Uniform<int> shaderMaterial = program.getUniform("materialId", 0, true);
		Uniform<int> useGammaCorrection = program.getUniform("gammaCorrect", 1, true);
		Uniform<float> timeUniform = program.getUniform("time", 0.f, true);
		Uniform<float> flameWeight = program.getUniform("flameWeight" , 0.f, true);

		//Uniform<glm::vec3> camPos        = program.getUniform("cameraPosition", glm::vec3(0), true);

		//Init Dungeon Scene
		Dungeon dungeonScene;

		Timer t,t2;
		t.start();
		t2.start();

		while(wnd.isOpen())
		{
			// time since the last frame in milliseconds
			glFinish();
			float dt = t.lap();

			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			cam.update(dt);

			// camera setup
			viewMatrix.set(cam.getView());
			projectionMatrix.set(cam.getProjection());
			camPosition.set(cam.getPosition());
			useGammaCorrection.set(gammaCorrect);
			flameWeight.set(dungeonScene.generateFlameWeight(25 /*Smooth Intervall*/));
			timeUniform.set(t2.current() * 0.01f);

			dungeonScene.draw(program, modelMatrix, shaderMaterial);

			wnd.setTitle("Hardware Renderer | " + std::to_string(t.current()) + " ms");

			glCheckError("main loop");

			wnd.swapBuffer();
			wnd.handleEvents();

			if (closeWindow)
				wnd.closeWindow();
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "ERR: " << e.what();
		// let the window stay open to read the exception
		while (true);
	}


	return 0;
}
