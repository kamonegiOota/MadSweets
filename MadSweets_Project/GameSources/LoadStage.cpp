#include"LoadStage.h"
#include"Scene.h"

namespace basecross
{
	LoadStage::ResourceLoadData::ResourceLoadData(const std::wstring& resourceKey, const std::wstring& filename) :
		resourceKey(resourceKey),
		filename(filename)
	{

	}

	LoadStage::ModelResourceLoadData::ModelResourceLoadData(const std::wstring& resourceKey, const std::wstring& filename,
		const ModelType modelType, const std::wstring& modelDir) :
		ResourceLoadData(resourceKey, filename),
		modelType(modelType),
		modelDir(modelDir)
	{

	}

	std::mutex LoadStage::m_mtx;
	bool LoadStage::m_isLoadFinish = false;

	const std::vector<LoadStage::ResourceLoadData> LoadStage::m_texureResourceLoadDatas =
	{

	};

	const std::vector<LoadStage::ResourceLoadData> LoadStage::m_seResourceLoadDatas =
	{
		ResourceLoadData(L"HideSE", L"HideSE.wav"),
		ResourceLoadData(L"HandyWalkSE1", L"HandyWalkSE1.wav"),
		ResourceLoadData(L"HandyWalkSE2", L"HandyWalkSE2.wav"),
		ResourceLoadData(L"PlayerWalkSE1", L"PlayerWalkSE1.wav"),
		ResourceLoadData(L"PlayerWalkSE2", L"PlayerWalkSE2.wav")
	};

	const std::vector<LoadStage::ResourceLoadData> LoadStage::m_bgmResourceLoadDatas =
	{
		ResourceLoadData(L"TitleBGM1", L"TitleBGM1.wav"),
		ResourceLoadData(L"TitleBGM2", L"TitleBGM2.wav"),
		ResourceLoadData(L"TitleBGM3", L"TitleBGM3.wav")
	};

	const std::vector<LoadStage::ModelResourceLoadData> LoadStage::m_modelResourceLoadDatas =
	{

	};

	LoadStage::LoadStage(const std::wstring& nextStageKey) :
		m_nextStageKey(nextStageKey)
	{

	}

	void LoadStage::CreateViewLight()
	{
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void LoadStage::LoadResource()
	{
		std::lock_guard<std::mutex> lock(m_mtx);

		const auto& app = App::GetApp();

		std::wstring mediaDir;
		mediaDir = app->GetDataDirWString();

		// テクスチャフォルダ

		std::wstring dir = mediaDir + L"Textures\\";

		for (auto& textureLoadData : m_texureResourceLoadDatas)
		{
			app->RegisterTexture(textureLoadData.resourceKey, dir + textureLoadData.filename);
		}

		// SEフォルダ

		dir = mediaDir + L"SEs\\";

		for (auto& seLoadData : m_seResourceLoadDatas)
		{
			app->RegisterWav(seLoadData.resourceKey, dir + seLoadData.filename);
		}

		// BGMフォルダ

		dir = mediaDir + L"BGMs\\";

		for (auto& bgmLoadData : m_bgmResourceLoadDatas)
		{
			app->RegisterWav(bgmLoadData.resourceKey, dir + bgmLoadData.filename);
		}

		// モデルフォルダ

		dir = mediaDir + L"Models\\";

		for (auto& modelLoadData : m_modelResourceLoadDatas)
		{
			std::shared_ptr<MeshResource> modelMesh;

			std::wstring modelDir = dir + modelLoadData.modelDir;

			switch (modelLoadData.modelType)
			{
			case ModelType::Static:
				modelMesh = MeshResource::CreateStaticModelMesh(modelDir, modelLoadData.filename);
				break;

			case ModelType::Bone:
				modelMesh = MeshResource::CreateBoneModelMesh(modelDir, modelLoadData.filename);
				break;
			}

			app->RegisterResource(modelLoadData.resourceKey, modelMesh);
		}

		m_isLoadFinish = true;
	}

	void LoadStage::OnCreate()
	{
		CreateViewLight();

		m_stageBackColor = App::GetApp()->GetScene<Scene>()->GetClearColor();

		App::GetApp()->GetScene<Scene>()->SetClearColor(Col4(0, 0, 0, 1));

		std::thread loadThread(LoadResource);

		loadThread.detach();
	}

	void LoadStage::OnUpdate()
	{
		if (m_isLoadFinish)
		{
			App::GetApp()->GetScene<Scene>()->SetClearColor(m_stageBackColor);
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), m_nextStageKey);
		}
	}
}