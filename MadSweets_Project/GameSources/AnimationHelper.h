#pragma once
#include<unordered_map>

namespace basecross
{
	template<class StructMember, class StateEnum>
	class StateBase
	{
	public:
		using ConditionFunction = bool(*)(const StructMember&);

		struct TransitionCondition
		{
			ConditionFunction conditionFunction;
			StateEnum nextStateEnum;
			bool isExitEnd;
		};

	private:

		std::vector<TransitionCondition> m_transitionConditions;

		StateEnum m_state;

		bool m_isEndLoop = false;

	public:

		StateBase(const StateEnum state) :
			m_state(state)
		{

		}

		void AddTransition(ConditionFunction function, const StateEnum nextState,const bool isExitEnd)
		{
			TransitionCondition transition{};
			transition.conditionFunction = function;
			transition.nextStateEnum = nextState;
			transition.isExitEnd = isExitEnd;

			m_transitionConditions.push_back(transition);
		}

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

		virtual void Entry() {}

		virtual void Play(const StructMember& member) = 0;

		virtual void Exit() {}

		virtual StateEnum GetNowState() const = 0;

		StateEnum GetThisState() const
		{
			return m_state;
		}

		virtual float GetStateRateOfTime() const = 0;

		void SetIsEndLoop(const bool isEndLoop)
		{
			m_isEndLoop = isEndLoop;
		}
	};

	struct AnimationClip
	{
		std::wstring animationKey;
		int playTime;
		bool isLoop = false;
	};

	template<class StructMember, class StateEnum>
	class AnimationStateBase : public StateBase<StructMember, StateEnum>
	{
		std::shared_ptr<PNTBoneModelDraw> m_modelDraw;

		AnimationClip m_animationClip;

	public:
		AnimationStateBase(const StateEnum& stateEnum, const std::shared_ptr<PNTBoneModelDraw>& modelDraw,
			const AnimationClip& animationClip) :
			StateBase(stateEnum),
			m_modelDraw(modelDraw),
			m_animationClip(animationClip)
		{
		}

		void Entry() override
		{
			m_modelDraw->SetMeshResource(m_animationClip.animationKey);
			m_modelDraw->AddAnimation(m_animationClip.animationKey, 0, m_animationClip.playTime, m_animationClip.isLoop);
			m_modelDraw->ChangeCurrentAnimation(m_animationClip.animationKey);
		}

		void Play(const StructMember& member) override
		{
			if (m_modelDraw->IsTargetAnimeEnd())
			{
				SetIsEndLoop(true);
			}
		}

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

	template<class StructMember, class StateEnum>
	class AnimatorMainStateMachine
	{
		using StateBasePtr = std::shared_ptr<StateBase<StructMember, StateEnum>>;

		std::unordered_map<StateEnum, StateBasePtr> m_states;

		std::shared_ptr<PNTBoneModelDraw> m_modelDraw;

		StateEnum m_nowStateEnum;

		bool isEmpty = true;

		bool isFirst = true;
	public:
		AnimatorMainStateMachine(const std::shared_ptr<PNTBoneModelDraw>& modelDraw) :
			m_modelDraw(modelDraw)
		{

		}

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

		void Play(const StructMember& member)
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

			m_modelDraw->UpdateAnimation(App::GetApp()->GetElapsedTime());

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

		StateEnum GetNowState() const
		{
			return m_nowStateEnum;
		}

		float GetStateRateOfTime() const
		{
			return m_states.at(m_nowStateEnum)->GetStateRateOfTime();
		}
	};

	template<class StructMember, class StateEnum>
	class Animator : public Component
	{
		using StateMachineType = AnimatorMainStateMachine<StructMember, StateEnum>;
		StructMember m_structMember;

		std::shared_ptr<StateMachineType> m_animatorStateMachine;

	public:
		Animator(std::shared_ptr<GameObject>& owner) :
			Component(owner)
		{

		}


		std::shared_ptr<StateMachineType> CreateAnimationStateMchine(std::shared_ptr<PNTBoneModelDraw>& draw)
		{
			m_animatorStateMachine = std::make_shared<StateMachineType>(draw);

			return m_animatorStateMachine;
		}

		StructMember& GetMemberRefarence()
		{
			return m_structMember;
		}

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

			

			m_animatorStateMachine->Play(m_structMember);
		}

		void OnDraw() override {}
	};

}