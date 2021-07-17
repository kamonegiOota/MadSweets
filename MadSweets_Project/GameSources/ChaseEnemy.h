/*!
@file BaseEnemy.h
@brief BaseEnemy
担当者：丸山 裕喜
*/

#pragma once

#include "BaseEnemy.h"
#include "I_Chase.h"

namespace basecross {

	/// <summary>
	/// 敵を見つけたら追いかけてくるエネミー
	/// </summary>
	class ChaseEnemy : public BaseEnemy, public I_Chase
	{

	public:
		ChaseEnemy(const std::shared_ptr<GameObject>& objPtr)
			:BaseEnemy(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		//Interfaceの実装
		void ChangeChaseState(const std::shared_ptr<GameObject>& target) override;

		//アクセッサ-----------------------------------------------
	};
}

//endbasecross