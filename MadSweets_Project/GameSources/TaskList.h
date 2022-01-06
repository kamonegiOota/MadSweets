/*!
@file TaskList.h
@brief TaskList
担当者：丸山 裕喜
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "DebugObject.h"

namespace basecross {

	class I_TaskNode
	{
	public:

		virtual void OnEnter() = 0;
		virtual bool OnUpdate() = 0;
		virtual void OnExit() = 0;
	};

	template<class T>
	class TaskNodeBase : public I_TaskNode 
	{
		std::shared_ptr<T> m_owner;

	public:

		TaskNodeBase(const std::shared_ptr<T>& owner)
			:m_owner(owner)
		{}

	protected:
		
		std::shared_ptr<T> GetOwner() {
			return m_owner;
		}
	};

	template<class T>
	class TaskNodeBase_Ex : TaskNodeBase<T>
	{
	public:

		struct Parametor {
			std::function<void()> enter;
			std::function<void()> update;
			std::function<void()> exit;
		};

	protected:

		Parametor m_funcParam;

	public:

		TaskNodeBase_Ex(const std::shared_ptr<T>& owner, const Parametor& param)
			:TaskNodeBase(owner), m_funcParam(param)
		{ }

		void OnEnter() override {
			if (m_funcParam.enter) {
				m_funcParam.enter();
			}
		}

		bool OnUpdate() override {
			if (m_funcParam.update) {
				m_funcParam.update();
			}

			return true;
		}

		void OnExit() override {
			if (m_funcParam.exit) {
				m_funcParam.exit();
			}
		}
	};
	
	//タスクリストの実装------------------------------------------------------------
	
	template<class EnumType>
	class TaskList {

		//タスク構造体
		struct Task {
			EnumType type;
			std::function<void()> enter;
			std::function<bool()> update;
			std::function<void()> exit;

			Task(const EnumType type,
				const std::function<void()>& enter,
				const std::function<bool()>& update,
				const std::function<void()>& exit)
				:
				type(type), enter(enter), update(update), exit(exit)
			{}

			Task(const EnumType type, I_TaskNode& taskNode) :
				type(type),
				enter([]() = { taskNode.OnEnter(); }),
				update([]() = { taskNode.OnUpdate(); }),
				exit([]() = { taskNode.OnEnter(); })
			{}
		};

	private:

		//定義されたタスク
		std::map<EnumType, std::shared_ptr<Task>> m_defineTaskMap;
		
		//現在積まれているタスク
		std::vector<ex_weak_ptr<Task>> m_currentTasks;
		//現在動いているタスク
		ex_weak_ptr<Task> m_currentTask;
		//現在動いているタスクのインデックス。
		int m_currentIndex = 0;

	public:

		/// <summary>
		/// 毎フレーム呼び出す関数(呼び出しは外部依存)
		/// </summary>
		void UpdateTask() {
			if (IsEnd()) { //終了していたらUpdateを呼ばない
				return;
			}

			//現在動作中のタスクがnullptrなら。
			if (m_currentTask == nullptr) { 
				m_currentTask = m_currentTasks[m_currentIndex]; //現在動作中のタスクの更新
				m_currentTask->enter();  //開始関数の実装
			}

			//タスクのアップデート
			bool isEndOneTask = m_currentTask->update();

			//タスクの終了したら
			if (isEndOneTask) {
				EndOneTask();
			}
		}

	private:

		void EndOneTask() {
			if (m_currentTask) {
				m_currentTask->exit(); //現在のタスクのExit
			}

			m_currentIndex++;

			if (IsEnd()) {  //次のタスクがないなら。
				m_currentIndex = 0;
				m_currentTask = null;
				m_currentTasks.clear();
				return;
			}

			m_currentTask = m_currentTasks[m_currentIndex]; //次のタスクを取得
			if (m_currentTask) {
				m_currentTask->enter();  //次のタスクのEnter()
			}
		}

	public:

		//アクセッサ-----------------------------------------------------------------------------------

		/// <summary>
		/// タスクの定義
		/// </summary>
		/// <param name="type">タスクのタイプ</param>
		/// <param name="task">タスクのクラス</param>
		void DefineTask(const EnumType type, const std::shared_ptr<TaskNodeBase>& task) {
			DefineTask(type, 
				[]() = { task->enter(); },
				[]() = { task->update(); },
				[]() = { task->exit(); }
			);
		}

		//タスクの定義
		void DefineTask(const EnumType type, 
			const std::function<void()>& enter,
			const std::function<bool()>& update,
			const std::function<void()>& exit)
		{
			auto task = std::make_shared<Task>(new Task(type, enter, update, exit));
			if (m_defineTaskMap.count(type)) {  //キーが存在するなら
				DebugObject::AddString(L"既に追加されています。");
				return;
			}
			m_defineTaskMap[type] = task;
		}

		//タスクの登録
		void AddTask(const EnumType type) {
			if (!m_defineTaskMap.count(type)) {
				DebugObject::AddString(L"タスクが登録されていません");
				return;
			}

			m_currentTasks.push_back(m_defineTaskMap[type]);
		}

		//強制終了
		void CompulsionStop(const bool isExitFunc = true) {
			//isExitFuncがtrueで、カレントタスクがnullptrでなかったら
			if (isExitFunc && m_currentTask != nullptr) { 
				m_currentTask->exit();
			}
			m_currentTask = nullptr;
			m_currentTasks.clear();
			m_currentIndex = 0;
		}

		//強制的に次のタスクに変更する。
		void CompulsionNextTask() {
			EndOneTask();
		}

		//終了しているかどうか
		bool IsEnd() {
			return m_currentTasks.size() <= m_currentIndex ? true : false;
		}

		//タスクが動いているかどうか
		bool IsMoveTask() {
			return m_currentTask != nullptr;  //カレントタスクが合ったらtrue
		}

		//現在進行中のタスクのタイプを取得
		EnumType GetCurrentTaskType() {
			return m_currentTask->type;
		}

		//追加されているタスクのタイプリスト
		std::vector<EnumType> GetCurrentTaskTypeList() {
			std::vector<EnumType> types;
			for (auto task : m_currentTasks) {
				types.push_back(task->type);
			}

			return types;
		}

		//現在のインデックスの取得
		int GetCurrentIndex() {
			return m_currentIndex;
		}
	};

}

//endbasecross