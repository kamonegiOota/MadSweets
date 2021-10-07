/*!
@file MainCamera.cpp
@brief MainCamera�̃N���X����
�S���F�ێR�T��
*/

#include "stdafx.h"
#include "Project.h"
#include "LiveCamera.h"


namespace basecross {

	void LiveCamera::CreateParticle() {

	}

	void LiveCamera::CreateSuperChat() {

	}

	std::shared_ptr<GameStage> LiveCamera::GetGameStage() {
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

	void LiveCamera::EyeMove() {
		auto delta = App::GetApp()->GetElapsedTime();

		auto pos = GetEye();
		const auto& endPos = m_params[m_index].eye.endPos;
		const float speed = m_params[m_index].eye.speed;

		auto newPos = Lerp::CalculateLerp(pos, endPos, 0.0f, 1.0f, delta * speed, Lerp::rate::Linear);

		SetEye(newPos);
	}

	void LiveCamera::AtMove() {
		auto delta = App::GetApp()->GetElapsedTime();

		auto at = GetAt();
		const auto& endAt = m_params[m_index].at.endPos;
		const float speed = m_params[m_index].at.speed;

		auto newAt = Lerp::CalculateLerp(at, endAt, 0.0f, 1.0f, delta * speed, Lerp::rate::Linear);

		SetAt(newAt);
	}

	void LiveCamera::NextIndex() {
		m_timeElapsed = 0.0f;
		m_index++;  //�C���f�b�N�X���C���N�������g

		if (IsEnd()) {  //��������
			EndProcess();
			ChangeCamera();
		}
		else {
			SetEye(m_params[m_index].eye.startPos);
			SetAt(m_params[m_index].at.startPos);
			PlayAnimation();

			if (m_params[m_index].isParticle) {
				//�p�[�e�B�N���̐���
				CreateParticle();
			}
		}
	}

	void LiveCamera::PlayAnimation() {

	}

	//�^�[�Q�b�g���X�e�[�W�̐��ʂ̕���������
	void LiveCamera::TargetLookForward() {

	}

	void LiveCamera::EndProcess() {

	}

	void LiveCamera::ChangeCamera() {

	}

	void LiveCamera::AnimationWait() {

	}

	void LiveCamera::TimeMgr() {
		auto delta = App::GetApp()->GetElapsedTime();

		if (m_params[m_index].lookTime == 0.0f) {
			AnimationWait();
			return;
		}

		m_timeElapsed += delta;
		if (m_timeElapsed >= m_params[m_index].lookTime)  //���Ԃ��o�߂�����
		{
			NextIndex();
		}
	}

	void LiveCamera::OnUpdate()
	{
		//�I���̂��m�点
		if (m_params.size() <= m_index) {
			return;
		}

		AtMove();
		EyeMove();

		TimeMgr();  //���ԊǗ�

	}

	void LiveCamera::LiveStart(const vector<LiveParam>& params, const std::shared_ptr<GameObject>& targetArea) {
		m_params = params;
		m_targetArea = targetArea;
		SetEye(m_params[m_index].eye.startPos);
		SetAt(m_params[m_index].at.startPos);
		PlayAnimation();
	}

}

//endbasecross