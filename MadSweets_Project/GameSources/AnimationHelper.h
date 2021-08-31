#pragma once
#include<unordered_map>
#include"DelegateSystem.h"

namespace basecross
{
	/// <summary>
	/// �X�e�[�g�̒��ۃN���X
	/// </summary>
	/// <typeparam name="StructMember">�g�p����\����</typeparam>
	/// <typeparam name="StateEnum">�g�p����񋓑�</typeparam>
	template<class StructMember, class StateEnum>
	class StateBase
	{
	public:
		/// <summary>
		/// �J�ڏ����^
		/// </summary>
		using ConditionFunction = bool(*)(const StructMember&);

		/// <summary>
		/// �J�ڏ��\����
		/// </summary>
		struct TransitionCondition
		{
			/// <summary>
			/// �J�ڂ������
			/// </summary>
			ConditionFunction conditionFunction;
			/// <summary>
			/// �J�ڐ�̃X�e�[�g
			/// </summary>
			StateEnum nextStateEnum;
			/// <summary>
			/// �A�j���[�V�����I�����ɏ������肷�邩
			/// </summary>
			bool isExitEnd;
		};

	private:

		/// <summary>
		/// �J�ڏ��z��
		/// </summary>
		std::vector<TransitionCondition> m_transitionConditions;

		/// <summary>
		/// �������g�̃X�e�[�g
		/// </summary>
		StateEnum m_state;

		/// <summary>
		/// �A�j���[�V�������[�v���I�����Ă��邩
		/// </summary>
		bool m_isEndLoop = false;

	public:

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="state">�������g�̃X�e�[�g</param>
		StateBase(const StateEnum state) :
			m_state(state)
		{

		}

		/// <summary>
		/// �J�ڂ�ǉ�����
		/// </summary>
		/// <param name="function">�J�ڂ������</param>
		/// <param name="nextState">�J�ڐ�̃X�e�[�g</param>
		/// <param name="isExitEnd">�A�j���[�V�������I�������ۂɏ������肷�邩</param>
		void AddTransition(ConditionFunction function, const StateEnum nextState,const bool isExitEnd)
		{
			TransitionCondition transition{};
			transition.conditionFunction = function;
			transition.nextStateEnum = nextState;
			transition.isExitEnd = isExitEnd;

			m_transitionConditions.push_back(transition);
		}

		/// <summary>
		/// �J�ڏ��������؂��Ď��ɍĐ������X�e�[�g���擾����
		/// </summary>
		/// <param name="structMember">�J�ڏ����Ɏg���\����</param>
		/// <returns>���ɍĐ������X�e�[�g</returns>
		StateEnum CheckTransition(const StructMember& structMember)
		{
			for (auto& transitionCondition : m_transitionConditions)
			{
				if (transitionCondition.isExitEnd && !m_isEndLoop)
				{
						continue;
				}

				if (transitionCondition.conditionFunction(structMember))
				{
					m_isEndLoop = false;

					return transitionCondition.nextStateEnum;
				}
			}

			m_isEndLoop = false;

			return m_state;
		}

		/// <summary>
		/// �X�e�[�g�ɓ˓����ɌĂ΂��֐�
		/// </summary>
		virtual void Entry() {}

		/// <summary>
		/// ���t���[���Ă΂��֐�
		/// </summary>
		/// <param name="member">�X�e�[�g�f�[�^�\����</param>
		virtual void Play(const StructMember& member) = 0;

		/// <summary>
		/// �X�e�[�g����̒E�o���ɌĂ΂��֐�
		/// </summary>
		virtual void Exit() {}

		/// <summary>
		/// ���݂̃X�e�[�g��Ԃ�
		/// </summary>
		/// <returns>���݂̃X�e�[�g</returns>
		virtual StateEnum GetNowState() const = 0;

		/// <summary>
		/// �������g�̃X�e�[�g��Ԃ��֐�
		/// </summary>
		/// <returns>�����̃X�e�[�g</returns>
		StateEnum GetThisState() const
		{
			return m_state;
		}

		virtual float GetStateRateOfTime() const = 0;

		/// <summary>
		/// �A�j���[�V�������[�v���I�����Ă��邩��ݒ肷��
		/// </summary>
		/// <param name="isEndLoop">�A�j���[�V�������[�v���I�����Ă��邩</param>
		void SetIsEndLoop(const bool isEndLoop)
		{
			m_isEndLoop = isEndLoop;
		}
	};

