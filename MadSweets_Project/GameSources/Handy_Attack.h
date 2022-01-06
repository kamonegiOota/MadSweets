/*!
@file Handy_Attack.h
@brief Handy_Attackなど
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "BaseAttack.h"

namespace basecross {

	class Handy_Attack : public BaseAttack
	{
		float m_delay = 1.0f;

		bool IsNowAnimeStateAttack();  //現在攻撃中だったら

		void StartAttack();

		void CreateThrowObject();  //投げる指を生成

		void ChangeAttackState() override;
		void ChangeAttackAnimation();

		void Rotation(const Vec3& direction);
		

	public:
		Handy_Attack(const std::shared_ptr<GameObject>& objPtr);

		Handy_Attack(const std::shared_ptr<GameObject>& objPtr,
			const AttackParam& param);

		void OnCreate() override;
		void OnUpdate() override;

		void Attack(const std::shared_ptr<GameObject>& target) override;
		void ChangeEndState() override;  //ステート終了時にやる処理
	};

}

//endbasecross