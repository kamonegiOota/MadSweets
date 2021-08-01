/*!
@file PlowlingMove.h
@brief PlowlingMove
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"
#include "AstarCtrl.h"

namespace basecross {

	/// <summary>
	/// �Œ�̃��[�g��p�j����R���|�[�l���g
	/// </summary>
	class PlowlingMove : public Component
	{
		//ex_weak_ptr<AstarCtrl> m_astar;

		/// <summary>
		/// �p�j����|�W�V����
		/// </summary>
		std::vector<Vec3> m_positions;

		int m_index;  //���݌������Ă���|�W�V�����̃C���f�b�N�X
		int m_addIndexDirect;  //�C���f�b�N�X�����������

		float m_maxSpeed = 2.0f;  //�ő�X�s�[�h��ݒ肷��AplowlingMove����
		float m_nearRange = 3.5f; //�߂��ɂ��邩�ǂ����̔��f������B

		/// <summary>
		/// ���̃|�W�V�����܂ł̃x�N�g�����v�Z���ĕԂ��B
		/// </summary>
		/// <returns>�v�Z�����x�N�g����Ԃ��B</returns>
		Vec3 CalucMoveVec();
		/// <summary>
		/// ���ۂ̈ړ�����
		/// </summary>
		void Move();
		void Rotation(const Vec3& moveVec);
		/// <summary>
		/// �ړI�n�Ɍ���Ȃ��߂��ꏊ�ɂ���Ȃ�true
		/// </summary>
		/// <param name="pos">���݂̃|�W�V����</param>
		/// <returns>�ړI�n�ɋ߂��ꍇtrue</returns>
		bool IsNearArrival(const Vec3& pos);
		/// <summary>
		/// ���̖ړI�n�̃C���f�b�N�X�ɐ؂�ւ��鏈��
		/// </summary>
		void NextIndex();

		//void RandomAstarMove();

	public:

		PlowlingMove(const std::shared_ptr<GameObject>& objPtr);
		PlowlingMove(const std::shared_ptr<GameObject>& objPtr,
			const std::vector<Vec3>& positions
		);
		PlowlingMove(const std::shared_ptr<GameObject>& objPtr,
			const std::vector<Vec3>& positions,
			const float& speed,
			const float& nearRange
		);
		
		void OnCreate() {}
		void OnStart();
		void OnUpdate();
		void OnDraw(){}
		
		//�A�N�Z�b�T----------------------------------------------
		void SetPositions(const std::vector<Vec3>& positions){
			m_positions = positions;
		}

		void AddPosition(const Vec3& position) {
			m_positions.push_back(position);
		}

		float GetMaxSpeed() const {
			return m_maxSpeed;
		}
		void SetMaxSpeed(const float& speed) {
			m_maxSpeed = speed;
		}

		float GetNearRange() const {
			return m_nearRange;
		}
		void SetNearRange(const float& nearRange) {
			m_nearRange = nearRange;
		}

		/// <summary>
		/// ���݌������Ă���|�W�V������Ԃ�
		/// </summary>
		/// <returns>���݌������Ă���|�W�V����</returns>
		Vec3 GetNowTargetPosition() const {
			return m_positions[m_index];
		}
	};

}

//endbasecross