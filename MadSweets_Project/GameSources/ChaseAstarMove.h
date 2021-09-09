/*!
@file ReturnPlowlingPosition.h
@brief ReturnPlowlingPosition
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

		int m_numLostChase = 5;  //LostMove�������
		int m_numLostChaseElapsed = m_numLostChase;
		float m_targetNearRange = 1.5f;  //�^�[�Q�b�g�̏ꏊ�ɋ߂��Ɣ��f����钷��

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

		void Rotation(const Vec3& moveVec);

		/// <summary>
		/// ���[�g�̌���
		/// </summary>
		/// <param name="target">��������Ώ�</param>
		void CalucRoute(const std::shared_ptr<GameObject>& target);
		/// <summary>
		/// ���ڈȍ~�Ƀ^�[�Q�b�g�̏ꏊ�𒲂ׂ鏈��
		/// </summary>
		/// <param name="target">�^�[�Q�b�g</param>
		void CalucNextRoute(const std::shared_ptr<GameObject>& target);

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