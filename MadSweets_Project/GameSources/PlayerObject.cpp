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
#include"ForwardLookAtCameraComponent.h"
#include"ChasingTarget.h"
#include"SoundHelper.h"
#include"PlayerHideManager.h"

#include<x3daudio.h>

//丸山追記分インクルード
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
		auto tpsCamera = GetStage()->Instantiate<GameObject>(Vec3(0, 0, 3), quat, springArm);
		tpsCamera->AddComponent<ForwardLookAtCameraComponent>();

		springArmComponent->SetChildObject(tpsCamera);
		springArmComponent->AddHitTag(L"Wall");

		auto draw = AddComponent<PNTBoneModelDraw>();

		AddComponent<Animator<PlayerAnimationMember, PlayerState>>();


		auto playerMover = AddComponent<PlayerMover>();
		playerMover->SetIsCameraAffected(true);
		AddComponent<PlayerProvider>();
		AddComponent<PlayerStanceManager>();

		AddComponent<CollisionCapsule>();

		auto weightManager = AddComponent<PlayerWeightManager>();
		weightManager->SetGaugeManager(GetStage()->GetSharedGameObject<GameObject>(L"PlayerWeightGauge")->GetComponent<GaugeManager>());


		CreateAnimator();

		AddComponent<SoundListener>();

		auto choiceManager = AddComponent<PlayerChoicesManager>();
		choiceManager->SetSearchRange(2.0f);

		AddComponent<PlayerHideManager>();


		//丸山追記文
		AddComponent<PlayerStatusMgr>();  //ステータス管理コンポーネント
		AddComponent<TimerDamage>()->SetUpdateActive(false);  //飢餓状態で一定時間ごとにダメージを受ける処理
		AddComponent<StomachSound>()->SetUpdateActive(false); //飢餓状態で一定時間ごとに腹の音がなる処理。
		AddComponent<PulledSweets>()->SetUpdateActive(false); //飢餓状態でお菓子の方向に引っ張られる処理
		AddComponent<HungerCompCtrl>();
		
		AddComponent<HpDrawMgr>();

		AddComponent<PlayerWeightMgr>();
		
	}

	void PlayerObject::OnUpdate()
	{
		GameObject::OnUpdate();

		static bool isTPS = true;
		if (!App::GetApp()->GetMyInputDevice()->GetXInputGamePad().IsInputDown(XInputCode::LeftThumb))
		{
			return;
		}

		auto springArm = m_springArm->GetComponent<SpringArmComponent>();
		if (isTPS)
		{
			springArm->SetArmRange(0);

			isTPS = false;
		}
		else
		{
			springArm->SetArmRange(10);

			isTPS = true;
		}
	}

	void PlayerObject::CreateAnimator()
	{
		auto animator = GetComponent<Animator<PlayerAnimationMember, PlayerState>>();

		auto stateMachine = animator->CreateAnimationStateMchine(GetComponent<PNTBoneModelDraw>());

		auto state = stateMachine->CreateAnimationState(PlayerState::StandStay, L"PlayerStandStay", 30, true);

		state->AddTransition([](const PlayerAnimationMember& member) {return member.changeStance.Get(); }, PlayerState::StandToCrouch, false);

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
	}
}