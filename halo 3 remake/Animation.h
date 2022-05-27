#pragma once
#include <iostream>
#include <vector>
#include <SimpleMath.h>
#include <DirectXMath.h>
#include "Model.h"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> 
#include <cmath>

#include <math.h>
#include <map>
#include <vector>
#include "utils.h"
#include "VertexBuffer.h"
#include <dwrite.h>

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class Animation : protected Bind::VertexBuffer, private Graphics
{
	friend class Mesh;
	friend class App;
	friend class Model;


private:

#define MAX_NUM_BONES_PER_VERTEX 4


	struct Vertex {


		Vector3 position;
		Vector3 normal;
		Vector2 uv;
		Vector4 boneIds = Vector4(0.0);
		Vector4 boneWeights = Vector4(0.0f);
	};
	
	





	struct Bone {
		int id = 0;
		std::string name = "";
		XMMATRIX offset;

		XMFLOAT4 projectionMatrix;
		std::vector<Bone> Children = {};
	};

	struct BoneTransformTrack {
		std::vector<float> positionTimestamps = {};
		std::vector<float> rotationTimestamps = {};
		std::vector<float> scaleTimestamps = {};

		std::vector<Vector3> positions = {};
		std::vector<Quaternion> rotations = {};
		std::vector<Vector3> scales = {};


	};

	struct ANIMATION {
		float duration = 0.0f;
		float ticksPerSecound = 1.0f;
		std::unordered_map<std::string, BoneTransformTrack> boneTranforms = {};
	};
public:
	Animation();
	bool readSkeleton(Bone& boneOutput, aiNode* node, std::unordered_map<std::string, std::pair<int, DirectX::XMMATRIX>>& boneInfoTable);
	void GetBoneTransforms(float TimeInSeconds, vector<XMMATRIX>& Transforms);

private:

	struct VertexBoneData
	{
		UINT BoneIDs[MAX_NUM_BONES_PER_VERTEX] = { 0 };
		float Weights[MAX_NUM_BONES_PER_VERTEX] = { 0.0f };

		VertexBoneData()
		{
		}

		void AddBoneData(UINT BoneID, float Weight)
		{
			for (UINT i = 0; i < ARRAY_SIZE_IN_ELEMENTS(BoneIDs); i++) {
				if (Weights[i] == 0.0) {
					BoneIDs[i] = BoneID;
					Weights[i] = Weight;
					//printf("Adding bone %d weight %f at index %i\n", BoneID, Weight, i);
					return;
				}
			}

			// should never get here - more bones than we have space for
			assert(0);
		}
	};
	void LoadMeshBones(UINT MeshIndex, const aiMesh* paiMesh);
	void LoadSingleBone(UINT MeshIndex, const aiBone* pBone);
	int GetBoneId(const aiBone* pBone);

	static std::unique_ptr<Mesh> PopulateBuffers(Graphics& gfx, const aiMesh& mesh, const aiMaterial* const* pMaterials, const std::filesystem::path& path, float scale);

	std::vector<std::unique_ptr<Mesh>> meshPtrs;

	enum BUFFER_TYPE {
		INDEX_BUFFER = 0,
		POS_VB = 1,
		TEXCOORD_VB = 2,
		NORMAL_VB = 3,
		BONE_VB = 4,
		NUM_BUFFERS = 5
	};
	UINT m_Buffers[NUM_BUFFERS] = { D3D11_BIND_VERTEX_BUFFER };


#define INVALID_MATERIAL 0xFFFFFFFF

	struct BasicMeshEntry {
		BasicMeshEntry()
		{
			NumIndices = 0;
			BaseVertex = 0;
			BaseIndex = 0;
			MaterialIndex = INVALID_MATERIAL;
		}

		unsigned int NumIndices;
		unsigned int BaseVertex;
		unsigned int BaseIndex;
		unsigned int MaterialIndex;
	};

	const aiScene* pScene = NULL;
	std::vector<BasicMeshEntry> m_Meshes;
	std::vector<Material> m_Materials;

	void Clear(Graphics& gfx);
	std::vector<Vertex> vertices = {};
	std::vector<UINT> indices = {};
	UINT boneCount = 0;
	ANIMATION animation;
	UINT vao = 0;
	Bone skeleton;
	UINT diffuseTexture;
	bool LoadMesh(Graphics& gfx, Drawable& ds, std::vector<std::shared_ptr<Bind::Bindable>> bindPtrs, const string& FileName, Model& x, const std::filesystem::path& path, float scale);
	bool InitFromScene(Graphics& gfx, Drawable& ds, std::vector<std::shared_ptr<Bind::Bindable>> bindPtrs, const aiScene* pScene, const std::string& FileName);
	void CountVerticesAndIndices(const aiScene* pScene, unsigned int& NumVertices, unsigned int& NumIndices);
	void ReserveSpace(unsigned int NumVertices, unsigned int NumIndices);
	void InitAllMeshes(const aiScene* pScene);
	void InitSingleMesh(UINT MeshIndex, const aiMesh* paiMesh);
	void ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const XMMATRIX& ParentTransform);
const aiNodeAnim* FindNodeAnim(const aiAnimation* _animation, const std::string& _nodeName); private:
	Assimp::Importer import;

	vector<XMVECTOR> m_Positions;
	vector<XMVECTOR> m_Normals;
	vector<XMVECTOR> m_TexCoords;
	vector<unsigned int> m_Indices;
	vector<VertexBoneData> m_Bones;
	Vector3 Vector3f(FLOAT x, FLOAT y, FLOAT z);
	Vector3 Vector2f(FLOAT x, FLOAT y);

	map<string, UINT> m_BoneNameToIndexMap;

	struct BoneInfo
	{
		XMMATRIX OffsetMatrix;
		XMFLOAT4X4 pMatrix4f;
		XMMATRIX FinalTransformation = XMMatrixIdentity();
		
		

		BoneInfo(const XMMATRIX& Offset)
		{
			OffsetMatrix = Offset;
			
			;
		}
	};
	vector<BoneInfo> m_BoneInfo;
	XMMATRIX m_GlobalInverseTransform;
	unsigned int FindScaling(float _animationTime, const aiNodeAnim* _nodeAnim);
	unsigned int FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
	unsigned int FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);
	void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
	void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
	void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);



};