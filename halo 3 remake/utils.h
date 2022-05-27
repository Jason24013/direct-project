#pragma once
#include <DirectXMath.h>
#include <SimpleMath.h>
#include <assimp/scene.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

inline Vector3 assimpToGlmVec3(aiVector3D vec) {
	return Vector3(vec.x, vec.y, vec.z);
}
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define ZERO_MEM(a) memset(a, 0, sizeof(a))

inline XMMATRIX aiMatrixToXMMatrix(aiMatrix4x4 mat) {
	
	XMFLOAT4X4 pMatrix2;
	XMMATRIX matrix3{};
	XMStoreFloat4x4(&pMatrix2, matrix3);
	matrix3 = XMMatrixScaling(0.5f, 0.5f, 1.0f);
	matrix3 = XMMatrixTranslation(0.0f, -0.5f, 0.0f);
	matrix3 = XMMatrixIdentity();
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			matrix3.r[x] .m128_f32[y] = mat[y][x];
		}
	}
	return matrix3;
}



inline Quaternion assimpToGlmQuat(aiQuaternion quat) {
	Quaternion q;
	q.x = quat.x;
	q.y = quat.y;
	q.z = quat.z;
	q.w = quat.w;

	return q;
}