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

		void Rotation(const Vec3& moveVec);

	public:

		ProbeAstarMove(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override{}
		void OnStart() override;
		void OnUpdate() override{}

		//Astar�𗘗p�����ړ�
		void Move();
		//���[�g�̍\�z
		void CalucRoute(const std::shared_ptr<GameObject>& target);


		//�A�N�Z�b�T-----------------------------------------------------------
		bool IsRouteEnd() const {
			auto astar = GetGameObject()->GetComponent<AstarCtrl>(false);
			return astar->IsRouteEnd();
		}

	};

}

//endbasecross