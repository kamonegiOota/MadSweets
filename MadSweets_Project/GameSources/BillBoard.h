
/*!
@file BillBoard.h
@brief BillBoard�N���X
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"

#include "MyUtility.h"

namespace basecross {

	

	class BillBoard : public Component 
	{
		float m_forwardAdjust;

	public:

		BillBoard(const std::shared_ptr<GameObject>& objPtr):
			Component(objPtr),
			m_forwardAdjust(maru::MyUtility::FOWARD_ADJUST)
		{}

		BillBoard(const std::shared_ptr<GameObject>& objPtr,
			const float forwardAdjust	
		) :
			Component(objPtr),
			m_forwardAdjust(forwardAdjust)
		{}

		void OnCreate() override;
		void OnUpdate() override;

	};

}

//endbasecross