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
#include "AshiObject.h"

#include "MyRandom.h"

//test用
#include "NumbersObject.h"
#include "NumbersCtrl.h"

namespace basecross {

	using maru::MyRandom;

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
			//auto numberObj = GetStage()->Instantiate<NumbersObject>(pos, Quat::Identity());
			//numberObj->GetComponent<NumbersCtrl>()->SetValue(index - 1);
		}

		//手動で設定したノード
		auto edges = StageMapCSV::sm_astarEdges[fileName];
		for (auto& edge : edges) {
			graph->AddEdge(edge);
		}

		auto astar = GraphAstar(graph);

		return astar;
	}

	void EnemyGenerator::AdjustCreateEnemy(const std::shared_ptr<GameObject>& enemy){
		//auto ashi = dynamic_pointer_cast<AshiObject>(enemy);
		//if (ashi) {
		//	auto eaten = ashi->GetComponent<EatenComponent>(false);
		//	if (eaten) {
		//		auto datas = eaten->GetDefaultEatenDatas();
		//		auto randIndex = MyRandom::Random(0, (int)datas.size());

		//		auto iter = datas.begin();
		//		std::advance(iter, randIndex); //イテレータを進める。

		//	    eaten->SetEatenData(datas[iter->first]);
		//	}
		//}
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
				param.plowPositions = csvMap->GetPositions(param.plowlingDataName);
				CreateEnemy<HandyObject>(fileName, astar, param.plowPositions);
				break;
			case UtilityEnemy::EnemyType::Cara:
				param.plowPositions = csvMap->GetPositions(param.plowlingDataName);
				CreateEnemy<CaraObject>(fileName, astar, param.plowPositions);
				//CreateEnemy<AshiObject>(fileName, astar, param.plowPositions);
				//CreateEnemy<HandyObject>(fileName, astar, param.plowPositions);
				break;
			case UtilityEnemy::EnemyType::Ashi:
				param.plowPositions = csvMap->GetPositions(param.plowlingDataName);
				CreateEnemy<AshiObject>(fileName, astar, param.plowPositions);
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