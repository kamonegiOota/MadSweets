
/*!
@file TargetEscape.h
@brief TargetEscape
担当者：丸山 裕喜
*/

#pragma once

#include "BaseUseVelocity.h"
class BaseUseVelocity;

namespace basecross {

	/// <summary>
	/// ターゲットから逃げるコンポーネント
	/// </summary>
	class TargetEscape : public Component , public BaseUseVelocity
	{
		int m_outSightCount = 0;     //視界から外れた回数をカウント
		int m_alertReleaseNum = 2;   //視界から何回外れたら警戒を解除するか  

		ex_weak_ptr<GameObject> m_target = nullptr;

		void EyeSearch(); //視線管理
		void Rotation();
		void Move();
		void TargetRayCheck();   //ターゲットが視界内にいるかどうか判断
		void ChangeStateCheck(); //ステートの変更が必要なら変更する。
		void CalucNextNode();    //次のノードを計算する。

		void SuccessEscape();

	public:
		TargetEscape(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		//アクセッサ-------------------------------------------------

		void SetTarget(const std::shared_ptr<GameObject>& target) {
			m_target = target;
		}
		
	};

}

//endbasecross