#include"LoadStage.h"
#include"Scene.h"
#include"SoundHelper.h"
#include"GameSaveManager.h"

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
		ResourceLoadData(L"MenuOption_TX", L"MenuOption.png"),
		ResourceLoadData(L"MenuPressAToStart_TX", L"MenuPressAToStart.png"),
		ResourceLoadData(L"MenuBack_TX", L"MenuBack.png"),
		ResourceLoadData(L"MenuSoundManage_TX", L"MenuSoundManage.png"),
		ResourceLoadData(L"OptionBGMVolume_TX", L"OptionBGMVolume.png"),
		ResourceLoadData(L"OptionSEVolume_TX", L"OptionSEVolume.png"),
		ResourceLoadData(L"OptionGauge_TX", L"OptionGauge.png"),
		ResourceLoadData(L"Beans_TX", L"Beans.png"),
		ResourceLoadData(L"SweetCokie_Tx", L"Sweet_Cokie.png"),
		ResourceLoadData(L"SweetEye_Tx", L"Sweet_Eye.png"),
		ResourceLoadData(L"SweetHand_Tx", L"Sweet_Hand.png"),
		ResourceLoadData(L"TitleBack_Tx", L"TitleBack.png"),
		ResourceLoadData(L"TitleStartPress_Tx", L"TitleStartPress.png"),

		ResourceLoadData(L"WeightGaugeBackground", L"WeightGaugeBackGround.png"),
		ResourceLoadData(L"WeightGaugeColor"     , L"WeightGaugeColor.png"),
		ResourceLoadData(L"WallCake_Tx"          , L"Tx_Cake.png"),
		ResourceLoadData(L"WallCake2_Tx"         , L"Tx_Cake2.png"),
		ResourceLoadData(L"WallCake3_Tx"         , L"Tx_Cake3.png"),
		ResourceLoadData(L"WallSponge_Tx"        , L"Tx_Sponge.png"),
		ResourceLoadData(L"WallSponge2_Tx"       , L"Tx_Sponge2.png"),
		ResourceLoadData(L"TitleFont_Tx"         , L"TitleFont.png"),
		ResourceLoadData(L"Title_Tx"             , L"TitleChoco.png"),
		ResourceLoadData(L"HpDraw_Tx"            , L"HPPinch.png"),
		ResourceLoadData(L"Cokie_Tx"             , L"Cokie.png"),
		ResourceLoadData(L"Cokie_Crack_Tx"       , L"Cokie_Crack.png"),
		ResourceLoadData(L"Cokie_Crack_Last_Tx"  , L"Cokie_Crack_Last.png"),
		ResourceLoadData(L"FadeBack_Tx"          , L"FadeBack.png"),

		//�v�����[�O�p
		ResourceLoadData(L"Prologue_Tx"          , L"Prologue.png"),
		ResourceLoadData(L"PrologueScond_Tx"     , L"Prologue_second.png"),

		//�f�u�Q�[�W
		ResourceLoadData(L"ChubbyFont_Tx"  , L"WeightTx_ChubbyFont.png"),
		ResourceLoadData(L"ChubbyGauge_Tx" , L"WeightTx_ChubbylGauge.png"),
		ResourceLoadData(L"HungerFont_Tx"  , L"WeightTx_HungerFont.png"),
		ResourceLoadData(L"HungerGauge_Tx" , L"WeightTx_HungerGauge.png"),
		ResourceLoadData(L"NomalFont_Tx"   , L"WeightTx_NomalFont.png"),
		ResourceLoadData(L"NomalGauge_Tx"  , L"WeightTx_NomalGauge.png"),
		ResourceLoadData(L"SkinnyFont_Tx"  , L"WeightTx_SkinnyFont.png"),
		ResourceLoadData(L"SkinnyGauge_Tx" , L"WeightTx_SkinnyGauge.png"),
	};

	const std::vector<LoadStage::ResourceLoadData> LoadStage::m_seResourceLoadDatas =
	{
		ResourceLoadData(L"HideSE", L"HideSE.wav"),
		ResourceLoadData(L"HandyWalkSE1", L"HandyWalkSE1.wav"),
		ResourceLoadData(L"HandyWalkSE2", L"HandyWalkSE2.wav"),
		ResourceLoadData(L"PlayerWalkSE1", L"PlayerWalkSE1.wav"),
		ResourceLoadData(L"PlayerWalkSE2", L"PlayerWalkSE2.wav"),
		ResourceLoadData(L"UI_SelectSE",L"UI_SelectSE.wav"),
		ResourceLoadData(L"UI_PushSE",L"UI_PushSE.wav")
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
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	void LoadStage::LoadResource()
	{
		std::lock_guard<std::mutex> lock(m_mtx);

		const auto& app = App::GetApp();

		std::wstring mediaDir;
		mediaDir = app->GetDataDirWString();

		// �e�N�X�`���t�H���_

		std::wstring dir = mediaDir + L"Textures\\";

		for (auto& textureLoadData : m_texureResourceLoadDatas)
		{
			app->RegisterTexture(textureLoadData.resourceKey, dir + textureLoadData.filename);
		}

		// SE�t�H���_

		dir = mediaDir + L"SEs\\";

		for (auto& seLoadData : m_seResourceLoadDatas)
		{
			app->RegisterWav(seLoadData.resourceKey, dir + seLoadData.filename);
		}

		// BGM�t�H���_

		dir = mediaDir + L"BGMs\\";

		for (auto& bgmLoadData : m_bgmResourceLoadDatas)
		{
			app->RegisterWav(bgmLoadData.resourceKey, dir + bgmLoadData.filename);
		}

		// ���f���t�H���_

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

		auto& soundSetting = GameSaveManager::GetSoundSetting();
		if (!soundSetting->Load())
		{
			soundSetting->SetBGMVolume(1.0f);
			soundSetting->SetSEVolume(1.0f);
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