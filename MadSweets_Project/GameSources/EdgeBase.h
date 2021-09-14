/*!
@file EnemyStateMachine.h
@brief EnemyStateMachine
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	/// <summary>
	/// エッジの基底クラス
	/// </summary>
	/// <typeparam name="EnumType">使用する列挙体</typeparam>
	/// <typeparam name="TransitionStructMember">遷移条件用の構造体メンバー</typeparam>
	template<class EnumType, class TransitionStructMember>
	class EdgeBase
	{
		std::function<bool(const TransitionStructMember& member)> m_isTransitionFunc = nullptr; //遷移する条件

		EnumType m_fromType;
		EnumType m_toType;

	public:
		EdgeBase(const EnumType from, const EnumType to)
			:EnemyMainEdge(from, to, nullptr)
		{}

		EdgeBase(const EnumType from, const EnumType to,
			const std::function<bool(const TransitionStructMember& member)>& isTransitionFunc
		) :
			m_fromType(from), m_toType(to), m_isTransitionFunc(isTransitionFunc)
		{}

		//アクセッサ--------------------------------------------------

		/// <summary>
		/// Toに遷移する条件を設定する。
		/// </summary>
		/// <param name="func">設定する条件</param>
		void SetIsToTransition(const std::function<bool(const TransitionStructMember& member)>& func) {
			m_isTransitionFunc = func;
		}
		bool IsTransition(const TransitionStructMember& member) {
			return m_isTransitionFunc(member);
		}

		EnumType GetFromType() const {
			return m_fromType;
		}

		EnumType GetToType() const {
			return m_toType;
		}
	};

}

//endbasecross