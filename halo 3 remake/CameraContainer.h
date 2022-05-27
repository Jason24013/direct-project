#pragma once
#include <vector>
#include <memory>

class Camera;
class Graphics;

class CameraContainer
{
public:
	void Bind(Graphics& Gfx);
	void addCamera(std::shared_ptr<Camera> pCam);
	Camera& GetCamera();
	~CameraContainer();
private:
	std::vector<std::shared_ptr<Camera>> cameras;
	int selected = 0;
};
