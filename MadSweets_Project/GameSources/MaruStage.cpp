/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
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
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void MaruStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -15.0f);
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



	void MaruStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
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
		
		//�f�[�^�\�z
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

		//Astar����
		GraphAstar astar(graph);
		enemy->AddComponent<AstarCtrl>(astar);
		//enemy->GetComponent<Transform>()->SetPosition(Vec3(-5.0f,0.0f,0.0f));
	}
}

//endbasecross
