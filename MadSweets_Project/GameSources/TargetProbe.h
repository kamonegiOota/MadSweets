/*!
@file ReturnPlowlingPosition.h
@brief ReturnPlowlingPosition
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "BaseUseVelocity.h"

namespace basecross {

	/// <summary>
	/// �^�[�Q�b�g��{������R���|�[�l���g
	/// </summary>
	class TargetProbe : public Component, public BaseUseVelocity
	{
		std::shared_ptr<GameObject> m_target;  //�{���Ώ�
		std::shared_ptr<GameObject> m_checkHideObj;  //�`�F�b�N���Ă���B���I�u�W�F�N�g
		int m_newNodeIndex = 0;
		
		std::function<void(TargetProbe&)> m_moveFunc;

		//����v���C���[�̑{�������邩�H
		int m_numPorb = 1;
		int m_probCount = 0;  //���ۂɑ{�������񐔁B

		float m_searchRange = 3.0f;  //�T������͈�

		//Node�̒ǉ�
		void AddNode(const Vec3& position);
		void RemoveNode();

		//Astar�ɑ{������Z�b�g����B
		void SetAstarRondomHideObject();

		void InvestigateHideObj();  //�B���I�u�W�F�N�g�𒲂ׂ鏈���B
		void RouteEnd();

		//�B���I�u�W�F�N�g��T���A�j���[�V�����̍Đ��̏I����҂�
		void WaitInvestigateAnimationUpdateEnd();
		void TargetMove();
		void AstarMove();

		void ResetProbe();
		void SetHideObjCollisionUpdate(const bool isUpdate);

		template<class T, class... Ts>
		void ChangeState(Ts&&... params) {
			//m_probCount = 0;
			auto enemy = GetGameObject()->GetComponent<BaseEnemy>(false);
			if (enemy) {
				enemy->ChangeStateMachine<T>(params...);  //����������Ԃɂ���B
			}
		}

	public:

		TargetProbe(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		void StartProb();  //�{���J�n
		void StartProb(const shared_ptr<GameObject>& target);  //�{���J�n

		//�T���A�j���[�V�������I�������Ƃ��̏���
		void EndInvestigateHideAnimation();

		//�A�N�Z�b�T--------------------------------------------------------
		void SetTarget(const std::shared_ptr<GameObject>& target) {
			m_target = target;
		}
		std::shared_ptr<GameObject> GetTarget() const {
			return m_target;
		}

		void ExitProbState();
	};

}

//endbasecorss