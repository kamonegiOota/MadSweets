
/*!
@file EnemyStateMachine.h
@brief EnemyStateMachine
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"

#include "NodeBase.h"

namespace basecross {

	template<class EnemyType>
	class EnemyStateNodeBase : public NodeBase<EnemyType>
	{
		//�R���|�[�l���g�̕ύX�֌W�̏����܂Ƃ߂��\����
		struct ChangeCompParam {
			std::shared_ptr<Component> comp;
			bool isStart;  //�X�^�[�g���ɂǂ����ɂ��邩�H
			bool isExit;   //�I�����ɂǂ����ɂ��邩�H

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
		/// �J�n�ƏI�����ɐ؂�ւ���R���|�[�l���g�̒ǉ�
		/// </summary>
		/// <param name="comp">�؂�ւ���R���|�[�l���g�̃|�C���^</param>
		/// <param name="isStart">�X�^�[�g���ɂǂ����ɐ؂�ւ���</param>
		/// <param name="isExit">�I�����ɂǂ����ɐ؂�ւ��邩</param>
		void AddChangeComp(const std::shared_ptr<Component>& comp,
			const bool isStart, const bool isExit)
		{
			if (comp == nullptr) {  //nullptr�Ȃ�ǉ����Ȃ�
				return;
			}

			ChangeCompParam param(comp, isStart, isExit);
			m_changeParams.push_back(param);
		}

		/// <summary>
		/// �J�n�ƏI�����ɐ؂�ւ���R���|�[�l���g�̒ǉ�
		/// </summary>
		/// <param name="param">�؂�ւ�������܂Ƃ߂��p�����[�^</param>
		void AddChangeComp(const ChangeCompParam& param) {
			if (param.comp == nullptr) {
				return;
			}
			m_changeParams.push_back(param);
		}

		/// <summary>
		/// �o�^���ꂽ�R���|�[�l���g�̐؂�ւ����s��(�X�^�[�g��)
		/// </summary>
		void StartChangeComps() {
			for (auto& param : m_changeParams) {

				param.comp->SetUpdateActive(param.isStart);
			}
		}

		/// <summary>
		/// �o�^���ꂽ�R���|�[�l���g�̐؂�ւ����s��(�I����)
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