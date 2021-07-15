/*!
@file GraphNode.cpp
@brief GraphNode�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

#include "TargetChase.h"

namespace basecross {

	TargetChase::TargetChase(const std::shared_ptr<GameObject>& objPtr):
		TargetChase(objPtr,nullptr)
	{}

	TargetChase::TargetChase(const std::shared_ptr<GameObject>& objPtr,
		const std::shared_ptr<GameObject>& target
	) :
		TargetChase(objPtr,target,1.0f)
	{}

	TargetChase::TargetChase(const std::shared_ptr<GameObject>& objPtr,
		const std::shared_ptr<GameObject>& target,
		const float& speed
	):
		Component(objPtr),
		m_target(target),
		m_speed(speed)
	{}

	void TargetChase::Move() {
		
	}

	void TargetChase::OnCreate() {

	}

	void TargetChase::OnUpdate() {
		if (m_target == nullptr) {  //�^�[�Q�b�g���Ǐ]
			return;
		}

		Move();
	}

}

//endbasecross