	/// <summary>
	/// �A�j���[�V�����ɕK�v�ȃf�[�^
	/// </summary>
	struct AnimationClip
	{
		/// <summary>
		/// �A�j���[�V�����̃��\�[�X�L�[
		/// </summary>
		std::wstring animationKey;
		/// <summary>
		/// �Đ�����
		/// </summary>
		int playTime;
		/// <summary>
		/// ���[�v���邩�ǂ���
		/// </summary>
		bool isLoop = false;
	};

	/// <summary>
	/// �A�j���[�V�����X�e�[�g���ۃN���X
	/// </summary>
	template<class StructMember, class StateEnum>
	class AnimationStateBase : public StateBase<StructMember, StateEnum>
	{
		/// <summary>
		/// �A�j���[�V�����C�x���g�\����
		/// </summary>
		struct AnimationEvent
		{
			/// <summary>
			/// ���s����鎞��
			/// </summary>
			float actionTime;
			/// <summary>
			/// �Ăׂ��C�x���g
			/// </summary>
			itbs::Utility::Delegate<void()> actionEvent;
			/// <summary>
			/// �A�N�V�������I�������
			/// </summary>
			bool isAction;

			AnimationEvent(const float actionTime, const itbs::Utility::Delegate<void()>& actionEvent) :
				actionTime(actionTime),
				actionEvent(actionEvent),
				isAction(false)
			{

			}
		};

		/// <summary>
		/// �ЂƂO�̃A�j���[�V�����̎���
		/// </summary>
		float m_beforeCurrentAnimationTime = 0.0f;

		/// <summary>
		/// �A�j���[�V�����C�x���g�z��
		/// </summary>
		std::vector<AnimationEvent> m_animationEvents;

		/// <summary>
		/// �Q�[���I�u�W�F�N�g
		/// </summary>
		std::shared_ptr<GameObject> m_gameobject;

		/// <summary>
		/// �A�j���[�V��������{�[�����f��
		/// </summary>
		std::shared_ptr<PNTBoneModelDraw> m_modelDraw;

		/// <summary>
		/// �A�j���[�V�����f�[�^
		/// </summary>
		AnimationClip m_animationClip;

		/// <summary>
		/// �X�e�[�g�˓����ɌĂ΂��C�x���g�z��
		/// </summary>
		std::vector<std::function<void()>> m_entryEvents;
		/// <summary>
		/// �X�e�[�g�˓����ɌĂ΂��C�x���g�z��
		/// </summary>
		std::vector<std::function<void()>> m_exitEvents;

	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="stateEnum">�������g�̃X�e�[�g</param>
		/// <param name="modelDraw">�A�j���[�V��������{�[�����f��Draw</param>
		/// <param name="animationClip">�A�j���[�V�����f�[�^</param>
		AnimationStateBase(const StateEnum& stateEnum, const std::shared_ptr<PNTBoneModelDraw>& modelDraw,
			const AnimationClip& animationClip) :
			StateBase(stateEnum),
			m_modelDraw(modelDraw),
			m_animationClip(animationClip),
			m_gameobject(modelDraw->GetGameObject())
		{
		}

		template<class T,
			std::enable_if_t<std::is_base_of_v<Component, T>, std::nullptr_t> = nullptr>
			void AddAnimationEvent(const float actionTime, void (T::* animationEvent)())
		{
			auto eventDelegate = itbs::Utility::Delegate<void()>(m_gameobject->GetComponent<T>(), animationEvent);
			m_animationEvents.push_back(AnimationEvent(actionTime, eventDelegate));
		}


		/// <summary>
		/// �X�e�[�g�ɓ˓����ɌĂ΂��֐�
		/// </summary>
		void Entry() override
		{
			m_modelDraw->SetMeshResource(m_animationClip.animationKey);
			m_modelDraw->AddAnimation(m_animationClip.animationKey, 0, m_animationClip.playTime, m_animationClip.isLoop);
			m_modelDraw->ChangeCurrentAnimation(m_animationClip.animationKey);

			for (auto& entryEvent : m_entryEvents)
			{
				entryEvent();
			}
		}

		/// <summary>
		/// �X�e�[�g�˓����̃C�x���g��ǉ�����
		/// </summary>
		/// <param name="entryEvent">�X�e�[�g�˓����̃C�x���g</param>
		void AddEntryEvent(const std::function<void()>& entryEvent)
		{
			m_entryEvents.push_back(entryEvent);
		}

		/// <summary>
		/// �X�e�[�g�E�o���̃C�x���g��ǉ�����
		/// </summary>
		/// <param name="exitEvent">�X�e�[�g�E�o���̃C�x���g</param>
		void AddExitEvent(const std::function<void()>& exitEvent)
		{
			m_exitEvents.push_back(exitEvent);
		}

		/// <summary>
		/// ���t���[���Ă΂��֐�
		/// </summary>
		void Play(const StructMember& member) override
		{

			if (m_modelDraw->IsTargetAnimeEnd())
			{
				SetIsEndLoop(true);

				return;
			}

			float currentTime = m_modelDraw->GetCurrentAnimationTime();

			bool isReset = m_beforeCurrentAnimationTime >= currentTime;

			for (AnimationEvent& animationEvent : m_animationEvents)
			{
				if (isReset)
				{
					animationEvent.isAction = false;
				}

				if (animationEvent.isAction)
				{
					continue;
				}

				if (currentTime >= animationEvent.actionTime)
				{
					animationEvent.actionEvent();
					animationEvent.isAction = true;
				}
			}

			m_beforeCurrentAnimationTime = currentTime;
		}

		/// <summary>
		/// �X�e�[�g�E�o���ɌĂ΂��֐�
		/// </summary>
		void Exit() override
		{
			for (auto& exitEvent : m_exitEvents)
			{
				exitEvent();
			}
		}

		/// <summary>
		/// ���݂̃X�e�[�g���擾����
		/// </summary>
		/// <returns>���݂̃X�e�[�g</returns>
		StateEnum GetNowState() const override
		{
			return GetThisState();
		}

		float GetStateRateOfTime() const override
		{
			auto currentTime = m_modelDraw->GetCurrentAnimationTime();
			return currentTime / (static_cast<float>(m_animationClip.playTime) / 30.0f);
		}
	};

