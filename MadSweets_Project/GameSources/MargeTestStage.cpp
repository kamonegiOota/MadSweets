
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
#include "SoundCookieObject.h"
#include "CrackCookieObject.h"
#include "HiddenComponent.h"
#include "PNTPointDraw.h"

#include "PointLight.h"
#include "CookieHideObject.h"
#include "WeightGaugeUI.h"
#include "HandyObject.h"
#include "CaraObject.h"
#include "AshiObject.h"
#include "GraObject.h"

#include "WallEvasion.h"

#include "LoadStageTrigger.h"
#include "LoadStageTriggerObject.h"

#include "EatenObject.h"

// 板橋 追加分 ----------------

#include "CameraHelper.h"

// ----------------------------

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

		Vec3 poss[] = {
			{Vec3(0.0f,0.5f,0.0f)},
			{Vec3(0.0f,-0.5f,0.0f)},
			{Vec3(-0.5f,0.0f,0.0f)},
		};

		//ライトの設定
		for (int i = 0; i < 3; i++) {
			auto& light = PtrMultiLight->GetLight(i);
			light.m_DiffuseColor = Col4(0.25f);
			//light.m_Directional = Vec3(0.0f);
			light.m_SpecularColor = Col4(0.25f);
			//light.m_Directional = poss[i];
		}
	}

	void MargeTestStage::OnCreate() {
		try {
			AddGameObject<DebugObject>()->SetDrawLayer(100);
			//DebugObject::sm_isResetDelta = true;

			//ビューとライトの作成
			CreateViewLight();

			// 板橋 追加分 ---------------

			AddGameObject<CameraObject>();

			// ---------------------------

			TempLoad();
			CreateMap(L"TempStage.csv");
			//CreateMap(L"Stage1.csv");
			//CreateMap(L"Stage2.csv");
			//CreateMap(L"Stage3.csv");

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

			//ウェイトゲージの生成
			Instantiate<WeightGaugeUI>();

			//プレイヤーの生成
			SetSharedGameObject(L"PlayerWeightGauge", gauge);
			auto player = Instantiate<PlayerObject>(Vec3(+12.0f, +1.0f, -12.0f),Quat());
			player->AddComponent<PointLight>();
			//player->RemoveComponent<CollisionCapsule>();
			//player->AddComponent<CollisionObb>();
			player->SetDrawActive(false);
			//player->AddComponent<CollisionObb>();
			//場所を把握するための処理
			//player->AddComponent<PositionDrawComp>();

			//敵の生成
			CreateEnemy(player);

			//食べ物の生成
			//CreateEatItems();

			//ライトの生成
			CreatePointLight();

			//クッキーの生成
			CreateSoundCookies();
			CreateCrackCookies();

			//隠れるオブジェクトの生成
			CreateHideObjects();

			//auto loadTrigger = Instantiate<GameObject>(Vec3(-8.0f, +1.0f, -12.0f),Quat::Identity())->AddComponent<LoadStageTrigger>();
			//loadTrigger->GetGameObject()->GetComponent<Transform>()->SetScale(Vec3(2.0f));
			//loadTrigger->GetGameObject()->AddComponent<PNTStaticDraw>()->SetMeshResource(L"DEFAULT_CUBE");

			//AddGameObject<MTestEnemyObject>()->GetComponent<Transform>()->SetScale(Vec3(1.0f));


		}
		catch (...) {
			throw;
		}
	}

	void MargeTestStage::OnUpdate() {

	}

	void MargeTestStage::CreateMap(const wstring& fileName, const Vec3& offset)
	{
		//m_nowMap = fileName;
		auto map = AddGameObject<StageMapCSV>(L"MapDatas/", fileName);

		vector<wstring> objNames = {
			{L"StageRotBox"},
			{L"Plane"},
			{L"BoxCollision"},
			{L"Floor"},
			{L"RoomWall"},
			{L"Wall"},
			{L"Partition"},
			{L"UpperWall"},
			{L"Corner"},
			{L"RoomCorner"},
			{L"InnerCorner"},
			{L"FrontWall"},
			{L"RightWall"},
			{L"BackWall"},
			{L"LeftWall"},
			{L"LeftWall"},
			{L"CandyDoor"},
			{L"Stairs"},
			//{L"Cube"},
		};

		for (const auto& objName : objNames) {
			map->CreateObject<FixedBox>(objName,offset);
		}

		map->CreateObject<CookieHideObject>(L"WallHide", offset);
		map->CreateObject<LoadStageTriggerObject>(L"Trigger",offset);
		map->CreateObject<EatenObject>(L"EatenObject",offset);

		for (auto obj : GetGameObjectVec()) {
			auto fixed = dynamic_pointer_cast<FixedBox>(obj);
			if (fixed) {
				//fixed->GetComponent<Collision>()->SetUpdateActive(false);
				if (fixed->GetName() == L"UpperWall" || fixed->GetName() == L"InnerCorner") {
					//fixed->GetComponent<Collision>()->SetUpdateActive(false);
				}
			}
		}

		m_mapCsv = map;
	}

	void MargeTestStage::ChangeMap(const wstring& fileName, const std::shared_ptr<AlphaFadeCtrl>& fade, const Vec3& offset) {
		//マップ情報の切り替え
		bool isNewCreate = m_mapCsv->ChangeMap(fileName);
		if (isNewCreate) {
			CreateMap(fileName, offset);
		}
		
		//playerの移動
		
		//フェードイン
		fade->FadeInStart();
	}

	void MargeTestStage::TempLoad() {
		//音ロード
		//wstring SE_Dir = mediaDir + L"SEs\\";
		//App::GetApp()->RegisterWav(L"Test", SE_Dir + L"Test.wav");
		//App::GetApp()->RegisterWav(L"Test2", SE_Dir + L"Test2.wav");
	}

	void MargeTestStage::CreateEnemy(const std::shared_ptr<GameObject>& player) {
		//auto enemy = Instantiate<ChaseEnemyObject>(Vec3(0.0f, 1.0f, 0.0f), Quat());
		//auto enemy = Instantiate<EscapeEnemyObject>(Vec3(0.0f,1.0f,0.0f),Quat());
		//auto enemy = Instantiate<HandyObject>(Vec3(0.0f, 1.0f, 0.0f), Quat::Identity());
		auto enemy = Instantiate<CaraObject>(Vec3(0.0f, 1.0f, 0.0f), Quat::Identity());
		//auto enemy = Instantiate<AshiObject>(Vec3(0.0f, 1.0f, 0.0f), Quat::Identity());

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

			//{ 11.19f,   0.87f,	3.89f},
			//{  2.94f, 	0.87f,  -5.83f	},
			//{ -2.25f,	0.87f,  -14.27f },
			//{ 10.73f,	0.87f,  -14.27f },
			//{ 16.35f,	0.87f,  -10.21f },
			//{ 16.35f,	0.87f,	2.64f },
			//{ -7.36f,	0.87f,  -1.05f },
			//{ 16.35f,	0.87f,  -6.6f },
		};

		int index = 0;
		for (auto pos : poss) {
			graph.AddNode(NavGraphNode(index++, pos));
		}

		vector<GraphEdge> edges = {
			  //{GraphEdge(0,5)},
			  //{GraphEdge(0,1)},

			  //{GraphEdge(1,0)},
			  //{GraphEdge(1,2)},
			  //{GraphEdge(1,6)},

			  //{GraphEdge(2,1)},
			  //{GraphEdge(2,3)},

			  //{GraphEdge(3,2)},
			  //{GraphEdge(3,4)},

			  //{GraphEdge(4,3)},
			  //{GraphEdge(4,7)},

			  //{GraphEdge(5,0)},
			  //{GraphEdge(5,7)},

			  //{GraphEdge(6,1)},

			  //{GraphEdge(7,5)},
			  //{GraphEdge(7,4)},

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

		auto wallEvasion = enemy->GetComponent<WallEvasion>();
		if (wallEvasion) {
			for (auto& obj : GetGameObjectVec()) {
				auto stageObj = dynamic_pointer_cast<StageObject>(obj);
				if(stageObj){
					wallEvasion->AddObstacleObjs(stageObj);
				}
			}
		}
	}

	void MargeTestStage::CreateEatItems() {
		Vec3 poss[] = {
			//{ +0.0f, +1.0f, +0.0f},//0
			//{-12.0f, +1.0f,-12.0f},
			//{+12.0f, +1.0f,-12.0f},//2
			{+13.0f, +1.0f,+13.0f},
			//{ +0.0f, +1.0f,+12.0f},//4
			//{-10.0f, +1.0f,+12.0f},
			//{-12.0f, +1.0f, +6.0f},//6
			//{-12.0f, +1.0f, -7.0f},

			//{-21.0f,1.0f,-20.0f}
		};

		//std::shared_ptr<GameObject> enemy;
		//for (auto& obj : GetGameObjectVec()) {
		//	auto ene = obj->GetComponent<ChaseEnemyObject>(false);
		//	if (ene) {
		//		enemy = ene;
		//		break;
		//	}
		//}

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
			//{-12.0f,1.5f,-12.0f},
			//{0.0f,0.0f,0.0f},

			{ +0.0f, +1.0f, +0.0f},//0
			{-12.0f, +1.0f,-12.0f},
			{+12.0f, +1.0f,-12.0f},//2
			{+11.0f, +1.0f,+11.0f},
			{ +0.0f, +1.0f,+12.0f},//4
			{-10.0f, +1.0f,+12.0f},
			{-12.0f, +1.0f, +7.0f},//6
			{-12.0f, +1.0f, -6.0f},
		};

		//constexpr int num = ;
		for (const auto& pos : positions) {
			auto obj = Instantiate<GameObject>(pos,Quat());
			obj->AddComponent<PointLight>();
		}
	}

	void MargeTestStage::CreateSoundCookies() {
		Vec3 positions[] = {
			{-12.0f,1.0f,-12.0f},
		};

		for (const auto& pos : positions) {
			auto obj = Instantiate<SoundCookieObject>(pos, Quat());
			//obj->AddComponent<PointLight>();
		}
	}

	void MargeTestStage::CreateCrackCookies() {
		Vec3 positions[] = {
			{13.0f,0.2f,12.0f},
		};

		for (const auto& pos : positions) {
			auto obj = Instantiate<CrackCookieObject>(pos, Quat());
			//obj->AddComponent<PointLight>();
		}
	}

	void MargeTestStage::CreateHideObjects() {
		Vec3 positions[] = {
			{14.0f,1.0f,-6.0f},
			//{11.0f,1.0f, 11.0f},
		};

		for (const auto& pos : positions) {
			auto obj = Instantiate<GameObject>(pos, Quat());
			obj->AddComponent<HiddenComponent>(pos,obj->GetComponent<Transform>()->GetForword());
			obj->AddComponent<PNTPointDraw>()->SetMeshResource(L"DEFAULT_CUBE");
			obj->AddComponent<CollisionObb>()->SetFixed(true);
			
			//obj->AddComponent<PointLight>();
		}
	}
}

//endbasecross