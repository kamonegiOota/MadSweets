/*!
@file MargeTestStage.h
@brief MargeTestStage
�S���ҁF�ێR �T��
*/

#pragma once

#include "AlphaFadeCtrl.h"
#include "StageMapCSV.h"

#include "GraphAstar.h"
#include "PlayerObject.h"
#include "PlowlingMove.h"

namespace basecross {

	class MargeTestStage : public Stage
	{
		
		static wstring sm_nowMap;
		static Vec3 sm_firstCreatePlayerPosition;
		static Vec3 sm_createPlayerPosition;
		static Vec3 sm_cretaePlayerForward;

		ex_weak_ptr<StageMapCSV> m_mapCsv;
		std::shared_ptr<PlayerObject> m_player;

		//�r���[�̍쐬
		void CreateViewLight();

		virtual void CreateMap(const wstring& fileName, const Vec3& offset = Vec3(0.0f));
		virtual GraphAstar CreateAstar(const wstring& fileName);

		template<class T>
		void CreateEnemy(const wstring& fileName, const GraphAstar& astar, const vector<Vec3>& positions) {
			auto enemy = Instantiate<T>(Vec3(0.0f, 0.0f, 0.0f), Quat::Identity());
			enemy->GetComponent<BaseEnemy>()->SetMapType(fileName);
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

			auto plow = enemy->GetComponent<PlowlingMove>(false);
			if (plow) {
				plow->SetPositions(positions);
			}
		}

	public:
		//�\�z�Ɣj��
		MargeTestStage() :Stage() {}
		virtual ~MargeTestStage() {}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//�X�e�[�W�̕ύX
		virtual void ChangeMap(const wstring& fileName,const std::shared_ptr<AlphaFadeCtrl>& fade, const Vec3& offset = Vec3(0.0f));

		//�e�X�g�p-----------------------------------------------------------
		virtual void TempLoad();
		void CreateEnemy(const std::shared_ptr<GameObject>& player);
		void CreateEatItems();
		void CreatePointLight();
		void CreateSoundCookies();
		void CreateCrackCookies();
		void CreateHideObjects();

		static void SetMapName(const wstring& name) {
			sm_nowMap = name;
		}
		static void SetCreatePlayerPosition(const Vec3& position) {
			sm_createPlayerPosition = position;
		}
	};

}

//endbasecross