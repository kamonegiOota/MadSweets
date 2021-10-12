/*!
@file MainStage.h
@brief MainStage
�S���ҁF�ێR �T��
*/

#pragma once

#include "AlphaFadeCtrl.h"
#include "StageMapCSV.h"

#include "GraphAstar.h"
#include "PlayerObject.h"
#include "PlowlingMove.h"
#include "WeightGaugeCtrl.h"

#include "StartCamera.h"

namespace basecross {

	class MainStage : public GameStage
	{
		static wstring sm_nowMap;
		static Vec3 sm_firstCreatePlayerPosition;
		static Vec3 sm_createPlayerPosition;
		static Vec3 sm_cretaePlayerForward;

		ex_weak_ptr<StageMapCSV> m_mapCsv;
		ex_weak_ptr<PlayerObject> m_player;

		std::shared_ptr<SingleView> m_startView;
		std::shared_ptr<StartCamera> m_startCamera;

		std::shared_ptr<SingleView> m_mainView;
		std::shared_ptr<Camera> m_mainCamera;

		//�Z�[�u���ꂽ�p�����[�^�̃Z�b�g
		void SavingValueSet(const std::shared_ptr<PlayerObject> player, const std::shared_ptr<WeightGaugeCtrl>& weight);  

		//�r���[�̍쐬
		void CreateStartCamera();
		void CreateMainCamera();
		void CreateViewLight();
		void CreatePlayer(const std::shared_ptr<WeightGaugeCtrl>& weightGauge);

		virtual void CreateMap(const wstring& fileName, const Vec3& offset = Vec3(0.0f));

		void GoClearStage();

	public:
		//�\�z�Ɣj��
		MainStage() :GameStage() {}
		virtual ~MainStage() {}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//�X�e�[�W�̕ύX
		virtual void ChangeMap(const wstring& fileName,const std::shared_ptr<AlphaFadeCtrl>& fade, const Vec3& offset = Vec3(0.0f));

		static void SetMapName(const wstring& name) {
			sm_nowMap = name;
		}

		static void SetCreatePlayerPosition(const Vec3& position) {
			sm_createPlayerPosition = position;
		}

		//�J�����֌W-----------------------------------------------------------------

		std::shared_ptr<StartCamera> ChangeStartCamera()
		{
			auto camera = m_startView->GetCamera();
			SetView(m_startView);

			auto startCamera = dynamic_pointer_cast<StartCamera>(camera);
			if (startCamera) {
				startCamera->Start(GetThis<Stage>());
			}
			return startCamera;
		}

		std::shared_ptr<Camera> ChangeMainCamera()
		{
			auto camera = m_mainView->GetCamera();
			SetView(m_mainView);

			return camera;
		}
	};

}

//endbasecross