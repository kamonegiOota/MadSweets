
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
#include "BaseEnemy.h"

#include "UtilityAstar.h"
#include "UtilityEnemy.h"

#include "PointLightObject.h"
#include "EnState_Plowling.h"

// 板橋 追加分 ----------------

#include "CameraHelper.h"
#include "GaugeManager.h"
#include "GameMessageWindowObject.h"
#include "PlayerInputer.h"
#include "PlayerCalorieGaugeObject.h"
#include "PlayerChoicesListObject.h"

// ----------------------------

#include "PlayerStatusMgr.h"
#include "PlayerWeightMgr.h"
#include "PlayerCalorieManager.h"
#include "Velocity.h"

#include "GameItemKeyObject.h"
#include "DoorObject.h"
#include "AstarEdgeDraw.h"
#include "Number.h"
#include "NumberObject.h"
#include "NumbersObject.h"
#include "NumbersCtrl.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------

	//wstring MargeTestStage::sm_nowMap = L"TempStage.csv";
	wstring MargeTestStage::sm_nowMap = L"Stage1.csv";
	Vec3 MargeTestStage::sm_firstCreatePlayerPosition = Vec3(-21.0f, +1.0f, -21.0f);
	//Vec3 MargeTestStage::sm_firstCreatePlayerPosition = Vec3(1.0f, +1.0f, 1.0f);
	Vec3 MargeTestStage::sm_createPlayerPosition = sm_firstCreatePlayerPosition;
	Vec3 MargeTestStage::sm_cretaePlayerForward = Vec3(1.0f, 0.0f, 0.0f);

	void MargeTestStage::SavingValueSet(const std::shared_ptr<PlayerObject> player, const std::shared_ptr<WeightGaugeCtrl>& weight) {
		auto saveValue = LoadStageTrigger::GetSavingValue();
		if (saveValue.hp == 0.0f) {
			return;
		}

		auto status = player->GetComponent<PlayerStatusMgr>(false);
		auto calorie = player->GetComponent<PlayerCalorieManager>(false);

		if (status && calorie) {
			status->SetHP(saveValue.hp);
			weight->SetNowGauge(saveValue.weight);
			weight->ChangeState(saveValue.weightState);
			calorie->SetNowCalorie(saveValue.calorie);
		}
	}

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
			light.m_DiffuseColor = Col4(0.35f);
			//light.m_Directional = Vec3(0.0f);
			light.m_SpecularColor = Col4(0.35f);
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
			Instantiate<CameraObject>();
			Instantiate<GameMessageWindowObject>();
			// ---------------------------

			auto fade = Instantiate<AlphaFadeObject>()->GetComponent<AlphaFadeCtrl>();
			fade->FadeInStart();

			//ゲージの生成
			Instantiate<PlayerCalorieGaugeObject>();

			//UI周り
			Instantiate<PlayerChoicesListObject>();

			//ウェイトゲージの生成
			auto weightGauge = Instantiate<WeightGaugeUI>()->GetComponent<WeightGaugeCtrl>();

			auto fadeObject = Instantiate<UIObject>();
			fadeObject->SetDrawLayer(100000);
			auto alphaFade = fadeObject->AddComponent<AlphaFadeCtrl>();
			alphaFade->AddEndAction(GetThis<MargeTestStage>(), &MargeTestStage::GoClearStage);

			SetSharedGameObject(L"FinishFadeObject", fadeObject);

			//プレイヤーの生成
			auto player = Instantiate<PlayerObject>(sm_createPlayerPosition,Quat());
			player->GetComponent<Transform>()->SetForward(sm_cretaePlayerForward);
			sm_createPlayerPosition = sm_firstCreatePlayerPosition;
			player->AddComponent<PointLight>();
			player->SetDrawActive(false);
			m_player = player;
			SavingValueSet(player, weightGauge);

			CreateMap(sm_nowMap);
			
			EventSystem::GetInstance(GetThis<Stage>())->SetBasicInputer(PlayerInputer::GetInstance());

			//test
			Instantiate<NumbersObject>(sm_createPlayerPosition, Quat());

			return;
			//test
			CreatePointLight();
			//敵の生成
			CreateEnemy(player);
			CreateHideObjects();
			CreateEatItems();
		}
		catch (...) {
			throw;
		}
	}

	void MargeTestStage::OnUpdate() {

	}

	void MargeTestStage::GoClearStage()
	{
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<SceneBase>(), L"ToClearStage");
	}

	void MargeTestStage::CreateMap(const wstring& fileName, const Vec3& offset)
	{
		auto map = AddGameObject<StageMapCSV>(L"MapDatas/", fileName);

		vector<wstring> objNames = {
			{L"StageRotBox"},{L"Plane"},{L"BoxCollision"},
			{L"Floor"},{L"RoomWall"},{L"Wall"},
			{L"Partition"},{L"UpperWall"},{L"Corner"},
			{L"RoomCorner"},{L"InnerCorner"},{L"FrontWall"},
			{L"RightWall"},{L"BackWall"},{L"LeftWall"},
			{L"LeftWall"},{L"CandyDoor"},{L"Stairs"},
		};

		for (const auto& objName : objNames) {
			map->CreateObject<FixedBox>(objName,offset);
		}

		map->CreateObject<OriginalMeshObject>(L"Chair", offset);
		map->CreateObject<OriginalMeshObject>(L"Table",offset);
		map->CreateObject<OriginalMeshObject>(L"Table2", offset);
		map->CreateObject<CookieHideObject>(L"Locker01", offset);
		map->CreateObject<LoadStageTriggerObject>(L"Trigger",offset);
		map->CreateObject<PointLightObject>(L"Light", offset);
		map->CreateObject<SoundCookieObject>(L"SoundCokie", offset);
		map->CreateObject<FixedBox>(L"Ceiling", offset);

		//eatオブジェクト
		auto positions = map->GetPositions(L"EatenObject");
		auto textures = map->GetTextures(L"EatenObject");
		for (int i = 0; i < positions.size() ; i++) {
			auto eatenObj = Instantiate<EatenObject>(positions[i], Quat::Identity());
			eatenObj->GetComponent<Transform>()->SetScale(Vec3(0.5f));
			eatenObj->SetTexture(textures[i]);
		}

		//鍵のオブジェクト
		positions = map->GetPositions(L"Key");
		for (auto& pos : positions) {
			Instantiate<GameItemKeyObject>(pos, Quat());
		}

		//扉
		positions = map->GetPositions(L"Door");
		for (auto& pos : positions) {
			Instantiate<DoorObject>(pos, Quat());
		}

		m_mapCsv = map;

		CreateAstar(fileName);
	}

	void MargeTestStage::ChangeMap(const wstring& fileName, const std::shared_ptr<AlphaFadeCtrl>& fade, const Vec3& offset) {
		//マップ情報の切り替え
		bool isNewCreate = m_mapCsv->ChangeMap(fileName);
		if (isNewCreate) {
			CreateMap(fileName, offset);
		}

		//敵の配置の切り替え
		auto enemys = maru::MyUtility::GetComponents<BaseEnemy>();
		for (auto& enemy : enemys) {
			if (fileName == enemy->GetMapType()) {
				auto plow = enemy->GetGameObject()->GetComponent<PlowlingMove>();
				auto pos = plow->GetNowTargetPosition();

				enemy->GetGameObject()->GetComponent<Transform>()->SetPosition(pos);

				enemy->GetGameObject()->SetUpdateActive(true);
				enemy->GetGameObject()->SetDrawActive(true);
			}
			else {
				enemy->GetGameObject()->SetUpdateActive(false);
				enemy->GetGameObject()->SetDrawActive(false);
				enemy->ChangeStateMachine<EnState_Plowling>();
			}
		}
		
		//フェードイン
		fade->FadeInStart();
	}


	GraphAstar MargeTestStage::CreateAstar(const wstring& fileName) {
		//将来的にそれ用のUtilかFactoryに書く
		auto graph = make_shared<SparseGraph<NavGraphNode, GraphEdge>>(true);
		vector<std::shared_ptr<GameObject>> obstacleObjs;
		vector<std::shared_ptr<GameObject>> excluteObjs;

		for (auto& obj : GetGameObjectVec()) {
			auto stageObj = dynamic_pointer_cast<StageObject>(obj);
			if (stageObj) {
				obstacleObjs.push_back(stageObj);
			}
		}

		excluteObjs.push_back(m_player);

		int index = 0;
		auto positions = m_mapCsv->GetPositions(L"Capsule");
		for (const auto& pos : positions) {
			graph->AddNode(make_shared<NavGraphNode>(index++, pos));
			//ノードの表示
			auto numberObj = Instantiate<NumbersObject>(pos, Quat::Identity());
			numberObj->GetComponent<NumbersCtrl>()->SetValue(index - 1);
			//auto obj = Instantiate<GameObject>(pos, Quat::Identity());
			//obj->AddComponent<PNTStaticDraw>()->SetMeshResource(L"DEFAULT_CUBE");
			//obj->GetComponent<Transform>()->SetScale(Vec3(0.5f));
			//astar.AddNode(pos, obstacleObjs, excluteObjs);
		}

		//手動で設定したノード
		auto edges = StageMapCSV::sm_astarEdges[fileName];
		for (auto& edge : edges) {
			graph->AddEdge(edge);
		}

		auto astar = GraphAstar(graph);
		//astar.AddEdges(obstacleObjs, excluteObjs);

		//エネミーの生成
		auto params = UtilityEnemy::sm_enemyParam[fileName];
		for (auto& param : params) {
			switch (param.type)
			{
			case UtilityEnemy::EnemyType::Handy:
				param.plowPositions = m_mapCsv->GetPositions(L"HandyPlowling");
				CreateEnemy<HandyObject>(fileName,astar,param.plowPositions);
				break;
			case UtilityEnemy::EnemyType::Cara:
				param.plowPositions = m_mapCsv->GetPositions(L"CaraPlowling");
				CreateEnemy<CaraObject>(fileName, astar, param.plowPositions);
				break;
			case UtilityEnemy::EnemyType::Gra:
				//CreateEnemy<GraObject>(fileName, astar, param.plowPositions);
				break;
			}
		}

		Instantiate<GameObject>()->AddComponent<AstarEdgeDraw>(astar);

		return astar;
	}

	void MargeTestStage::TempLoad() {

	}

	void MargeTestStage::CreateEnemy(const std::shared_ptr<GameObject>& player) {
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
			graph.AddNode(make_shared<NavGraphNode>(index++, pos));
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

		//GraphAstar astar(graph);
		//auto astar = CreateAstar();
		//enemy->AddComponent<AstarCtrl>(astar);
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
			//auto obj = Instantiate<SoundCookieObject>(pos, Quat());
			//obj->AddComponent<PointLight>();
		}
	}

	void MargeTestStage::CreateCrackCookies() {
		Vec3 positions[] = {
			{13.0f,0.2f,12.0f},
		};

		for (const auto& pos : positions) {
			//auto obj = Instantiate<CrackCookieObject>(pos, Quat());
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




