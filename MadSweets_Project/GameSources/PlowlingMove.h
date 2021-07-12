/*!
@file BaseEnemy.cpp
@brief BaseEnemy����
�S���ҁF�ێR �T��
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	/// <summary>
	/// �Œ�̃��[�g��p�j����R���|�[�l���g
	/// </summary>
	class PlowlingMove : public Component
	{
		/// <summary>
		/// �p�j����|�W�V����
		/// </summary>
		std::vector<Vec3> m_positions;

		int m_index;  //���݌������Ă���|�W�V�����̃C���f�b�N�X
		int m_addIndexDirect;  //�C���f�b�N�X�����������

		float m_speed;

		/// <summary>
		/// ���̃|�W�V�����܂ł̃x�N�g�����v�Z���ĕԂ��B
		/// </summary>
		/// <returns>�v�Z�����x�N�g����Ԃ��B</returns>
		Vec3 CalucMoveVec();
		/// <summary>
		/// ���ۂ̈ړ�����
		/// </summary>
		void Move();
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

	public:

		PlowlingMove(const std::shared_ptr<GameObject>& objPtr);
		PlowlingMove(const std::shared_ptr<GameObject>& objPtr,
			const std::vector<Vec3>& positions
		);
		PlowlingMove(const std::shared_ptr<GameObject>& objPtr,
			const std::vector<Vec3>& positions,
			const float& speed
		);
		

		void OnCreate() {}
		void OnUpdate();
		void OnDraw(){}
		
		//�A�N�Z�b�T----------------------------------------------
		void SetPositions(const std::vector<Vec3>& positions){
			m_positions = positions;
		}

		void AddPosition(const Vec3& position) {
			m_positions.push_back(position);
		}

		float GetSpeed() const {
			return m_speed;
		}
		void SetSpeed(const float& speed) {
			m_speed = speed;
		}
	};

}

//endbasecross