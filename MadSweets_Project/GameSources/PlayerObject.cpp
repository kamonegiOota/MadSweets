#include"PlayerObject.h"
#include"PlayerInputer.h"
#include"PlayerMover.h"
#include"PlayerProvider.h"
#include"PlayerCameraObject.h"
#include"PlayerStanceManager.h"
#include"AnimationHelper.h"
#include"PlayerCalorieManager.h"
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
#include"PlayerOpenDoorManager.h"
#include"PlayerGameItemGetter.h"
#include"Lock.h"

//丸山追記分インクルード
#include "PlayerStatusManager.h"
#include "TimerDamage.h"
#include "StomachSound.h"
#include "PulledSweets.h"
#include "HungerCompCtrl.h"
#include "HpDrawManager.h"

#include "PlayerWeightManager.h"
#include "HitEffectManager.h"

namespace basecross
{
	PlayerObject::PlayerObject(std::shared_ptr<Stage>& stage) :
		GameObject(stage)
	{

	}

	void PlayerObject::OnCreate()
	{
		auto fpsCamera = GetStage()->Instantiate<GameObject>(Vec3(), Quat::Identity(), GetThis<GameObject>());
		auto virtualCamera = fpsCamera->AddComponent<VirtualCamera>(10);
		auto cameraRotater = fpsCamera->AddComponent<CameraRotater>();
		cameraRotater->SetMinRotX(-XM_PIDIV4);
		cameraRotater->SetMaxRotX(XM_PIDIV4);

		auto springArm = GetStage()->Instantiate<GameObject>(Vec3(), Quat());

		auto chasingTarget = springArm->AddComponent<ChasingTarget>();
		chasingTarget->SetTarget(GetThis<GameObject>());
		auto cameraMover = springArm->AddComponent<PlayerCameraMover>();
		cameraMover->SetMinRotX(-XM_PIDIV4);
		cameraMover->SetMaxRotX(XM_PIDIV4);
		auto springArmComponent = springArm->AddComponent<SpringArmComponent>();

		Quat quat = Quat::Identity();
		quat.rotationY(XM_PI);

		springArmComponent->AddHitTag(L"Wall");

		auto draw = AddComponent<PNTBoneModelDraw>();

		AddComponent<Animator<PlayerAnimationMember, PlayerState>>();


		auto playerMover = AddComponent<PlayerMover>();
		playerMover->SetIsCameraAffected(true);
		AddComponent<PlayerProvider>();
		AddComponent<PlayerStanceManager>();

		AddComponent<PlayerRotater>();

		AddComponent<CollisionCapsule>();

		auto calorieManager = AddComponent<PlayerCalorieManager>();
		calorieManager->SetGaugeManager(GetStage()->GetSharedGameObject<GameObject>(L"PlayerCalorieGauge")->GetComponent<GaugeManager>());

		AddComponent<PlayerSounder>();

		CreateAnimator();

		AddComponent<SoundListener>();

		auto choiceManager = AddComponent<PlayerChoicesManager>();
		choiceManager->SetSearchRange(2.0f);

		AddComponent<PlayerHideManager>();
		AddComponent<PlayerGameItemGetter>();
		AddComponent<PlayerOpenDoorManager>();

		AddComponent<LockPlayer>();

		//丸山追記文
		AddComponent<PlayerStatusManager>();  //ステータス管理コンポーネント
		AddComponent<TimerDamage>()->SetUpdateActive(false);  //飢餓状態で一定時間ごとにダメージを受ける処理
		AddComponent<StomachSound>()->SetUpdateActive(false); //飢餓状態で一定時間ごとに腹の音がなる処理。
		AddComponent<PulledSweets>()->SetUpdateActive(false); //飢餓状態でお菓子の方向に引っ張られる処理
		AddComponent<HungerCompCtrl>();

		auto hitEffectParam = HitEffectManager::Parametor(L"HitCream_Tx", Col4(0.9f, 0.85f, 0.65f, 0.0f), 0.5f, 0.8f);
		AddComponent<HitEffectManager>(hitEffectParam);
		
		AddComponent<HpDrawManager>();

		AddComponent<PlayerWeightManager>();
		
		AddComponent<Gravity>();


		//デバッグ用
		//AddComponent<PlayerDebuger>(fpsCameraComponent, tpsCameraComponent,GetThis<PlayerObject>());
		//auto tpsCamera = GetStage()->Instantiate<DebugCameraObject>(Vec3(0, 0, 3), quat, springArm);
		//springArmComponent->SetChildObject(tpsCamera);
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

		state->AddTransition([](const PlayerAnimationMember& member) {return member.moveSpeed > 0.01f; }, PlayerState::StandMove, false);

		auto mover = GetComponent<PlayerMover>();

		state->AddEntryEvent([mover]() {mover->SetMoveSpeed(3.0f); });

		state = stateMachine->CreateAnimationState(PlayerState::StandMove, L"PlayerStandStay", 30, true);

		state->AddAnimationEvent(0.25f, &PlayerSounder::PlayerWalk);
		state->AddAnimationEvent(0.75f, &PlayerSounder::PlayerWalk);

		state->AddTransition([](const PlayerAnimationMember& member) {return member.moveSpeed < 0.01f; }, PlayerState::StandStay, false);
	}
}