/*!
@file MainCamera.cpp
@brief MainCamera�̃N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"

#include "AlphaFadeCtrl.h"

#include "StartCamera.h"
#include "Mathf.h"

#include "MainStage.h"
#include "Lock.h"
#include "MyUtility.h"

#include "PlayerInputer.h"

namespace basecross {

	std::shared_ptr<GameStage> StartCamera::GetGameStage() {
		auto& app = App::GetApp(); // �A�v���P�[�V�����I�u�W�F�N�g���擾
		auto scene = app->GetScene<Scene>(); // �A�v���I�u�W�F����V�[�����擾
		auto stage = dynamic_pointer_cast<GameStage>(scene->GetActiveStage());

		if (stage) {
			return stage;
		}
		else {
			return nullptr;
		}
	}

	void StartCamera::PlayAnimation() {
		auto stage = GetStage<GameStage>();
		if (!stage) {
			return;
		}

		if (m_index == m_params.size() - 1) {  //�����Ō�̃C���f�b�N�X��������
			//auto player = stage->GetPlayer();
			//auto anime = player->GetComponent<PlayerAnimationCtrl>(false);
			//if (anime) {  //�A�j���[�V�������擾�ł�����B
			//	anime->ChangeAnimation(L"LookOut");
			//}
		}
	}

	void StartCamera::StartLock(const bool b, const std::shared_ptr<Stage>& stage) {
		auto player = MyUtility::GetGameObject<PlayerObject>(stage);
		if (!player) {
			return;
		}
		
		auto lock = player->GetComponent<LockPlayer>(false);
		if (lock) {
			lock->SetPlayerOperationActive(!b);
		}
	}

	void StartCamera::FadeStart() {
		auto stage = GetGameStage();
		if (!stage) {
			return;
		}

		//�t�F�[�h�̎���
		auto fadeCtrl = stage->Instantiate<GameObject>()->AddComponent<AlphaFadeCtrl>();
		fadeCtrl->SetSpeed(1.0f);
		fadeCtrl->AddEndAction(GetThis<StartCamera>(), &StartCamera::ChangeCamera);
		fadeCtrl->AddEndAction(fadeCtrl, &AlphaFadeCtrl::FadeInStart);
		fadeCtrl->FadeOutStart();

		m_fadeCtrl = fadeCtrl;
	}

	void StartCamera::OnCreate()
	{
		if (m_params.size() == 0) {
			ChangeCamera();
			return;
		}

		SetAt(m_params[m_index].at.startPos);
		SetEye(m_params[m_index].eye.startPos);
	}

	void StartCamera::OnUpdate()
	{
		if (m_params.size() == 0) {
			ChangeCamera();
			return;
		}

		//�I���̂��m�点
		if (m_params.size() <= m_index) {
			return; //�I��
		}

		Skip();
		
		auto delta = App::GetApp()->GetElapsedTime();

		EyeMove();
		AtMove();
		
		m_timeElapsed += delta;
		if (m_timeElapsed >= m_params[m_index].lookTime)
		{
			m_timeElapsed = 0.0f;
			m_index++;
			if (IsEnd()) {  //�I����������
				FadeStart();
				//ChangeCamera();
			}
			else {
				PlayAnimation();
				SetEye(m_params[m_index].eye.startPos);
				SetAt(m_params[m_index].at.startPos);
			}
		}

	}

	void StartCamera::Start(const std::shared_ptr<Stage>& stage) {
		StartLock(true, stage);
	}

	void StartCamera::EyeMove()
	{
		auto delta = App::GetApp()->GetElapsedTime();

		auto pos = GetEye();
		const auto& endPos = m_params[m_index].eye.endPos;
		const float speed = m_params[m_index].eye.speed;

		auto newPos = Lerp::CalculateLerp(pos, endPos, 0.0f, 1.0f, delta * speed, Lerp::rate::Linear);

		SetEye(newPos);
	}


	void StartCamera::AtMove()
	{
		auto delta = App::GetApp()->GetElapsedTime();

		auto at = GetAt();
		const auto& endAt = m_params[m_index].at.endPos;
		const float speed = m_params[m_index].at.speed;

		auto newAt = Lerp::CalculateLerp(at, endAt, 0.0f, 1.0f, delta * speed, Lerp::rate::Linear);

		SetAt(newAt);
	}

	void StartCamera::Skip(){
		if (PlayerInputer::IsDecision()) {
			ChangeCamera();
			//LockMove(false);
		}
	}

	void StartCamera::ChangeCamera() {
		//�I��,MainCamera�ɐ؂�ւ�
		auto& app = App::GetApp(); // �A�v���P�[�V�����I�u�W�F�N�g���擾
		auto scene = app->GetScene<Scene>(); // �A�v���I�u�W�F����V�[�����擾
		auto stage = dynamic_pointer_cast<MainStage>(scene->GetActiveStage()); // �V�[������X�e�[�W���擾����

		if (stage)
		{
			stage->ChangeMainCamera();
			StartLock(false, stage);

			//auto gameCtrl = stage->GetGameStateCtrl();
			//gameCtrl->ChangeState(GameState::Play);
		}
	}

}

//endbasecross