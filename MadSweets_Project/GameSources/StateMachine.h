/*!
@file EnemyStateMachine.h
@brief EnemyStateMachine
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	namespace maru
	{
		//コンポーネントの変更関係の情報をまとめた構造体
		struct ChangeCompParam {
			std::shared_ptr<Component> comp;
			bool isStart;  //スタート時にどっちにするか？
			bool isExit;   //終了時にどっちにするか？

			ChangeCompParam(const std::shared_ptr<Component>& comp,
				const bool isStart,
				const bool isExit
			):
				comp(comp),
				isStart(isStart),
				isExit(isExit)
			{}
		};


		template<class T>//,
			//enable_if_t<is_base_of_v<GameObject, T>, std::nullptr_t> = nullptr >  //GameObjectを継承したもののみ指定できる
			//enable_if_t<is_base_of_v<BaseEnemy, T>, std::nullptr_t> = nullptr>  //BaseEnemyを継承した物のみ指定できる
		class StateMachine
		{
			std::weak_ptr<T> m_owner;

			std::vector<ChangeCompParam> m_changeParams;

		protected:

			std::shared_ptr<T> GetOwner() {
				auto owner = m_owner.lock();
				if (owner) {
					return owner;
				}
				return nullptr;
			}

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
			StateMachine(const std::shared_ptr<T>& owner) :
				m_owner(owner)
			{}

			virtual void OnStart() = 0;
			virtual void OnUpdate() = 0;
			virtual void OnExit() = 0;

		};

	}

}

//endbasecross