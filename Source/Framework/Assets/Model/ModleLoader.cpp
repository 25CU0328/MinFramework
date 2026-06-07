
#include "ModleLoader.h"


// コンストラクタ
Assets::Model::ModleLoader::ModleLoader()
{

}
// デストラクタ
Assets::Model::ModleLoader::~ModleLoader()
{

}

// 3Dモデルを読み込む
bool Assets::Model::ModleLoader::LoadObjModel(const std::string _strFilePath, ModelData& _outData)
{
	Assimp::Importer importer;
	const aiScene* pScene = importer.ReadFile(
		_strFilePath,
		aiProcess_Triangulate |	// 三角形じゃないフェスを三角形化
		aiProcess_FlipUVs |		// uvの向きが反転しないを
		aiProcess_GenNormals	// ノーマルのないモデるにノーマルを生成
	);

	if (pScene == nullptr)
	{
		printf("【ModleLoader】：Failed to Load File\n");
		return false;
	}

	// モデルの解析
	if (!pScene->HasMeshes())
	{
		printf("【ModleLoader】：Scene Does not Contain any Mesh\n");
		return false;
	}

	_outData = _parseSceneData(pScene);

	return true;
}


// シーンデータの解析
// 解析したデータはModelDataとして返す
ModelData Assets::Model::ModleLoader::_parseSceneData(const aiScene* _pScene)
{
	ModelData modelData;
	int meshNum = (int)_pScene->mNumMeshes;
	for (int i = 0; i < meshNum; ++i)
	{
		aiMesh* pMesh = _pScene->mMeshes[i];
		MeshData meshData;

		int meshNum = (int)pMesh->mNumVertices;
		// ヴァーテックスデータのコピー
		for (int j = 0; j < meshNum; ++j)
		{
			VertexData vertexData = {};
			// 頂点座標のコピー
			auto tempFloat3 = pMesh->mVertices[j];
			vertexData.position = XMFLOAT3(
				tempFloat3.x, 
				tempFloat3.y, 
				tempFloat3.z
			);

			if (pMesh->HasNormals())
			{
				// 法線のコピー
				tempFloat3 = pMesh->mNormals[j];
				vertexData.normal = XMFLOAT3(
					tempFloat3.x, 
					tempFloat3.y, 
					tempFloat3.z
				);
			}

			if (pMesh->HasTextureCoords(0))
			{
				vertexData.uv = XMFLOAT2(
					pMesh->mTextureCoords[0][j].x,
					pMesh->mTextureCoords[0][j].y
				);
			}

			meshData.vertexDatas.emplace_back(vertexData);
		}

		int faceNum = (int)pMesh->mNumFaces;
		// インデックスデータのコピー
		for (int faceIndex = 0; faceIndex < faceNum; ++faceIndex)
		{
			aiFace face =pMesh->mFaces[faceIndex];

			int indiceNum = (int)face.mNumIndices;
			for (int index = 0; index < indiceNum; ++index)
			{
				meshData.indices.push_back(face.mIndices[index]);
			}
		}


		// メッシュデータを保存する
		modelData.meshDatas.emplace_back(meshData);
	}

	/*
	// Debug用
	for (MeshData meshData : modelData.meshDatas) 
	{ 
		for (VertexData vertexData : meshData.vertexDatas) 
		{ 
			std::cout << "Position(" << vertexData.position.x << ", " << vertexData.position.y << ", " << vertexData.position.z << ")" << std::endl; 
			std::cout << "Normal(" << vertexData.normal.x << ", " << vertexData.normal.y << ", " << vertexData.normal.z << ")" << std::endl; 
			std::cout << "UV(" << vertexData.uv.x << ", " << vertexData.uv.y << ")" << std::endl; 
		} 
	}*/
	return modelData;
}