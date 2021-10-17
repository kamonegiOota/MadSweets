/*!
@file ObjectTransport.h
@brief ObjectTransport
担当者：丸山 裕喜
*/


#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	/// <summary>
	/// オブジェクトを運ぶコンポーネント
	/// </summary>
	class ObjectTransport : public Component
	{
		Vec3 m_offset = Vec3(0.0f);
		std::weak_ptr<GameObject> m_target;  //運ぶ対象

		void ParentSet();  //ターゲットを自分自身の子オブジェクトにする。
		void Move();  //移動を処理をする。

	public:
		ObjectTransport(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		//アクセッサ----------------------------------------------------------

		void SetTarget(const std::shared_ptr<GameObject>& target) {
			m_target = target;
			ParentSet();
		}
		std::shared_ptr<GameObject> GetTarget() const {
			auto target = m_target.lock();
			return target;
		}

		void SetOffset(const Vec3& offset) {
			m_offset = offset;
		}
		Vec3 GetOffset() const {
			return m_offset;
		}

		/// <summary>
		/// ターゲットが存在するかどうか
		/// </summary>
		/// <returns>ターゲットが存在しないならtrue</returns>
		bool IsTargetEmpty() {
			auto target = m_target.lock();
			return target == nullptr ? true : false;
		}

	};

}

//endbasecross