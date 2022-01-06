/*!
@file EnemyGenerator.h
@brief EnemyGenerator
’S“–ÒFŠÛR —TŠì
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
		/// Astar‚Ì¶¬
		/// </summary>
		/// <param name="fileName">ƒXƒe[ƒW‚Ì–¼‘O</param>
		/// <returns>¶¬‚µ‚½Astar‚ğ“n‚·</returns>
		GraphAstar CreateAstar(const wstring& fileName);

		/// <summary>
		/// “G‚Ì¶¬
		/// </summary>
		template<class T,
			enable_if_t<is_base_of_v<GameObject, T>, std::nullptr_t> = nullptr >
		void CreateEnemy(const wstring& fileName, const GraphAstar& astar, const vector<Vec3>& positions) {
			auto player = m_player.lock();

			auto enemy = GetStage()->Instantiate<T>(Vec3(0.0f, 0.0f, 0.0f), Quat::Identity());
			enemy->GetComponent<BaseEnemy>()->SetMapType(fileName);
			enemy->AddComponent<AstarCtrl>(astar);
			enemy->GetComponent<EyeSearchRange>()->AddTarget(player);

			auto wallEvasion = enemy->GetComponent<WallEvasion>(false);
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

			AdjustCreateEnemy(enemy);
		}

		void AdjustCreateEnemy(const std::shared_ptr<GameObject>& enemy);

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