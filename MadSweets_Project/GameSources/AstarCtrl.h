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
		GraphAstar m_astar;

		float m_speed;

		Vec3 CalucMoveVec();

	public:
		AstarCtrl(const std::shared_ptr<GameObject>& objPtr,
			const GraphAstar& astar
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
		void SearchAstarStart(const std::shared_ptr<GameObject>& target);
		void SearchAstarStart(const Vec3& targetPos);
		
		/// <summary>
		/// �^�[�Q�b�g�̍s���\�����ăm�[�h��I������֐�
		/// </summary>
		/// <param name="target"></param>
		void SearchAstarForecastStart(const std::shared_ptr<GameObject>& target);

		//�����o���Ƃ��̃��[�g�v�Z
		void SearchAstarEscapeStart(const std::shared_ptr<GameObject>& target);
		//�����Ă���Ƃ��̃��[�g�v�Z
		void SearchAstarEscapeNextRoute(const std::shared_ptr<GameObject>& target);

		Vec3 GetCalucNodePos(){
			return m_astar.CalucTargetNode(GetGameObject());
		}

		bool IsRouteEnd() const {
			return m_astar.IsRouteEnd();
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