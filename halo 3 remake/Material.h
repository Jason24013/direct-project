#include "Texture.h"

class Material {

public:
    DirectX::XMFLOAT3 AmbientColor = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    DirectX::XMFLOAT3 DiffuseColor = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    DirectX::XMFLOAT3 SpecularColor = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

    // TODO: need to deallocate these
    Bind::Texture* pDiffuse = NULL; // base color of the material
    Bind::Texture* pSpecularExponent = NULL;
};
