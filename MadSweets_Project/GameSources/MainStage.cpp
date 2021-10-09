
/*!
@file MainStage.h
@brief MainStage
�S���ҁF�ێR �T��
*/

#include "MainStage.h"
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

// �� �ǉ��� ----------------

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

#include "EnemyMainStateMachine.h"

#include "TestEnemyNode.h"

#include "EnemyGenerator.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------

	//wstring MainStage::sm_nowMap = L"TempStage.csv";
	wstring MainStage::sm_nowMap = L"Stage1.csv";
	Vec3 MainStage::sm_firstCreatePlayerPosition = Vec3(-21.0f, +1.0f, -21.0f);
	//Vec3 MainStage::sm_firstCreatePlayerPosition = Vec3(1.0f, +1.0f, 1.0f);
	Vec3 MainStage::sm_createPlayerPosition = sm_firstCreatePlayerPosition;
	Vec3 MainStage::sm_cretaePlayerForward = Vec3(1.0f, 0.0f, 0.0f);

	void MainStage::SavingValueSet(const std::shared_ptr<PlayerObject> player, const std::shared_ptr<WeightGaugeCtrl>& weight) {
		auto saveValue = LoadStageTrigger::GetSavingValue();
		if (saveValue.isActive == false) {
			//��������ꏊ�Ȃǂ������ʒu�ɕύX
			sm_nowMap = L"Stage1.csv";
			sm_createPlayerPosition = sm_firstCreatePlayerPosition;
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

	void MainStage::CreateStartCamera() {
		//StartCamera�̐ݒ�
		m_startView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		vector<StartCamera::ShowParam> params = {
			//startPos            //startLock          //endPos             //endLock                //time
			{
				//������
				LiveMoveParam(Vec3(2.0f,0.0f,0.0f),Vec3(+4.0f,+0.0f,+0.0f)),
				LiveMoveParam(Vec3(0.0f,0.0f,0.0f),Vec3(-3.0f,-3.0f,-3.0f)),
			},
		};
		auto startCam = ObjectFactory::Create<StartCamera>(params);
		m_startView->SetCamera(startCam);
	}

	void MainStage::CreateMainCamera() {
		const Vec3 eye(0.0f, +15.0f, -30.0f);
		const Vec3 at(0.0f);
		m_mainView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		m_mainCamera = ObjectFactory::Create<Camera>();
		m_mainView->SetCamera(m_mainCamera);
		m_mainCamera->SetEye(eye);
		m_mainCamera->SetAt(at);
	}

	void MainStage::CreateViewLight() {
		CreateStartCamera();
		CreateMainCamera();

		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
		//PtrMultiLight->SetAmbientLightColor(Col4(1.0f,0.1f,0.1f,0.1f));

		Vec3 poss[] = {
			{Vec3(0.0f,0.5f,0.0f)},
			{Vec3(0.0f,-0.5f,0.0f)},
			{Vec3(-0.5f,0.0f,0.0f)},
		};

		//���C�g�̐ݒ�
		for (int i = 0; i < 3; i++) {
			auto& light = PtrMultiLight->GetLight(i);
			light.m_DiffuseColor = Col4(0.35f);
			//light.m_Directional = Vec3(0.0f);
			light.m_SpecularColor = Col4(0.35f);
			//light.m_Directional = poss[i];
		}
	}

	void MainStage::CreatePlayer(const std::shared_ptr<WeightGaugeCtrl>& weightGauge) {
		auto player = Instantiate<PlayerObject>(sm_createPlayerPosition, Quat());
		player->GetComponent<Transform>()->SetForward(sm_cretaePlayerForward);
		sm_createPlayerPosition = sm_firstCreatePlayerPosition;
		player->AddComponent<PointLight>();
		player->SetDrawActive(false);
		m_player = player;
		SavingValueSet(player, weightGauge);
	}

	void MainStage::OnCreate() {
		try {
			AddGameObject<DebugObject>()->SetDrawLayer(100);
			//DebugObject::sm_isResetDelta = true;

			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			// �� �ǉ��� ---------------
			Instantiate<CameraObject>();
			Instantiate<GameMessageWindowObject>();
			// ---------------------------

			auto fade = Instantiate<AlphaFadeObject>()->GetComponent<AlphaFadeCtrl>();
			fade->FadeInStart();

			//�Q�[�W�̐���
			Instantiate<PlayerCalorieGaugeObject>();

			//UI����
			Instantiate<PlayerChoicesListObject>();

			//�E�F�C�g�Q�[�W�̐���
			auto weightGauge = Instantiate<WeightGaugeUI>()->GetComponent<WeightGaugeCtrl>();

			//�t�F�[�h�̐���
			auto fadeObject = Instantiate<UIObject>();
			fadeObject->SetDrawLayer(100000);
			auto alphaFade = fadeObject->AddComponent<AlphaFadeCtrl>();
			alphaFade->AddEndAction(GetThis<MainStage>(), &MainStage::GoClearStage);

			SetSharedGameObject(L"FinishFadeObject", fadeObject);

			//�v���C���[�̐���
			CreatePlayer(weightGauge);

			//�}�b�v�̐���
			CreateMap(sm_nowMap);
			//�G�̐���
			auto generator = Instantiate<GameObject>()->AddComponent<EnemyGenerator>(m_mapCsv.GetShard());
			generator->Generate(sm_nowMap);

			EventSystem::GetInstance(GetThis<Stage>())->SetBasicInputer(PlayerInputer::GetInstance());

			//�X�^�[�g���o�J�����̃X�^�[�g
			if (m_mapCsv->GetAdmissionCount(sm_nowMap) == 0) {
				ChangeStartCamera();
			}
			
		}
		catch (...) {
			throw;
		}
	}

	void MainStage::OnUpdate() {

	}

	void MainStage::GoClearStage()
	{
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<SceneBase>(), L"ToClearStage");
	}

	void MainStage::CreateMap(const wstring& fileName, const Vec3& offset)
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
		map->CreateObject<CookieHideObject>(L"Locker01", offset, false);
		map->CreateObject<LoadStageTriggerObject>(L"Trigger",offset, false);
		map->CreateObject<PointLightObject>(L"Light", offset);
		map->CreateObject<SoundCookieObject>(L"SoundCokie", offset);
		map->CreateObject<FixedBox>(L"Ceiling", offset);

		//eat�I�u�W�F�N�g
		auto positions = map->GetPositions(L"EatenObject");
		auto textures = map->GetTextures(L"EatenObject");
		for (int i = 0; i < positions.size() ; i++) {
			auto eatenObj = Instantiate<EatenObject>(positions[i], Quat::Identity());
			eatenObj->GetComponent<Transform>()->SetScale(Vec3(0.5f));
			eatenObj->SetTexture(textures[i]);
		}

		//���̃I�u�W�F�N�g
		positions = map->GetPositions(L"Key");
		for (auto& pos : positions) {
			Instantiate<GameItemKeyObject>(pos, Quat());
		}

		//��
		positions = map->GetPositions(L"Door");
		for (auto& pos : positions) {
			Instantiate<DoorObject>(pos, Quat());
		}

		m_mapCsv = map;
	}

	void MainStage::ChangeMap(const wstring& fileName, const std::shared_ptr<AlphaFadeCtrl>& fade, const Vec3& offset) {
		//�}�b�v���̐؂�ւ�
		bool isNewCreate = m_mapCsv->ChangeMap(fileName);
		if (isNewCreate) {
			CreateMap(fileName, offset);
		}

		//�G�̔z�u�̐؂�ւ�
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
				//enemy->ChangeStateMachine<EnState_Plowling>();
			}
		}
		
		//�t�F�[�h�C��
		fade->FadeInStart();
	}
}

//endbasecross




