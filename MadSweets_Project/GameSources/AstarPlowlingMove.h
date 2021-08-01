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

	struct PlowlingParam 
	{
		Vec3 startPos = Vec3(0.0f);   //�����|�X
		Vec3 endPos = Vec3(0.0f);	  //�ڕW�̃|�W�V����
		Vec3 returnPos = Vec3(0.0f);  //���̍s���n����߂�Ƃ��̃|�W�V����
		float maxSpeed = 2.0f;
		float nearRange = 3.0f;
	};

	/// <summary>
	/// Astar�𗘗p�����p�j�R���|�[�l���g
	/// </summary>
	class AstarPlowlingMove : public Component
	{
		ex_weak_ptr<AstarCtrl> m_astar;

		PlowlingParam m_param;

		void ChangeRoute();
		void Move();

	public:

		AstarPlowlingMove(const std::shared_ptr<GameObject>& objPtr)
			:AstarPlowlingMove(objPtr, PlowlingParam())
		{}

		AstarPlowlingMove(const std::shared_ptr<GameObject>& objPtr,
			const PlowlingParam& param
		) :
			Component(objPtr), m_param(param)
		{}

		void OnCreate() override{}
		void OnStart() override;
		void OnUpdate() override;


		//�A�N�Z�b�T-------------------------------------------
		void SetStartPos(const Vec3& startPos) {
			m_param.startPos = startPos;
		}
		
		void SetEndPos(const Vec3 endPos) {
			m_param.endPos = endPos;
		}

		Vec3 GetReturnPos() const {
			return m_param.returnPos;
		}

		void SetMaxSpeed(const float& speed) {
			m_param.maxSpeed = speed;
		}
		float GetMaxSpeed() const {
			return m_param.maxSpeed;
		}

		
	};

}

//endbasecross