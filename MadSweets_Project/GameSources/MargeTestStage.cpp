
/*!
@file MargeTestStage.h
@brief MargeTestStage
担当者：丸山 裕喜
*/

#include "MargeTestStage.h"
#include "StageMapCSV.h"
#include "FixedBox.h"

#include "DebugObject.h"

#include "PlayerObject.h"
#include "GaugeUI.h"

#include "PositionDrawComp.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void MargeTestStage::CreateViewLight() {
		const Vec3 eye(0.0f, +15.0f, -30.0f);
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

	void MargeTestStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			TempLoad();
			CreateMap(L"TempStage.csv");

			//ゲージの生成
			auto gauge = Instantiate<GaugeUI>();
			auto rectTransform = gauge->GetComponent<RectTransform>();
			rectTransform->SetAnchor(AnchorType::LeftUp);

			//プレイヤーの生成
			SetSharedGameObject(L"PlayerWeightGauge", gauge);
			auto player = Instantiate<PlayerObject>(Vec3(+12.0f, +1.0f, -12.0f),Quat());
			player->SetDrawActive(false);
			player->AddComponent<CollisionObb>();
			//場所を把握するための処理
			player->AddComponent<PositionDrawComp>();

			AddGameObject<DebugObject>()->SetDrawLayer(100);
			DebugObject::sm_isResetDelta = true;
		}
		catch (...) {
			throw;
		}
	}

	void MargeTestStage::CreateMap(const wstring& fileName)
	{
		auto map = AddGameObject<StageMapCSV>(L"MapDatas/", fileName);

		map->CreateObject<FixedBox>(L"StageRotBox");
		map->CreateObject<FixedBox>(L"Plane");
	}

	void MargeTestStage::TempLoad() {
		std::wstring mediaDir = App::GetApp()->GetDataDirWString();
		auto& app = App::GetApp();

		std::wstring textureDir = mediaDir + L"Textures\\";
		app->RegisterTexture(L"WeightGaugeBackground", textureDir + L"WeightGaugeBackGround.png");
		app->RegisterTexture(L"WeightGaugeColor", textureDir + L"WeightGaugeColor.png");
		//モデル
		std::wstring modelDir = mediaDir + L"Models\\";
		auto modelMesh = MeshResource::CreateBoneModelMesh(
			modelDir + L"Player\\StandStay\\", L"PlayerStandStay.bmf");
		app->RegisterResource(L"PlayerStandStay", modelMesh);
		modelMesh = MeshResource::CreateBoneModelMesh(
			modelDir + L"Player\\CrouchStay\\", L"PlayerCrouchStay.bmf");
		app->RegisterResource(L"PlayerCrouchStay", modelMesh);
		modelMesh = MeshResource::CreateBoneModelMesh(
			modelDir + L"Player\\StandToCrouch\\", L"PlayerStandToCrouch.bmf");
		app->RegisterResource(L"PlayerStandToCrouch", modelMesh);
	}

	void MargeTestStage::CreateEnemy(const std::shared_ptr<GameObject>& player) {

	}
}

//endbasecross