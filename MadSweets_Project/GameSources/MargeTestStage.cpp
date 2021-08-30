
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
#include "OriginalMeshObject.h"

#include "WallEvasion.h"

#include "LoadStageTrigger.h"
#include "LoadStageTriggerObject.h"

#include "EatenObject.h"
#include "PlowlingMove.h"

// 板橋 追加分 ----------------

#include "CameraHelper.h"
#include "GaugeManager.h"
#include "GameMessageWindowObject.h"
#include "PlayerInputer.h"

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
			light.m_DiffuseColor = Col4(0.3f);
			//light.m_Directional = Vec3(0.0f);
			light.m_SpecularColor = Col4(0.3f);
			//light.m_Directional = poss[i];
		}
	}

	void MargeTestStage::OnCreate() {
		try {
			//AddGameObject<DebugObject>()->SetDrawLayer(100);
			//DebugObject::sm_isResetDelta = true;

			//ビューとライトの作成
			CreateViewLight();

			// 板橋 追加分 ---------------

			Instantiate<CameraObject>();
			Instantiate<GameMessageWindowObject>();

			// ---------------------------

			TempLoad();

			//ゲージの生成
			auto gauge = Instantiate<GaugeUI>();
			auto rectTransform = gauge->GetComponent<RectTransform>();
			rectTransform->SetAnchor(AnchorType::LeftUp);
			rectTransform->SetPosition(200, -50);
			auto gaugeManager = gauge->GetComponent<GaugeManager>();
			gaugeManager->SetGaugeImage(L"WeightGaugeColor");
			gaugeManager->SetGaugeBackgroundImage(L"WeightGaugeBackground");
			gaugeManager->SetGaugeRectSize(768 * 0.5f, 256 * 0.5f);
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
			auto player = Instantiate<PlayerObject>(Vec3(-21.0f, +1.0f, -21.0f),Quat());
			player->AddComponent<PointLight>();
			//player->RemoveComponent<CollisionCapsule>();
			//player->AddComponent<CollisionObb>();
			player->SetDrawActive(false);
			//player->AddComponent<CollisionObb>();
			//場所を把握するための処理
			//player->AddComponent<PositionDrawComp>();
			m_player = player;

			//CreateMap(L"TempStage.csv");
			CreateMap(L"Stage1.csv");
			//CreateMap(L"Stage2.csv");
			//CreateMap(L"Stage3.csv");

			//敵の生成
			CreateEnemy(player);

			//食べ物の生成
			//CreateEatItems();

			//ライトの生成
			CreatePointLight();

			//クッキーの生成
			//CreateSoundCookies();
			//CreateCrackCookies();

			//隠れるオブジェクトの生成
			//CreateHideObjects();

			//auto loadTrigger = Instantiate<GameObject>(Vec3(-8.0f, +1.0f, -12.0f),Quat::Identity())->AddComponent<LoadStageTrigger>();
			//loadTrigger->GetGameObject()->GetComponent<Transform>()->SetScale(Vec3(2.0f));
			//loadTrigger->GetGameObject()->AddComponent<PNTStaticDraw>()->SetMeshResource(L"DEFAULT_CUBE");

			//AddGameObject<MTestEnemyObject>()->GetComponent<Transform>()->SetScale(Vec3(1.0f));

			//auto table = Instantiate<GameObject>();
			//table->AddComponent<PNTPointDraw>()->SetMeshResource(L"Table");
			//table->GetComponent<Transform>()->SetScale(Vec3(1.0f,0.8f,1.0f));

			EventSystem::GetInstance(GetThis<Stage>())->SetBasicInputer(PlayerInputer::GetInstance());
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

		map->CreateObject<OriginalMeshObject>(L"Chair", offset);
		map->CreateObject<OriginalMeshObject>(L"Table",offset);
		map->CreateObject<OriginalMeshObject>(L"Table2", offset);
		map->CreateObject<CookieHideObject>(L"Locker01", offset);
		map->CreateObject<LoadStageTriggerObject>(L"Trigger",offset);
		map->CreateObject<EatenObject>(L"EatenObject",offset);

		m_mapCsv = map;

		CreateAstar();
	}

	void MargeTestStage::ChangeMap(const wstring& fileName, const std::shared_ptr<AlphaFadeCtrl>& fade, const Vec3& offset) {
		//マップ情報の切り替え
		bool isNewCreate = m_mapCsv->ChangeMap(fileName);
		if (isNewCreate) {
			CreateMap(fileName, offset);
		}
		
		//フェードイン
		fade->FadeInStart();
	}

	GraphAstar MargeTestStage::CreateAstar() {

		SparseGraph<NavGraphNode, GraphEdge> graph(true);
		//GraphAstar astar(graph);
		vector<std::shared_ptr<GameObject>> stageObjs;
		vector<std::shared_ptr<GameObject>> excluteObjs;

		for (auto& obj : GetGameObjectVec()) {
			auto stageObj = dynamic_pointer_cast<StageObject>(obj);
			if (stageObj) {
				stageObjs.push_back(stageObj);
			}
		}

		excluteObjs.push_back(m_player);

		int index = 0;
		auto positions = m_mapCsv->GetPositions(L"Capsule");
		for (const auto& pos : positions) {
			graph.AddNode(NavGraphNode(index++, pos));
			//astar.AddNode(pos, m_stageObjs, m_excluteObjs);
		}

		vector<GraphEdge> edges = {
			{GraphEdge(0,1)},
			{GraphEdge(0,5)},
			{GraphEdge(0,7)},
			{GraphEdge(1,0)},
			{GraphEdge(1,12)},
			{GraphEdge(1,2)},
			{GraphEdge(2,1)},
			{GraphEdge(2,3)},
			{GraphEdge(3,2)},
			{GraphEdge(3,4)},
			{GraphEdge(4,3)},
			{GraphEdge(4,5)},
			{GraphEdge(5,4)},
			{GraphEdge(5,0)},
			{GraphEdge(5,11)},

			{GraphEdge(6,1)},
			{GraphEdge(6,12)},
			{GraphEdge(7,1)},
			{GraphEdge(7,8)},
			{GraphEdge(8,7)},
			{GraphEdge(8,9)},
			{GraphEdge(8,12)},
			{GraphEdge(9,8)},
			{GraphEdge(9,13)},
			{GraphEdge(10,11)},
			{GraphEdge(11,10)},
			{GraphEdge(11,5)},
			{GraphEdge(12,6)},
			{GraphEdge(12,13)},
			{GraphEdge(12,8)},

			{GraphEdge(13,12)},
			{GraphEdge(13,9)},
			{GraphEdge(14,15)},
			{GraphEdge(15,14)},
			{GraphEdge(15,16)},
			{GraphEdge(16,15)},
			{GraphEdge(16,17)},
			{GraphEdge(17,16)},
		};

		for (auto& edge : edges) {
			graph.AddEdge(edge);
		}

		GraphAstar astar(graph);

		//GraphAstar astar(graph);
		//astar.AddEdges(stageObjs, excluteObjs);
		
		//エネミーの仮生成
		auto enemy = Instantiate<HandyObject>(Vec3(0.0f,0.0f,0.0f), Quat::Identity());
		enemy->AddComponent<AstarCtrl>(astar);
		enemy->GetComponent<EyeSearchRange>()->AddTarget(m_player);

		auto wallEvasion = enemy->GetComponent<WallEvasion>();
		if (wallEvasion) {
			for (auto& obj : GetGameObjectVec()) {
				auto stageObj = dynamic_pointer_cast<StageObject>(obj);
				if (stageObj) {
					wallEvasion->AddObstacleObjs(stageObj);
				}
			}
		}

		enemy->GetComponent<Transform>()->SetPosition(positions[0]);
		vector<Vec3> poss;
		poss.push_back(positions[0]);
		poss.push_back(positions[1]);
		enemy->GetComponent<PlowlingMove>()->SetPositions(poss);
		//m_player->GetComponent<Transform>()->SetPosition(poss[0]);
		//m_player->GetComponent<Transform>()->SetPosition(13,1.0,-6.5);

		//DebugObject::sm_wss << to_wstring(stageObjs.size());

		return astar;
	}

	void MargeTestStage::TempLoad() {
		//音ロード
		//wstring SE_Dir = mediaDir + L"SEs\\";
		//App::GetApp()->RegisterWav(L"Test", SE_Dir + L"Test.wav");
		//App::GetApp()->RegisterWav(L"Test2", SE_Dir + L"Test2.wav");
	}

	void MargeTestStage::CreateEnemy(const std::shared_ptr<GameObject>& player) {
		return;
		//auto enemy = Instantiate<ChaseEnemyObject>(Vec3(0.0f, 1.0f, 0.0f), Quat());
		//auto enemy = Instantiate<EscapeEnemyObject>(Vec3(0.0f,1.0f,0.0f),Quat());
		auto enemy = Instantiate<HandyObject>(Vec3(0.0f, 1.0f, 0.0f), Quat::Identity());
		//auto enemy = Instantiate<CaraObject>(Vec3(0.0f, 1.0f, 0.0f), Quat::Identity());
		//auto enemy = Instantiate<AshiObject>(Vec3(0.0f, 1.0f, 0.0f), Quat::Identity());
		//auto enemy = Instantiate<GraObject>(Vec3(0.0f, 1.0f, 0.0f), Quat::Identity());

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
		//auto astar = CreateAstar();
		enemy->AddComponent<AstarCtrl>(astar);
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




