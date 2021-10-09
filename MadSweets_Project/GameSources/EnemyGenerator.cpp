/*!
@file MTestEnemyObject.h
@brief MTestEnemyObject
担当者：丸山 裕喜
*/


#pragma once

#include "stdafx.h"
#include "Project.h"

#include "BaseEnemy.h"
#include "EyeSearchRange.h"
#include "WallEvasion.h"
#include "PlowlingMove.h"

#include "EnemyGenerator.h"
#include "MyUtility.h"
#include "PlayerObject.h"
#include "UtilityEnemy.h"
#include "AstarEdgeDraw.h"

//エネミーインクルード
#include "HandyObject.h"
#include "CaraObject.h"
#include "GraObject.h"

//test用
#include "NumbersObject.h"
#include "NumbersCtrl.h"

namespace basecross {

	GraphAstar EnemyGenerator::CreateAstar(const wstring& fileName) {
		auto csvMap = m_csvMap.lock();
		auto player = m_player.lock();

		auto graph = make_shared<SparseGraph<NavGraphNode, GraphEdge>>(true);
		vector<std::shared_ptr<GameObject>> obstacleObjs;
		vector<std::shared_ptr<GameObject>> excluteObjs;

		for (auto& obj : GetStage()->GetGameObjectVec()) {
			auto stageObj = dynamic_pointer_cast<StageObject>(obj);
			if (stageObj) {
				obstacleObjs.push_back(stageObj);
			}
		}

		excluteObjs.push_back(player);

		int index = 0;
		auto positions = csvMap->GetPositions(L"Capsule");
		for (const auto& pos : positions) {
			graph->AddNode(make_shared<NavGraphNode>(index++, pos));
			//ノードの表示
			auto numberObj = GetStage()->Instantiate<NumbersObject>(pos, Quat::Identity());
			numberObj->GetComponent<NumbersCtrl>()->SetValue(index - 1);
		}

		//手動で設定したノード
		auto edges = StageMapCSV::sm_astarEdges[fileName];
		for (auto& edge : edges) {
			graph->AddEdge(edge);
		}

		auto astar = GraphAstar(graph);

		return astar;
	}

	void EnemyGenerator::Generate(const wstring& fileName) {
		m_player = MyUtility::GetGameObject<PlayerObject>(GetStage());

		auto astar = CreateAstar(fileName);
		auto csvMap = m_csvMap.lock();
		
		//エネミーの生成
		auto params = UtilityEnemy::sm_enemyParam[fileName];
		for (auto& param : params) {
			switch (param.type)
			{
			case UtilityEnemy::EnemyType::Handy:
				param.plowPositions = csvMap->GetPositions(L"HandyPlowling");
				CreateEnemy<HandyObject>(fileName, astar, param.plowPositions);
				break;
			case UtilityEnemy::EnemyType::Cara:
				param.plowPositions = csvMap->GetPositions(L"CaraPlowling");
				CreateEnemy<CaraObject>(fileName, astar, param.plowPositions);
				//CreateEnemy<HandyObject>(fileName, astar, param.plowPositions);
				break;
			case UtilityEnemy::EnemyType::Gra:
				//CreateEnemy<GraObject>(fileName, astar, param.plowPositions);
				break;
			}
		}

		//test用
		//GetStage()->Instantiate<GameObject>()->AddComponent<AstarEdgeDraw>(astar);
	}

}

//endbasecross