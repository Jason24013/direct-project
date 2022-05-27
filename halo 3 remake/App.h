#pragma once
#include "Window.h"
#include "ChiliTimer.h"
#include "ImguiManager.h"
#include "Camera.h"
#include "PointLight.h"
#include "TestPlane.h"
#include "Model.h"
#include <set>
#include "Animation.h"

class App
{
public:
	App(const std::string& commmandLine = "");
	// master frame / message loop
	int Go();
	~App();
private:
	void DoFrame();
	void ShowImguiDemoWindow();
private:
	std::string commandLine;
	bool showDemoWindow = false;
	ImguiManager imgui;
	Window wnd;
	ChiliTimer timer;
	float speed_factor = 1.0f;
	Camera cam;
	Animation::Bone d;
	PointLight light;
	Model gobber{ wnd.Gfx(), d, "Models\\masterchief.gltf",6.0f };
	//Model wall{ wnd.Gfx(),"Models\\brick_wall\\brick_wall.obj",6.0f };
	//TestPlane tp{ wnd.Gfx(),6.0 };
	//Model nano{ wnd.Gfx(),"Models\\nano_textured\\nanosuit.obj",2.0f };
	Model Sponza{ wnd.Gfx(), d, "Models\\sponza\\sponza.obj",1.0f / 20.0f };
};