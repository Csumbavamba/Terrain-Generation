#include "Application.h"

#include "Camera.h"
#include "ShaderLoader.h"
#include "Utility.h"
#include "Input.h" 
#include "AudioSound.h"
#include "AudioEngine.h"
#include "Time.h"

// Scenes
#include "Scene.h"
#include "SceneManager.h"
#include "StartMenuScene.h"
#include "GameScene.h"


#pragma comment(lib, "Ws2_32.lib")

Application * Application::instance = NULL;

Application::Application()
{
	// Create Scenes
	startMenuScene = new StartMenuScene();
	startMenuScene->SetIsActiveScene(true);
	gameScene = new GameScene();

	
	// Push Scenes into the scene Holder
	scenes.push_back(startMenuScene);
	scenes.push_back(gameScene);


	backgroundMusic = new AudioSound("Audio/Moria-Music.mp3", LOOPING);

	SceneManager::AddScenes(scenes);
}


Application::~Application()
{
	// Scenes
	for (Scene * scene : scenes)
	{
		delete scene;
		scene = NULL;
	}

	scenes.clear();

	delete backgroundMusic;
	backgroundMusic = NULL;

	// Static Deletes
	AudioEngine::Shutdown();
	SceneManager::ShutDown();
	ShaderLoader::ShutDown();
	Input::ShutDown();
	Utility::ShutDown();
	Time::ShutDown();
}

Application * Application::GetInstance()
{
	if (instance == NULL)
	{
		instance = new Application();
	}
	return instance;;
}

void Application::PlayGame(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1024, 768);
	glutCreateWindow("Dwarf Game II");

	glClearColor(1.0, 0.0, 0.0, 1.0); // Clear Window


	glewInit(); // ADD FUNCTIONS AFTER THIS

	//// Enable Culling
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	//// Enable Depth for Rendering -- See if that causes error
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP); // TODO - see what does this do
	glDepthFunc(GL_LESS);

	// Blend between textures
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Enable Antialiasing
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glEnable(GL_MULTISAMPLE);

	GetInstance()->Initialise();

	glutDisplayFunc(Render);
	glutIdleFunc(Update);

	// Input stuff
	glutKeyboardFunc(Input::KeyboardDown);
	glutKeyboardUpFunc(Input::KeyboardUp);
	glutSpecialFunc(Input::SpecialKeyboardDown);
	glutSpecialUpFunc(Input::SpecialKeyboardUp);
	glutMouseFunc(Input::MouseClick);
	glutMotionFunc(Input::MouseActiveMove);
	glutPassiveMotionFunc(Input::MousePassiveMove);

	glutCloseFunc(Application::ShutDownGame);
	glutMainLoop();

	return;
}

void Application::Initialise()
{
	// Create Programs
	program = ShaderLoader::GetInstance()->CreateProgram("VertexShader.vs", "FragmentShader.fs");

	// Initialize the Scenes
	for (Scene * scene : scenes)
	{
		scene->Initialise();
	}

	backgroundMusic->PlaySound();
}

void Application::Render()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0); // clear red

	
	// Do rendering here - Render Current Scene
	SceneManager::GetActiveScene()->Render(GetInstance()->program);

	glBindVertexArray(0); // Unbind VAO
	glUseProgram(0);

	glutSwapBuffers();
}

void Application::Update()
{
	// Update Time
	Time::Update();

	// Update Screen size
	Utility::Update();

	// Update the Audio Engine
	AudioEngine::Update();


	// Update the Current Scene
	SceneManager::GetActiveScene()->Update(Time::GetDeltaTime());


	// Last function call
	glutPostRedisplay();
}

void Application::QuitGame()
{
	glutLeaveMainLoop();
}


void Application::ShutDownGame()
{
	delete instance;
	instance = NULL;
}

