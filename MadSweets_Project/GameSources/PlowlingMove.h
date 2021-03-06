/*!
@file PlowlingMove.h
@brief PlowlingMove
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"
#include "AstarCtrl.h"
#include "BaseUseVelocity.h"

namespace basecross {

	/// <summary>
	/// 固定のルートを徘徊するコンポーネント
	/// </summary>
	class PlowlingMove : public Component, public BaseUseVelocity
	{
		/// <summary>
		/// 徘徊するポジション
		/// </summary>
		std::vector<Vec3> m_positions;

		int m_index;  //現在向かっているポジションのインデックス
		int m_addIndexDirect;  //インデックスが増える方向

		/// <summary>
		/// 次のポジションまでのベクトルを計算して返す。
		/// </summary>
		/// <returns>計算したベクトルを返す。</returns>
		Vec3 CalucMoveVec();
		/// <summary>
		/// 実際の移動処理
		/// </summary>
		void Move();
		void Rotation(const Vec3& moveVec);

		/// <summary>
		/// 次の目的地のインデックスに切り替える処理
		/// </summary>
		void NextIndex();

	public:

		PlowlingMove(const std::shared_ptr<GameObject>& objPtr);
		PlowlingMove(const std::shared_ptr<GameObject>& objPtr,
			const std::vector<Vec3>& positions
		);
		
		void OnCreate();
		void OnStart();
		void OnUpdate();
		
		//アクセッサ----------------------------------------------

		void SetPositions(const std::vector<Vec3>& positions){
			m_positions = positions;
		}

		void AddPosition(const Vec3& position) {
			m_positions.push_back(position);
		}

		/// <summary>
		/// 現在向かっているポジションを返す
		/// </summary>
		/// <returns>現在向かっているポジション</returns>
		Vec3 GetNowTargetPosition() const {
			return m_positions[m_index];
		}
	};

}

//endbasecross