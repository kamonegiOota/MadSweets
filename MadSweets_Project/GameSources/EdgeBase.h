/*!
@file EnemyStateMachine.h
@brief EnemyStateMachine
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	/// <summary>
	/// �G�b�W�̊��N���X
	/// </summary>
	/// <typeparam name="EnumType">�g�p����񋓑�</typeparam>
	/// <typeparam name="TransitionStructMember">�J�ڏ����p�̍\���̃����o�[</typeparam>
	template<class EnumType, class TransitionStructMember>
	class EdgeBase
	{
		std::function<bool(const TransitionStructMember& member)> m_isTransitionFunc = nullptr; //�J�ڂ������

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

		//�A�N�Z�b�T--------------------------------------------------

		/// <summary>
		/// To�ɑJ�ڂ��������ݒ肷��B
		/// </summary>
		/// <param name="func">�ݒ肷�����</param>
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