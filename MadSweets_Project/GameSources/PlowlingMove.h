/*!
@file BaseEnemy.cpp
@brief BaseEnemy実体
担当者：丸山 裕喜
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	/// <summary>
	/// 固定のルートを徘徊するコンポーネント
	/// </summary>
	class PlowlingMove : public Component
	{
		/// <summary>
		/// 徘徊するポジション
		/// </summary>
		std::vector<Vec3> m_positions;

		int m_index;  //現在向かっているポジションのインデックス
		int m_addIndexDirect;  //インデックスが増える方向

		float m_speed;

		/// <summary>
		/// 次のポジションまでのベクトルを計算して返す。
		/// </summary>
		/// <returns>計算したベクトルを返す。</returns>
		Vec3 CalucMoveVec();
		/// <summary>
		/// 実際の移動処理
		/// </summary>
		void Move();
		/// <summary>
		/// 目的地に限りなく近い場所にいるならtrue
		/// </summary>
		/// <param name="pos">現在のポジション</param>
		/// <returns>目的地に近い場合true</returns>
		bool IsNearArrival(const Vec3& pos);
		/// <summary>
		/// 次の目的地のインデックスに切り替える処理
		/// </summary>
		void NextIndex();

	public:

		PlowlingMove(const std::shared_ptr<GameObject>& objPtr);
		PlowlingMove(const std::shared_ptr<GameObject>& objPtr,
			const std::vector<Vec3>& positions
		);
		PlowlingMove(const std::shared_ptr<GameObject>& objPtr,
			const std::vector<Vec3>& positions,
			const float& speed
		);
		

		void OnCreate() {}
		void OnUpdate();
		void OnDraw(){}
		
		//アクセッサ----------------------------------------------
		void SetPositions(const std::vector<Vec3>& positions){
			m_positions = positions;
		}

		void AddPosition(const Vec3& position) {
			m_positions.push_back(position);
		}

		float GetSpeed() const {
			return m_speed;
		}
		void SetSpeed(const float& speed) {
			m_speed = speed;
		}
	};

}

//endbasecross