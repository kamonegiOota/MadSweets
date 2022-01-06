/*!
@file TaskList.h
@brief TaskList
�S���ҁF�ێR �T��
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
	
	//�^�X�N���X�g�̎���------------------------------------------------------------
	
	template<class EnumType>
	class TaskList {

		//�^�X�N�\����
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

		//��`���ꂽ�^�X�N
		std::map<EnumType, std::shared_ptr<Task>> m_defineTaskMap;
		
		//���ݐς܂�Ă���^�X�N
		std::vector<ex_weak_ptr<Task>> m_currentTasks;
		//���ݓ����Ă���^�X�N
		ex_weak_ptr<Task> m_currentTask;
		//���ݓ����Ă���^�X�N�̃C���f�b�N�X�B
		int m_currentIndex = 0;

	public:

		/// <summary>
		/// ���t���[���Ăяo���֐�(�Ăяo���͊O���ˑ�)
		/// </summary>
		void UpdateTask() {
			if (IsEnd()) { //�I�����Ă�����Update���Ă΂Ȃ�
				return;
			}

			//���ݓ��쒆�̃^�X�N��nullptr�Ȃ�B
			if (m_currentTask == nullptr) { 
				m_currentTask = m_currentTasks[m_currentIndex]; //���ݓ��쒆�̃^�X�N�̍X�V
				m_currentTask->enter();  //�J�n�֐��̎���
			}

			//�^�X�N�̃A�b�v�f�[�g
			bool isEndOneTask = m_currentTask->update();

			//�^�X�N�̏I��������
			if (isEndOneTask) {
				EndOneTask();
			}
		}

	private:

		void EndOneTask() {
			if (m_currentTask) {
				m_currentTask->exit(); //���݂̃^�X�N��Exit
			}

			m_currentIndex++;

			if (IsEnd()) {  //���̃^�X�N���Ȃ��Ȃ�B
				m_currentIndex = 0;
				m_currentTask = null;
				m_currentTasks.clear();
				return;
			}

			m_currentTask = m_currentTasks[m_currentIndex]; //���̃^�X�N���擾
			if (m_currentTask) {
				m_currentTask->enter();  //���̃^�X�N��Enter()
			}
		}

	public:

		//�A�N�Z�b�T-----------------------------------------------------------------------------------

		/// <summary>
		/// �^�X�N�̒�`
		/// </summary>
		/// <param name="type">�^�X�N�̃^�C�v</param>
		/// <param name="task">�^�X�N�̃N���X</param>
		void DefineTask(const EnumType type, const std::shared_ptr<TaskNodeBase>& task) {
			DefineTask(type, 
				[]() = { task->enter(); },
				[]() = { task->update(); },
				[]() = { task->exit(); }
			);
		}

		//�^�X�N�̒�`
		void DefineTask(const EnumType type, 
			const std::function<void()>& enter,
			const std::function<bool()>& update,
			const std::function<void()>& exit)
		{
			auto task = std::make_shared<Task>(new Task(type, enter, update, exit));
			if (m_defineTaskMap.count(type)) {  //�L�[�����݂���Ȃ�
				DebugObject::AddString(L"���ɒǉ�����Ă��܂��B");
				return;
			}
			m_defineTaskMap[type] = task;
		}

		//�^�X�N�̓o�^
		void AddTask(const EnumType type) {
			if (!m_defineTaskMap.count(type)) {
				DebugObject::AddString(L"�^�X�N���o�^����Ă��܂���");
				return;
			}

			m_currentTasks.push_back(m_defineTaskMap[type]);
		}

		//�����I��
		void CompulsionStop(const bool isExitFunc = true) {
			//isExitFunc��true�ŁA�J�����g�^�X�N��nullptr�łȂ�������
			if (isExitFunc && m_currentTask != nullptr) { 
				m_currentTask->exit();
			}
			m_currentTask = nullptr;
			m_currentTasks.clear();
			m_currentIndex = 0;
		}

		//�����I�Ɏ��̃^�X�N�ɕύX����B
		void CompulsionNextTask() {
			EndOneTask();
		}

		//�I�����Ă��邩�ǂ���
		bool IsEnd() {
			return m_currentTasks.size() <= m_currentIndex ? true : false;
		}

		//�^�X�N�������Ă��邩�ǂ���
		bool IsMoveTask() {
			return m_currentTask != nullptr;  //�J�����g�^�X�N����������true
		}

		//���ݐi�s���̃^�X�N�̃^�C�v���擾
		EnumType GetCurrentTaskType() {
			return m_currentTask->type;
		}

		//�ǉ�����Ă���^�X�N�̃^�C�v���X�g
		std::vector<EnumType> GetCurrentTaskTypeList() {
			std::vector<EnumType> types;
			for (auto task : m_currentTasks) {
				types.push_back(task->type);
			}

			return types;
		}

		//���݂̃C���f�b�N�X�̎擾
		int GetCurrentIndex() {
			return m_currentIndex;
		}
	};

}

//endbasecross