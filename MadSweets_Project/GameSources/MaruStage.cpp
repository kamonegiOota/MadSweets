/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"
#include "MaruStage.h"

#include "MTestEnemyObject.h"
#include "GraphAstar.h"
//#include "GraphEdge.h"
#include "AstarCtrl.h"
#include "DebugObject.h"
#include "BaseEnemy.h"
#include "MTestBox.h"
#include "TargetChase.h"
#include "PlayerMover.h"
#include "SearchObject.h"
#include "EyeSearchRange.h"
#include "ChaseEnemy.h"

#include "ChaseEnemyObject.h"
#include "EnemyEar.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void MaruStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -15.0f);
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



	void MaruStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();

			CreateGraphTest();

			//auto target = AddGameObject<MTestBox>();
			//target->AddComponent<BaseEnemy>();
			//target->SetColor(Col4(1.0f,0.0f,0.0f,1.0f));
			//target->GetComponent<Transform>()->SetPosition(Vec3(5.0f,1.0f,0.0f));

			//auto player = AddGameObject<MTestBox>();
			//player->SetColor(Col4(0.0f, 1.0f, 0.0f, 1.0f));
			//chaseEnemy->AddComponent<ChaseEnemy>();
			//chaseEnemy->AddComponent<EyeSearchRange>()->AddTarget(target);
			//chaseEnemy->AddComponent<TargetChase>();
			//player->AddComponent<PlayerMover>();

			//Instantiate<ChaseEnemyObject>()->GetComponent<EyeSearchRange>()->AddTarget(player);

			AddGameObject<DebugObject>();
		}
		catch (...) {
			throw;
		}
	}

	void MaruStage::OnUpdate() {
		
		//std::shared_ptr<BaseEnemy> enemy;
		//auto objs = GetGameObjectVec();
		//for (auto& obj : objs) {
		//	auto search = obj->GetComponent<SearchObject>(false);
		//	if (search) {
		//		auto size = search->GetSearchComponents<AstarCtrl>().size();
		//		DebugObject::sm_wss << to_wstring(size);
		//	}
		//	auto ene = obj->GetComponent<BaseEnemy>(false);
		//	if (ene) {
		//		enemy = ene;
		//	}
		//}

		//auto& key = App::GetApp()->GetMyInputDevice()->GetKeyBoard();
		//if (key.IsInputDown(itbs::Input::KeyCode::T)) {
		//	if (enemy) {
		//		//enemy->ChangeStateMachine<>
		//	}
		//}
	}

	void MaruStage::CreateGraphTest() {
		std::vector<std::shared_ptr<GameObject>> enemys;
		constexpr int EnemyNum = 0;
		for (int i = 0; i < EnemyNum; i++) {
			auto enemy = AddGameObject<MTestEnemyObject>();
			enemy->GetComponent<Transform>()->SetPosition(Vec3(-5.0f,0.0f,0.0f));
			auto col = enemy->GetComponent<CollisionObb>();
			//col->SetAfterCollision(AfterCollision::None);
			//col->AddExcludeCollisionTag(L"MTestEnemy");
			enemys.push_back(enemy);
		}

		SparseGraph<NavGraphNode, GraphEdge> graph(true);
		
		//データ構築
		std::vector<Vec3> poss = {
			{+0.0f ,+0.0f ,+0.0f},//0
			{+5.0f ,+0.0f ,+0.0f},
			{-5.0f ,+0.0f ,+0.0f},//2
			{-1.0f ,+5.0f ,+0.0f},
			{+0.0f ,-5.0f ,+0.0f},//4
			{+5.0f ,+5.0f ,+0.0f},
			{+10.0f ,+0.0f ,+0.0f},//6
			{+6.0f ,+4.0f ,+0.0f},
			{+2.0f ,+2.0f ,+0.0f},
		};

		int index = 0;
		for (auto pos : poss) {
			graph.AddNode(make_shared<NavGraphNode>(index++, pos));
		}
		
		//for (int i = 0; i < poss.size(); i++) {
		//	for (int j = 0; j < poss.size(); j++) {
		//		if (i == j) {
		//			continue;
		//		}
		//		graph.AddEdge(GraphEdge(i,j));
		//	}
		//}

		vector<GraphEdge> edges = {
			{GraphEdge(0,1)},
			{GraphEdge(0,2)},
			{GraphEdge(0,3)},
			{GraphEdge(0,4)},
			{GraphEdge(1,0)},
			{GraphEdge(2,0)},
			{GraphEdge(3,0)},
			{GraphEdge(4,0)},
			{GraphEdge(3,5)},
			//{GraphEdge(1,5)},

			{GraphEdge(1,6)},
			{GraphEdge(6,7)},
			{GraphEdge(7,5)},
			{GraphEdge(0,8)},
		};

		for (auto& edge : edges) {
			graph.AddEdge(edge);
		}

		auto astarTarget = AddGameObject<MTestEnemyObject>();
		astarTarget->GetComponent<Transform>()->SetPosition(Vec3(5.0f, +5.0f, 0.0f));

		//Astar生成
		//GraphAstar astar(graph);
		for (auto enemy : enemys) {
			//enemy->AddComponent<AstarCtrl>(astar)->SearchAstarStart(astarTarget);
		}
		
		//enemy->GetComponent<Transform>()->SetPosition(Vec3(-5.0f,0.0f,0.0f));


		//auto testObj = AddGameObject<MTestBox>();
		//testObj->AddComponent<PlayerMover>();
		//auto eyeRange = testObj->AddComponent<EyeSearchRange>();
		//eyeRange->AddTarget(enemys[0]);

		//auto testSearch = AddGameObject<GameObject>();
		//testSearch->GetComponent<Transform>()->SetScale(Vec3(3.0f));
		//testSearch->AddComponent<SearchObject>();
		//testSearch->SetParent(testObj);

		auto player = AddGameObject<MTestBox>();
		player->SetColor(Col4(0.0f, 1.0f, 0.0f, 1.0f));
		player->AddComponent<PlayerMover>();

		auto chaseEnemy = Instantiate<ChaseEnemyObject>();
		chaseEnemy->GetComponent<EyeSearchRange>()->AddTarget(player);
		//chaseEnemy->AddComponent<AstarCtrl>(astar);
		//chaseEnemy->AddComponent<EnemyEar>();
	}
}

//endbasecross
