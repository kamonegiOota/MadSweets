#include"PlayerObject.h"
#include"PlayerInputer.h"
#include"PlayerMover.h"
#include"PlayerProvider.h"
#include"PlayerCameraObject.h"
#include"PlayerStanceManager.h"
#include"AnimationHelper.h"
#include"PlayerWeightManager.h"
#include"PlayerChoicesManager.h"
#include"SpringArmComponent.h"
#include"PlayerCameraMover.h"
#include"ChasingTarget.h"
#include"SoundHelper.h"
#include"PlayerHideManager.h"
#include"CameraHelper.h"
#include"PlayerDebuger.h"
#include"PlayerRotater.h"
#include"CameraRotater.h"
#include"PlayerSounder.h"
#include"DebugCameraObject.h"

//�ێR�ǋL���C���N���[�h
#include "PlayerStatusMgr.h"
#include "TimerDamage.h"
#include "StomachSound.h"
#include "PulledSweets.h"
#include "HungerCompCtrl.h"
#include "HpDrawMgr.h"

#include "PlayerWeightMgr.h"

namespace basecross
{
	PlayerObject::PlayerObject(std::shared_ptr<Stage>& stage) :
		GameObject(stage)
	{

	}

	void PlayerObject::OnCreate()
	{
		auto fpsCamera = GetStage()->Instantiate<GameObject>(Vec3(), Quat::Identity(), GetThis<GameObject>());
		fpsCamera->GetComponent<Transform>()->SetRotation(Vec3(XM_PIDIV4 / 4, XM_PIDIV4, 0));
		//auto fpsCameraComponent = fpsCamera->AddComponent<CameraComponent>();
		auto virtualCamera = fpsCamera->AddComponent<VirtualCamera>(10);
		auto cameraRotater = fpsCamera->AddComponent<CameraRotater>();
		cameraRotater->SetMinRotX(-XM_PIDIV4);
		cameraRotater->SetMaxRotX(XM_PIDIV4);

		auto springArm = GetStage()->Instantiate<GameObject>(Vec3(), Quat());

		m_springArm = springArm;

		auto chasingTarget = springArm->AddComponent<ChasingTarget>();
		chasingTarget->SetTarget(GetThis<GameObject>());
		auto cameraMover = springArm->AddComponent<PlayerCameraMover>();
		cameraMover->SetMinRotX(-XM_PIDIV4);
		cameraMover->SetMaxRotX(XM_PIDIV4);
		auto springArmComponent = springArm->AddComponent<SpringArmComponent>();

		Quat quat = Quat::Identity();
		quat.rotationY(XM_PI);
		auto tpsCamera = GetStage()->Instantiate<DebugCameraObject>(Vec3(0, 0, 3), quat, springArm);
		//auto tpsCameraComponent = tpsCamera->AddComponent<CameraComponent>();

		springArmComponent->SetChildObject(tpsCamera);
		springArmComponent->AddHitTag(L"Wall");

		auto draw = AddComponent<PNTBoneModelDraw>();

		AddComponent<Animator<PlayerAnimationMember, PlayerState>>();


		auto playerMover = AddComponent<PlayerMover>();
		playerMover->SetIsCameraAffected(true);
		AddComponent<PlayerProvider>();
		AddComponent<PlayerStanceManager>();

		AddComponent<PlayerRotater>();

		AddComponent<CollisionCapsule>();

		auto weightManager = AddComponent<PlayerWeightManager>();
		weightManager->SetGaugeManager(GetStage()->GetSharedGameObject<GameObject>(L"PlayerWeightGauge")->GetComponent<GaugeManager>());

		AddComponent<PlayerSounder>();

		CreateAnimator();

		AddComponent<SoundListener>();

		auto choiceManager = AddComponent<PlayerChoicesManager>();
		choiceManager->SetSearchRange(2.0f);

		AddComponent<PlayerHideManager>();

		//auto gameobj = GetStage()->Instantiate<GameObject>(Vec3(), Quat(), GetThis<GameObject>());

		//auto trans = gameobj->GetComponent<Transform>();
		////trans->Rotate(0, 0, 0);
		//std::wstringstream wss;
		//auto rot = trans->GetForword();
		//wss << L"x : " << rot.x << L" y : " << rot.y << L" z : " << rot.z;
		//MessageBox(0, wss.str().c_str(), L"�t�H���[�h", 0);

		//AddComponent<PlayerDebuger>(fpsCameraComponent, tpsCameraComponent,GetThis<PlayerObject>());


		//�ێR�ǋL��
		AddComponent<PlayerStatusMgr>();  //�X�e�[�^�X�Ǘ��R���|�[�l���g
		AddComponent<TimerDamage>()->SetUpdateActive(false);  //�Q���Ԃň�莞�Ԃ��ƂɃ_���[�W���󂯂鏈��
		AddComponent<StomachSound>()->SetUpdateActive(false); //�Q���Ԃň�莞�Ԃ��Ƃɕ��̉����Ȃ鏈���B
		AddComponent<PulledSweets>()->SetUpdateActive(false); //�Q���Ԃł��َq�̕����Ɉ��������鏈��
		AddComponent<HungerCompCtrl>();
		
		AddComponent<HpDrawMgr>();

		AddComponent<PlayerWeightMgr>();
		
	}

	void PlayerObject::OnUpdate()
	{
		GameObject::OnUpdate();
	}

	void PlayerObject::CreateAnimator()
	{
		auto animator = GetComponent<Animator<PlayerAnimationMember, PlayerState>>();

		auto stateMachine = animator->CreateAnimationStateMchine();

		auto state = stateMachine->CreateAnimationState(PlayerState::StandStay, L"PlayerStandStay", 30, true);

		state->AddTransition([](const PlayerAnimationMember& member) {return member.changeStance.Get(); }, PlayerState::StandToCrouch, false);

		state->AddTransition([](const PlayerAnimationMember& member) {return member.moveSpeed > 0.01f; }, PlayerState::StandMove, false);

		auto mover = GetComponent<PlayerMover>();

		state->AddEntryEvent([mover]() {mover->SetMoveSpeed(3.0f); });
		//state->AddExitEvent([mover]() {mover->SetUpdateActive(false); });

		state = stateMachine->CreateAnimationState(PlayerState::StandToCrouch, L"PlayerStandToCrouch", 5, false);

		state->AddTransition([](const PlayerAnimationMember& member) {return true; }, PlayerState::CrouchStay, true);

		state = stateMachine->CreateAnimationState(PlayerState::CrouchStay, L"PlayerCrouchStay", 30, true);

		state->AddEntryEvent([mover]() { mover->SetMoveSpeed(1.5f); });

		state->AddTransition([](const PlayerAnimationMember& member) {return member.changeStance.Get(); }, PlayerState::CrouchToStand, false);

		state->AddTransition([](const PlayerAnimationMember& member) {return PlayerInputer::IsDashPush(); }, PlayerState::CrouchToStand, false);

		state = stateMachine->CreateAnimationState(PlayerState::CrouchToStand, L"PlayerStandToCrouch", 5, false);

		state->AddTransition([](const PlayerAnimationMember& member) {return true; }, PlayerState::StandStay, true);

		state = stateMachine->CreateAnimationState(PlayerState::StandMove, L"PlayerStandStay", 30, true);

		state->AddAnimationEvent(0.25f, &PlayerSounder::PlayerWalk);
		state->AddAnimationEvent(0.75f, &PlayerSounder::PlayerWalk);

		state->AddTransition([](const PlayerAnimationMember& member) {return member.moveSpeed < 0.01f; }, PlayerState::StandStay, false);
	}
}