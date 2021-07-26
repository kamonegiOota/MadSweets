
/*!
@file MyUtility.h
@brief MyUtilityクラス
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	/// <summary>
	/// 速度計算に必要な便利関数まとめ
	/// </summary>
	class UtilVelocity 
	{

	public:

		/// <summary>
		/// 最大速度制限
		/// </summary>
		/// <param name="velocity">制限したいベクトル</param>
		/// <param name="maxSpeed">制限速度</param>
		/// <returns>制限された範囲のベクトルを返す。</returns>
		static Vec3 MaxSpeedVecCheck(const Vec3 velocity ,const float& maxSpeed);

		//ベクトル計算用の関数。
		/// <summary>
		/// 直線的に追いかけるためのベクトルを計算して返す関数
		/// </summary>
		/// <param name="velocity">現在の速度</param>
		/// <param name="toVec">ターゲット方向のベクトル</param>
		/// <param name="maxSpeed">最大速度</param>
		/// <returns>「ターゲットの方向のベクトル」- 「現在の速度」</returns>
		static Vec3 CalucSeekVec(const Vec3& velocity, const Vec3& toVec,const float& maxSpeed);
		/// <summary>
		/// 到着ベクトルを返す(近づくと小さくなるベクトル)
		/// </summary>
		/// <param name="velocity">現在の速度</param>
		/// <param name="toVec">ターゲット方向のベクトル</param>
		/// <param name="maxSpeed">最大速度</param>
		/// <param name="decl"></param>
		/// <returns>到着ベクトルを返す(近づくと小さくなるベクトル)を返す</returns>
		static Vec3 CalucArriveVec(const Vec3& velocity, const Vec3& toVec,const float& maxSpeed,const float& decl = 3.0f);

		//近くにいるときはArriveで,遠くにいるときはSeekで追いかける関数
		static Vec3 CalucNearArriveFarSeek(const Vec3& velocity, const Vec3& toVec,
			const float& maxSpeed, const float& nearRange, const float& decl = 3.0f);
	};

}

//endbasecross