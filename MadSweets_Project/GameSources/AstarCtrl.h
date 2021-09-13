/*!
@file PlowlingMove.h
@brief PlowlingMove
�S���ҁF�ێR �T��
*/
#pragma once

#include "GraphAstar.h"

namespace basecross {

	class AstarCtrl : public Component
	{
		std::shared_ptr<GraphAstar> m_astar;

		float m_speed;

		void Rotation(const Vec3& direct);
		Vec3 CalucMoveVec();

	public:
		AstarCtrl(const std::shared_ptr<GameObject>& objPtr,
			const std::shared_ptr<GraphAstar>& astar
		):
			Component(objPtr),
			m_astar(astar),
			m_speed(3.0f)
		{}

		void OnCreate() override;
		void OnUpdate() override{}
		void OnDraw() override {}

		void UpdateMove();
		void UpdateVelocityMove(const float& maxSpeedd, const float& nearRange = 3.0f);

		//�A�N�Z�b�T-------------------------------------------------------------

		/// <summary>
		/// Astar�̃��[�g�v�Z�̃X�^�[�g
		/// </summary>
		/// <param name="target">���[�g�ړI�̃|�C���^</param>
		void SearchAstarStart(const std::shared_ptr<GameObject>& target);
		void SearchAstarStart(const Vec3& targetPos);
		
		/// <summary>
		/// �^�[�Q�b�g�̍s���\�����ăm�[�h��I������֐�
		/// </summary>
		/// <param name="target"></param>
		//void SearchAstarForecastStart(const std::shared_ptr<GameObject>& target);

		/// <summary>
		/// �����o���Ƃ��̃��[�g�v�Z
		/// </summary>
		/// <param name="target">�����o���^�[�Q�b�g</param>
		void SearchAstarEscapeStart(const std::shared_ptr<GameObject>& target);
		/// <summary>
		/// �����Ă���Ƃ��̃��[�g�v�Z(���ڈȍ~)
		/// </summary>
		/// <param name="target">�����o���Ώ�</param>
		void SearchAstarEscapeNextRoute(const std::shared_ptr<GameObject>& target);

		/// <summary>
		/// �m�[�h�̒ǋL
		/// </summary>
		/// <param name="position">�m�[�h�̃|�W�V����</param>
		/// <param name="obstacleObjs">��Q���̃I�u�W�F�N�g�z��</param>
		/// <param name="excluteObjs">��Q������Ȃ��I�u�W�F�N�g�z��</param>
		/// <returns>�ǉ������m�[�h�̃C���f�b�N�X</returns>
		int AddNode(const Vec3& position,
			const vector<shared_ptr<GameObject>>& obstacleObjs, const vector<shared_ptr<GameObject>>& excluteObjs);

		/// <summary>
		/// �m�[�h�̍폜
		/// </summary>
		/// <param name="index">�폜�������m�[�h�̃C���f�b�N�X</param>
		void RemoveNode(const int& index);

		/// <summary>
		/// �^�[�Q�b�g�����ԋ߂��m�[�h�������ă|�W�V�������擾
		/// </summary>
		/// <param name="target">�^�[�Q�b�g�̃|�C���^</param>
		/// <returns>�m�[�h�̃|�W�V����</returns>
		Vec3 CalucTargetNearNodePosition(const std::shared_ptr<GameObject>& target);

		/// <summary>
		/// �����̃m�[�h�����ԃ^�[�Q�b�g�ɋ߂��m�[�h���擾
		/// </summary>
		/// <param name="target">�^�[�Q�b�g�̃|�C���^</param>
		/// <returns>�^�[�Q�b�g�ɋ߂��m�[�h</returns>
		NavGraphNode CalucMyNodeToTargetNearNode(const std::shared_ptr<GameObject>& target);

		/// <summary>
		/// ���݌������m�[�h�̃|�W�V������Ԃ�
		/// </summary>
		/// <returns>�m�[�h�̃|�W�V����</returns>
		Vec3 GetCalucNodePos(){
			return m_astar->CalucTargetNode(GetGameObject());
		}

		bool IsRouteEnd() const {
			return m_astar->IsRouteEnd();
		}

		void SetSpeed(const float& speed) {
			m_speed = speed;
		}
		float GetSpeed() const {
			return m_speed;
		}
	};

}

//endbasecross