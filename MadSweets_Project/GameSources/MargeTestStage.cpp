
/*!
@file MargeTestStage.h
@brief MargeTestStage
�S���ҁF�ێR �T��
*/

#include "MargeTestStage.h"
#include "StageMapCSV.h"
#include "FixedBox.h"

#include "DebugObject.h"

#include "PlayerObject.h"
#include "GaugeUI.h"

#include "PositionDrawComp.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void MargeTestStage::CreateViewLight() {
		const Vec3 eye(0.0f, +15.0f, -30.0f);
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

	void MargeTestStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			TempLoad();
			CreateMap(L"TempStage.csv");

			//�Q�[�W�̐���
			auto gauge = Instantiate<GaugeUI>();
			auto rectTransform = gauge->GetComponent<RectTransform>();
			rectTransform->SetAnchor(AnchorType::LeftUp);

			//�v���C���[�̐���
			SetSharedGameObject(L"PlayerWeightGauge", gauge);
			auto player = Instantiate<PlayerObject>(Vec3(+12.0f, +1.0f, -12.0f),Quat());
			player->SetDrawActive(false);
			player->AddComponent<CollisionObb>();
			//�ꏊ��c�����邽�߂̏���
			player->AddComponent<PositionDrawComp>();

			AddGameObject<DebugObject>()->SetDrawLayer(100);
			DebugObject::sm_isResetDelta = true;
		}
		catch (...) {
			throw;
		}
	}

	void MargeTestStage::CreateMap(const wstring& fileName)
	{
		auto map = AddGameObject<StageMapCSV>(L"MapDatas/", fileName);

		map->CreateObject<FixedBox>(L"StageRotBox");
		map->CreateObject<FixedBox>(L"Plane");
	}

	void MargeTestStage::TempLoad() {
		std::wstring mediaDir = App::GetApp()->GetDataDirWString();
		auto& app = App::GetApp();

		std::wstring textureDir = mediaDir + L"Textures\\";
		app->RegisterTexture(L"WeightGaugeBackground", textureDir + L"WeightGaugeBackGround.png");
		app->RegisterTexture(L"WeightGaugeColor", textureDir + L"WeightGaugeColor.png");
		//���f��
		std::wstring modelDir = mediaDir + L"Models\\";
		auto modelMesh = MeshResource::CreateBoneModelMesh(
			modelDir + L"Player\\StandStay\\", L"PlayerStandStay.bmf");
		app->RegisterResource(L"PlayerStandStay", modelMesh);
		modelMesh = MeshResource::CreateBoneModelMesh(
			modelDir + L"Player\\CrouchStay\\", L"PlayerCrouchStay.bmf");
		app->RegisterResource(L"PlayerCrouchStay", modelMesh);
		modelMesh = MeshResource::CreateBoneModelMesh(
			modelDir + L"Player\\StandToCrouch\\", L"PlayerStandToCrouch.bmf");
		app->RegisterResource(L"PlayerStandToCrouch", modelMesh);
	}

	void MargeTestStage::CreateEnemy(const std::shared_ptr<GameObject>& player) {

	}
}

//endbasecross