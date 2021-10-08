/*!
@file MTestEnemyObject.h
@brief MTestEnemyObject
担当者：丸山 裕喜
*/


#pragma once

#include "stdafx.h"
#include "Project.h"

#include "GraphAstar.h"
#include "StageMapCSV.h"

namespace basecross {

	class WallEvasion;
	class PlowlingMove;
	class EyeSearchRange;
	class BaseEnemy;

	class EnemyGenerator : public Component
	{
		std::weak_ptr<StageMapCSV> m_csvMap;
		std::weak_ptr<GameObject> m_player;

		/// <summary>
		/// Astarの生成
		/// </summary>
		/// <param name="fileName">ステージの名前</param>
		/// <returns>生成したAstarを渡す</returns>
		GraphAstar CreateAstar(const wstring& fileName);

		/// <summary>
		/// 敵の生成
		/// </summary>
		template<class T>
		void CreateEnemy(const wstring& fileName, const GraphAstar& astar, const vector<Vec3>& positions) {
			auto player = m_player.lock();

			auto enemy = GetStage()->Instantiate<T>(Vec3(0.0f, 0.0f, 0.0f), Quat::Identity());
			enemy->GetComponent<BaseEnemy>()->SetMapType(fileName);
			enemy->AddComponent<AstarCtrl>(astar);
			enemy->GetComponent<EyeSearchRange>()->AddTarget(player);

			auto wallEvasion = enemy->GetComponent<WallEvasion>();
			if (wallEvasion) {
				for (auto& obj : GetStage()->GetGameObjectVec()) {
					auto stageObj = dynamic_pointer_cast<StageObject>(obj);
					if (stageObj) {
						wallEvasion->AddObstacleObjs(stageObj);
					}
				}
			}

			auto plow = enemy->GetComponent<PlowlingMove>(false);
			if (plow) {
				plow->SetPositions(positions);
			}

			enemy->GetComponent<Transform>()->SetPosition(positions[0]);
		}

	public:
		EnemyGenerator(const std::shared_ptr<GameObject>& objPtr,
			const std::shared_ptr<StageMapCSV>& csvMap
		) :
			Component(objPtr),m_csvMap(csvMap)
		{}

		void OnCreate() {}
		void OnUpdate() {}

		void Generate(const wstring& fileName);
	};

}

//endbasecross