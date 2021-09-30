/*!
@file ChaseAstarMove.h
@brief ChaseAstarMove
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"

#include "BaseUseVelocity.h"
#include "AstarCtrl.h"

namespace basecross {

	//�^�[�Q�b�g�Ǐ]����Astar�𗘗p���Ĉړ����������̃R���|�[�l���g
	class ChaseAstarMove : public Component , public BaseUseVelocity
	{
		bool m_isProbeEnd = false;

		int m_numLostChase = 1;  //LostMove�������
		int m_numLostChaseElapsed = m_numLostChase;
		float m_targetNearRange = 1.5f;  //�^�[�Q�b�g�̏ꏊ�ɋ߂��Ɣ��f����钷���B
		float m_lostSeekTime = 3.0f;     //�^�[�Q�b�g�Ƃ̊Ԃɏ�Q��������ꍇ�B

		ex_weak_ptr<GameObject> m_target;   //�^�[�Q�b�g�̃|�C���^
		Vec3 m_targetPosition = Vec3(0.0f); //���݌������Ă���ꏊ

		/// <summary>
		/// NumLostChaseElapsed�̃��Z�b�g
		/// </summary>
		void ResetNumLostChaseElapsed();

		/// <summary>
		/// �^�[�Q�b�g�̋߂��ɗ�����true��Ԃ�
		/// </summary>
		/// <returns>�^�[�Q�b�g�̋߂��Ȃ�true</returns>
		bool IsRouteEnd();

		/// <summary>
		/// �^�[�Q�b�g�Ɍ������ď�Q�������邩���f����B
		/// </summary>
		/// <param name="target">�^�[�Q�b�g</param>
		/// <returns>��Q��������Ȃ�true</returns>
		bool IsRayObstacle(const std::shared_ptr<GameObject>& target);
		/// <summary>
		/// �^�[�Q�b�g�Ɍ������ď�Q�������邩���f����B
		/// </summary>
		/// <param name="targetPosition">�^�[�Q�b�g�̃|�W�V����</param>
		/// <param name="excluteObjs">��Q������Ȃ��Ώ�</param>
		/// <returns>��Q��������Ȃ�true</returns>
		bool IsRayObstacle(const Vec3& targetPosition, vector<shared_ptr<GameObject>>& excluteObjs = vector<shared_ptr<GameObject>>());

		void Rotation(const Vec3& moveVec);

		/// <summary>
		/// ���[�g�̌���
		/// </summary>
		/// <param name="target">��������Ώ�</param>
		void CalcuRoute(const std::shared_ptr<GameObject>& target);
		/// <summary>
		/// ���ڈȍ~�Ƀ^�[�Q�b�g�̏ꏊ�𒲂ׂ鏈��
		/// </summary>
		/// <param name="target">�^�[�Q�b�g</param>
		void CalcuNextRoute(const std::shared_ptr<GameObject>& target);
		/// <summary>
		/// �ړ��̗͂��v�Z���ĕԂ�
		/// </summary>
		/// <param name="target">�ǂ�������Ώ�</param>
		/// <returns>�ړ��̗�</returns>
		Vec3 CalcuMoveForce(const std::shared_ptr<GameObject>& target);

		//�^�[�Q�b�g���X�g�܂ł̃J�E���g���X�^�[�g
		void LostTimerStart();
		//�^�[�Q�b�g���X�g��Ԃ̉���
		void LostTimerCancel();

	public:

		ChaseAstarMove(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override{}
		void OnStart() override;
		void OnUpdate() override {}

		/// <summary>
		/// �ړ�����
		/// </summary>
		void Move();

		/// <summary>
		/// �^�[�Q�b�g�����E����O�ꂽ���̏���
		/// </summary>
		/// <param name="target">�Ǐ]���̃^�[�Q�b�g</param>
		void LostTarget(const std::shared_ptr<GameObject>& target);
		/// <summary>
		/// ���̃��[�g����������B
		/// </summary>
		void NextRoute();

		//�A�N�Z�b�T-----------------------------------------------------------

		/// <summary>
		/// �T�����I�����Ă��邩�ǂ����𔻒f
		/// </summary>
		/// <returns>�I�����Ă�����true</returns>
		bool IsProbeEnd() const {
		 	return m_isProbeEnd;
		}

		/// <summary>
		/// �^�[�Q�b�g���������Ă��牽�񒲂ׂ邩���Z�b�g����
		/// </summary>
		/// <param name="num">�^�[�Q�b�g���������Ă��牽�񒲂ׂ邩</param>
		void SetNumLostCheck(const int& num) {
			m_numLostChase = num;
		}
		/// <summary>
		/// �^�[�Q�b�g���������Ă��牽�񒲂ׂ邩
		/// </summary>
		/// <returns>�^�[�Q�b�g���������Ă��牽�񒲂ׂ邩</returns>
		int GetNumLostCheck() const {
			return m_numLostChase;
		}

		/// <summary>
		/// �ړI�̏ꏊ�ɋ߂��Ɣ��f����鋗���̃Z�b�g
		/// </summary>
		/// <param name="range">�ړI�̏ꏊ�ɋ߂��Ɣ��f����鋗��</param>
		void SetTargetNearRange(const float& range) {
			m_targetNearRange = range;
		}
		/// <summary>
		/// �ړI�̏ꏊ�ɋ߂��Ɣ��f����鋗��
		/// </summary>
		/// <returns>�ړI�̏ꏊ�ɋ߂��Ɣ��f����鋗��</returns>
		float GetTargetNearRange() const {
			return m_targetNearRange;
		}
	};

}

//endbasecross