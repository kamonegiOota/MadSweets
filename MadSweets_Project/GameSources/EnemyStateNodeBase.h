
/*!
@file EnemyStateMachine.h
@brief EnemyStateMachine
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "NodeBase.h"

namespace basecross {

	template<class EnemyType>
	class EnemyStateNodeBase : public NodeBase<EnemyType>
	{
		//コンポーネントの変更関係の情報をまとめた構造体
		struct ChangeCompParam {
			std::shared_ptr<Component> comp;
			bool isStart;  //スタート時にどっちにするか？
			bool isExit;   //終了時にどっちにするか？

			ChangeCompParam(const std::shared_ptr<Component>& comp,
				const bool isStart,
				const bool isExit
			) :
				comp(comp),
				isStart(isStart),
				isExit(isExit)
			{}
		};


		std::vector<ChangeCompParam> m_changeParams;

	protected:

		/// <summary>
		/// 開始と終了時に切り替えるコンポーネントの追加
		/// </summary>
		/// <param name="comp">切り替えるコンポーネントのポインタ</param>
		/// <param name="isStart">スタート時にどっちに切り替える</param>
		/// <param name="isExit">終了時にどっちに切り替えるか</param>
		void AddChangeComp(const std::shared_ptr<Component>& comp,
			const bool isStart, const bool isExit)
		{
			if (comp == nullptr) {  //nullptrなら追加しない
				return;
			}

			ChangeCompParam param(comp, isStart, isExit);
			m_changeParams.push_back(param);
		}

		/// <summary>
		/// 開始と終了時に切り替えるコンポーネントの追加
		/// </summary>
		/// <param name="param">切り替える情報をまとめたパラメータ</param>
		void AddChangeComp(const ChangeCompParam& param) {
			if (param.comp == nullptr) {
				return;
			}
			m_changeParams.push_back(param);
		}

		/// <summary>
		/// 登録されたコンポーネントの切り替えを行う(スタート時)
		/// </summary>
		void StartChangeComps() {
			for (auto& param : m_changeParams) {

				param.comp->SetUpdateActive(param.isStart);
			}
		}

		/// <summary>
		/// 登録されたコンポーネントの切り替えを行う(終了時)
		/// </summary>
		void ExitChangeComps() {
			for (auto& param : m_changeParams) {
				param.comp->SetUpdateActive(param.isExit);
			}
		}

	public:

		EnemyStateNodeBase(const std::shared_ptr<EnemyType>& owner)
			:NodeBase<EnemyType>(owner)
		{}

	};

}

//endbasecross