	/// <summary>
	/// �A�j���[�V�����p�X�e�[�g�}�V�[���N���X
	/// </summary>
	template<class StructMember, class StateEnum>
	class AnimatorMainStateMachine
	{
		/// <summary>
		/// �X�e�[�g�^
		/// </summary>
		using StateBasePtr = std::shared_ptr<StateBase<StructMember, StateEnum>>;

		/// <summary>
		/// �X�e�[�g�񋓑̂ƃX�e�[�g���}�b�v��������
		/// </summary>
		std::unordered_map<StateEnum, StateBasePtr> m_states;

		/// <summary>
		/// ���f���̃|�C���^
		/// </summary>
		std::shared_ptr<PNTBoneModelDraw> m_modelDraw;

		/// <summary>
		/// ���݂̃X�e�[�g
		/// </summary>
		StateEnum m_nowStateEnum;

		/// <summary>
		/// �X�e�[�g����������Ă��Ȃ���
		/// </summary>
		bool isEmpty = true;

		/// <summary>
		/// �X�e�[�g�}�V���̍Đ��̍ŏ��̈��
		/// </summary>
		bool isFirst = true;
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="modelDraw">���f���Ǘ��̃|�C���^</param>
		AnimatorMainStateMachine(const std::shared_ptr<PNTBoneModelDraw>& modelDraw) :
			m_modelDraw(modelDraw)
		{

		}

		/// <summary>
		/// �A�j���[�V�����X�e�[�g���쐬����֐�
		/// </summary>
		/// <param name="stateEnum">�X�e�[�g�L�[</param>
		/// <param name="animationName">�A�j���[�V�����̃��\�[�X�L�[</param>
		/// <param name="animationLength">�A�j���[�V�����̍Đ��b��</param>
		/// <param name="isLoop">���[�v���邩�ǂ���</param>
		/// <returns>�A�j���[�V�����X�e�[�g</returns>
		std::shared_ptr<AnimationStateBase<StructMember, StateEnum>> CreateAnimationState(const StateEnum stateEnum,
			const std::wstring& animationName, const int animationLength, const bool isLoop)
		{
			AnimationClip animationClip;
			animationClip.animationKey = animationName;
			animationClip.isLoop = isLoop;
			animationClip.playTime = animationLength;

			auto state = std::make_shared<AnimationStateBase<StructMember, StateEnum>>(stateEnum, m_modelDraw, animationClip);
			m_states.insert(std::make_pair(stateEnum, state));

			if (isEmpty)
			{

				isEmpty = false;
				m_nowStateEnum = stateEnum;
			}

			return state;
		}

