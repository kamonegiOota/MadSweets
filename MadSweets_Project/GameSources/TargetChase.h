
/*!
@file TargetChase.h
@brief TargetChase
�S���ҁF�ێR �T��
*/

#pragma once

#include "TargetMgr.h"

namespace basecross {

	//�ݒ肳�ꂽ�^�[�Q�b�g��Ǐ]���鏈��
	class TargetChase : public Component
	{
		enum class ChaseMode {
			Look,  //���F�ł��Ă�����
			Lost   //���F�ł��ĂȂ����
		};

		ex_weak_ptr<GameObject> m_target;
		ChaseMode m_chaseMode = ChaseMode::Look;
		float m_maxSpeed = 10.0f;

		std::function<void(TargetChase&)> m_updateFunc;

		bool m_isEnd = false;

		/// <summary>
		/// ���E�̐�ɉB���I�u�W�F�N�g�������āA������target���B��Ă����炻����^�[�Q�b�g�ɂ���B
		/// </summary>
		/// <returns>���E�̐�ɉB���I�u�W�F�N�g�������true</returns>
		bool TargetEyeRangeHide();
		/// <summary>
		/// �^�[�Q�b�g������������
		/// </summary>
		void LostTarget();  
		/// <summary>
		/// �^�[�Q�b�g����������
		/// </summary>
		void FindTarget();

		/// <summary>
		/// ���E�̒��Ƀ^�[�Q�b�g�����鎞�̈ړ�
		/// </summary>
		void LookMove();
		/// <summary>
		/// ���E�̊O�Ƀ^�[�Q�b�g�����鎞�̈ړ�
		/// </summary>
		void LostMove();

		/// <summary>
		/// ���E���ɂ��邩�`�F�b�N���A����ɍ��킹�ď�Ԃ�ς���B
		/// </summary>
		void LookCheck();

		void Rotation(const Vec3& moveVec);

		void ChangeStateMachine();

	public:
		TargetChase(const std::shared_ptr<GameObject>& objPtr);

		TargetChase(const std::shared_ptr<GameObject>& objPtr, const float& speed);

		void OnCreate() override;
		void OnUpdate() override;
		void OnDraw() override {}

		/// <summary>
		/// �ǂ������̊J�n
		/// </summary>
		void ChaseStart() {
			m_isEnd = false;
			m_chaseMode = ChaseMode::Look;
			m_updateFunc = &TargetChase::LookMove;
			
			auto targetMgr = GetGameObject()->GetComponent<TargetMgr>(false);
			if (targetMgr) {
				m_target = targetMgr->GetTarget();
			}
		}

		//�A�N�Z�b�T-----------------------------------------------------------------------

		void SetTarget(const std::shared_ptr<GameObject>& target) {
			m_target = target;
		}
		std::shared_ptr<GameObject> GetTarget() const {
			return m_target.GetShard();
		}

		void SetMaxSpeed(const float& speed) {
			m_maxSpeed = speed;
		}
		float GetMaxSpeed() const {
			return m_maxSpeed;
		}

		bool IsEnd() {
			return m_isEnd;
		}

	};

}

//endbasecross