
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
#include "TestEatenObject.h"

#include "PositionDrawComp.h"

#include "ChaseEnemyObject.h"
#include "EscapeEnemyObject.h"
#include "EyeSearchRange.h"

#include "SparseGraph.h"
#include "GraphEdge.h"
#include "NavGraphNode.h"
#include "GraphAstar.h"
#include "AstarCtrl.h"
#include "MTestEnemyObject.h"

#include "PointLight.h"

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
		//PtrMultiLight->SetAmbientLightColor(Col4(1.0f,0.1f,0.1f,0.1f));

		for (int i = 0; i < 3; i++) {
			auto& light = PtrMultiLight->GetLight(i);
			light.m_DiffuseColor = Col4(0.1f);
			//light.m_Directional = Vec3(0.0f);
			light.m_SpecularColor = Col4(0.1f);
			
		}
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

			//UI周り
			auto go = Instantiate<UIObject>();
			go->GetComponent<RectTransform>()->SetPosition(300, 0);
			auto mo = go->AddComponent<ChoicesList>();
			mo->OnStart();

			SetSharedGameObject(L"PlayerChoicesList", go);

			//プレイヤーの生成
			SetSharedGameObject(L"PlayerWeightGauge", gauge);
			auto player = Instantiate<PlayerObject>(Vec3(+12.0f, +1.0f, -12.0f),Quat());
			//player->RemoveComponent<CollisionCapsule>();
			//player->AddComponent<CollisionObb>();
			//player->SetDrawActive(false);
			//player->AddComponent<CollisionObb>();
			//場所を把握するための処理
			//player->AddComponent<PositionDrawComp>();

			//敵の生成
			CreateEnemy(player);

			//食べ物の生成
			CreateEatItems();

			//ライトの生成
			CreatePointLight();

			//AddGameObject<MTestEnemyObject>();

			AddGameObject<DebugObject>()->SetDrawLayer(100);
			//DebugObject::sm_isResetDelta = true;
		}
		catch (...) {
			throw;
		}
	}

	void MargeTestStage::OnUpdate() {
		for (auto obj : GetGameObjectVec()) {
			auto player = dynamic_pointer_cast<PlayerObject>(obj);
			if (player) {
				//DebugObject::m_wss << L"ss";
				auto pos = player->GetComponent<Transform>()->GetPosition();
				//auto forward = player->GetComponent<Transform>()->GetForword();
				auto light = dynamic_pointer_cast<MultiLight>(GetLight());
				auto newLight = light->GetLight(2);
				//newLight.m_Directional = forward;
				newLight.m_Directional = pos;
				newLight.m_DiffuseColor = Col4(1.0f);
				newLight.m_SpecularColor = Col4(1.0f);
				//light->SetDefaultLighting();
			}
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
		app->RegisterTexture(L"WallCake_Tx", textureDir + L"Tx_Cake.png");
		app->RegisterTexture(L"WallSponge_Tx", textureDir + L"Tx_Sponge.png");

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

		modelMesh = MeshResource::CreateBoneModelMesh(
			modelDir + L"Handy\\", L"Handy_Walk.bmf");
		app->RegisterResource(L"Handy", modelMesh);
	}

	void MargeTestStage::CreateEnemy(const std::shared_ptr<GameObject>& player) {
		auto enemy = Instantiate<ChaseEnemyObject>(Vec3(0.0f, 1.0f, 0.0f), Quat());
		//auto enemy = Instantiate<EscapeEnemyObject>(Vec3(0.0f,1.0f,0.0f),Quat());
		SparseGraph<NavGraphNode, GraphEdge> graph(true);
		
		//Astar生成
		std::vector<Vec3> poss = {
			{ +0.0f, +1.0f, +0.0f},//0
			{-12.0f, +1.0f,-12.0f},
			{+12.0f, +1.0f,-12.0f},//2
			{+11.0f, +1.0f,+11.0f},
			{ +0.0f, +1.0f,+12.0f},//4
			{-10.0f, +1.0f,+12.0f},
			{-12.0f, +1.0f, +7.0f},//6
			{-12.0f, +1.0f, -6.0f},
		};

		int index = 0;
		for (auto pos : poss) {
			graph.AddNode(NavGraphNode(index++, pos));
		}

		vector<GraphEdge> edges = {
			{GraphEdge(0,1)},
			{GraphEdge(0,2)},
			{GraphEdge(0,4)},
			{GraphEdge(1,0)},
			{GraphEdge(1,2)},
			{GraphEdge(1,7)},
			{GraphEdge(2,0)},
			{GraphEdge(2,1)},
			{GraphEdge(2,3)},
			{GraphEdge(3,2)},
			{GraphEdge(3,4)},
			{GraphEdge(4,0)},
			{GraphEdge(4,3)},
			{GraphEdge(4,5)},
			{GraphEdge(5,4)},
			{GraphEdge(5,6)},
			{GraphEdge(6,5)},
			{GraphEdge(7,1)},
		};

		for (auto& edge : edges) {
			graph.AddEdge(edge);
		}

		GraphAstar astar(graph);
		enemy->AddComponent<AstarCtrl>(graph);
		enemy->GetComponent<EyeSearchRange>()->AddTarget(player);
	}

	void MargeTestStage::CreateEatItems() {
		Vec3 poss[] = {
			//{ +0.0f, +1.0f, +0.0f},//0
			//{-12.0f, +1.0f,-12.0f},
			//{+12.0f, +1.0f,-12.0f},//2
			{+13.0f, +1.0f,+13.0f},
			//{ +0.0f, +1.0f,+12.0f},//4
			//{-10.0f, +1.0f,+12.0f},
			{-12.0f, +1.0f, +6.0f},//6
			//{-12.0f, +1.0f, -7.0f},
		};

		std::shared_ptr<GameObject> enemy;
		for (auto& obj : GetGameObjectVec()) {
			auto ene = obj->GetComponent<ChaseEnemyObject>(false);
			if (ene) {
				enemy = ene;
				break;
			}
		}

		for (auto& pos : poss) {
			pos.y += -0.5f;
			AddGameObject<FixedBox>(L"Fixed", Vec3(0.5f,1.0f,0.5f), Vec3(0.0f), pos, L"");
			pos.y += 1.0f;
			auto item = Instantiate<TestEatenObject>(pos,Quat());
			item->GetComponent<Collision>()->SetAfterCollision(AfterCollision::None);
			//item->GetComponent<Collision>()->AddExcludeCollisionGameObject(enemy);
		}
	}

	void MargeTestStage::CreatePointLight() {
		
		Vec3 positions[] = {
			{-12.0f,1.5f,-12.0f},
			{0.0f,0.0f,0.0f},
			
		};

		constexpr int num = 1;
		for (int i = 0; i < num; i++) {
			auto obj = Instantiate<GameObject>(positions[i],Quat());
			obj->AddComponent<PointLightComp>();
		}
	}
}

//endbasecross