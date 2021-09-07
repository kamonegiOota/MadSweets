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

	//�T������Astar�𗘗p���Ĉړ����������̃R���|�[�l���g
	class ProbeAstarMove : public Component , public BaseUseVelocity
	{
		bool m_isProbeEnd = false;

		int m_numLostChase = 7;  //LostMove�������
		int m_numLostChaseElapsed = m_numLostChase;
		float m_targetNearRange = 1.5f;  //�^�[�Q�b�g�̏ꏊ�ɋ߂��Ɣ��f����钷��

		ex_weak_ptr<GameObject> m_target;
		Vec3 m_targetPosition = Vec3(0.0f);

		bool IsRouteEnd();

		void Rotation(const Vec3& moveVec);
		void ChangeTargetChase();

		void CalucRoute(const std::shared_ptr<GameObject>& target);
		void CalucNextRoute(const std::shared_ptr<GameObject>& target);

	public:

		ProbeAstarMove(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override{}
		void OnStart() override;
		void OnUpdate() override {}

		//Astar�𗘗p�����ړ�
		void Move();

		//�ړI�������������̏���
		void LostTarget(const std::shared_ptr<GameObject>& target);
		//���̃��[�g����������B
		void NextRoute();

		//�A�N�Z�b�T-----------------------------------------------------------

		bool IsProbeEnd() const {
		 	return m_isProbeEnd;
		}

		void SetNumLostCheck(const int& num) {
			m_numLostChase = num;
		}
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
		float GetTargetNearRange() const {
			return m_targetNearRange;
		}
	};

}

//endbasecross