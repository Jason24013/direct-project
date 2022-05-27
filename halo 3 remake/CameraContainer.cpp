#include "CameraContainer.h"
#include "Camera.h"
#include "Graphics.h"

void CameraContainer::Bind(Graphics& Gfx)
{
	Gfx.SetCamera(GetCamera().GetMatrix());
}

void CameraContainer::addCamera(std::shared_ptr<Camera> pCam)
{
	cameras.push_back(std::move(pCam));
}


Camera& CameraContainer::GetCamera()
{
	return *cameras[selected];
}


CameraContainer::~CameraContainer()
{

}