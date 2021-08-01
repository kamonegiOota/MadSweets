/*!
@file PlowlingMove.h
@brief PlowlingMove
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"
#include "AstarCtrl.h"

namespace basecross {

	struct PlowlingParam 
	{
		Vec3 startPos = Vec3(0.0f);   //初期ポス
		Vec3 endPos = Vec3(0.0f);	  //目標のポジション
		Vec3 returnPos = Vec3(0.0f);  //他の行動系から戻るときのポジション
		float maxSpeed = 2.0f;
		float nearRange = 3.0f;
	};

	/// <summary>
	/// Astarを利用した徘徊コンポーネント
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


		//アクセッサ-------------------------------------------
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