		/// <summary>
		/// �Đ�����ۂɌĂ΂��
		/// </summary>
		/// <param name="member">�X�e�[�g�}�V�����g�p����f�[�^�\����</param>
		/// <param name="animationSpeed">�A�j���[�V�����X�s�[�h</param>
		void Play(const StructMember& member,const float animationSpeed)
		{
			if (isEmpty)
			{
				return;
			}

			if (isFirst)
			{
				isFirst = false;
				m_states.at(m_nowStateEnum)->Entry();
			}

			m_modelDraw->UpdateAnimation(App::GetApp()->GetElapsedTime() * animationSpeed);

			auto state = m_states.at(m_nowStateEnum);

			auto nextState = state->CheckTransition(member);

			while (nextState != state->GetThisState())
			{
				state->Exit();

				m_nowStateEnum = nextState;

				state = m_states[m_nowStateEnum];

				state->Entry();

				nextState = state->CheckTransition(member);
			}

			state->Play(member);
		}

		/// <summary>
		/// ���݂̃X�e�[�g���擾����
		/// </summary>
		/// <returns>���݂̃X�e�[�g</returns>
		StateEnum GetNowState() const
		{
			return m_nowStateEnum;
		}

		float GetStateRateOfTime() const
		{
			return m_states.at(m_nowStateEnum)->GetStateRateOfTime();
		}
	};

	/// <summary>
	/// �A�j���[�V�����Ǘ��R���|�[�l���g
	/// </summary>
	template<class StructMember, class StateEnum>
	class Animator : public Component
	{
		/// <summary>
		/// �X�e�[�g�}�V�[���^
		/// </summary>
		using StateMachineType = AnimatorMainStateMachine<StructMember, StateEnum>;
		/// <summary>
		/// �X�e�[�g�}�V���Ŏg�p����\����
		/// </summary>
		StructMember m_structMember;

		/// <summary>
		/// �X�e�[�g�}�V���̃|�C���^
		/// </summary>
		std::shared_ptr<StateMachineType> m_animatorStateMachine;
		/// <summary>
		/// �A�j���[�V�����Ɏg�����f���̕`��|�C���^
		/// </summary>
		std::shared_ptr<PNTBoneModelDraw> m_boneModelDraw;

		float m_animationSpeed = 1.0f;

	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="owner">�Q�[���I�u�W�F�N�g</param>
		Animator(std::shared_ptr<GameObject>& owner) :
			Component(owner)
		{
		}

		/// <summary>
		/// �A�j���[�V�����X�e�[�g�}�V�[�����쐬����֐�
		/// </summary>
		/// <returns></returns>
		std::shared_ptr<StateMachineType> CreateAnimationStateMchine()
		{
			if (!m_boneModelDraw)
			{
				m_boneModelDraw = GetGameObject()->GetComponent<PNTBoneModelDraw>();
			}

			m_animatorStateMachine = std::make_shared<StateMachineType>(m_boneModelDraw);

			return m_animatorStateMachine;
		}

		void SetAnimationSpeed(const float animationSpeed)
		{
			m_animationSpeed = animationSpeed;
		}

		/// <summary>
		/// �X�e�[�g�}�V�[���Ŏg�p����\���̂̎Q�Ƃ��擾����
		/// </summary>
		/// <returns>�X�e�[�g�}�V�[���Ŏg�p����\���̂̎Q��</returns>
		StructMember& GetMemberRefarence()
		{
			return m_structMember;
		}

		/// <summary>
		/// ���݂̃X�e�[�g���擾����
		/// </summary>
		/// <returns>���݂̃X�e�[�g</returns>
		StateEnum GetNowState() const
		{
			return m_animatorStateMachine->GetNowState();
		}

		float GetStateRateOfTime() const
		{
			return m_animatorStateMachine->GetStateRateOfTime();
		}

		void OnUpdate() override
		{
			if (!m_animatorStateMachine)
			{
				return;
			}

			m_animatorStateMachine->Play(m_structMember, m_animationSpeed);
		}
	};

}