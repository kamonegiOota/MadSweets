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

			AddGameObject<DebugObject>();
		}
		catch (...) {
			throw;
		}
	}

	void MaruStage::CreateGraphTest() {
		auto enemy = AddGameObject<MTestEnemyObject>();

		SparseGraph<NavGraphNode, GraphEdge> graph(true);
		
		//データ構築
		std::vector<Vec3> poss = {
			{+0.0f ,+0.0f ,+0.0f},
			{+5.0f ,+0.0f ,+0.0f},
			{-5.0f ,+0.0f ,+0.0f},
			{+0.0f ,+5.0f ,+0.0f},
			{+0.0f ,-5.0f ,+0.0f},
			{+5.0f ,+6.0f ,+0.0f},
		};

		int index = 0;
		for (auto pos : poss) {
			graph.AddNode(NavGraphNode(index++, pos));
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
		};

		for (auto& edge : edges) {
			graph.AddEdge(edge);
		}

		//Astar生成
		GraphAstar astar(graph);
		enemy->AddComponent<AstarCtrl>(astar);
		//enemy->GetComponent<Transform>()->SetPosition(Vec3(-5.0f,0.0f,0.0f));
	}
}

//endbasecross
