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
		//std::shared_ptr<GameObject> m_target;  //�{���Ώ�
		std::shared_ptr<GameObject> m_checkHideObj;  //�`�F�b�N���Ă���B���I�u�W�F�N�g
		int m_newNodeIndex = 0;
		
		std::function<void(TargetProbe&)> m_moveFunc;

		//����v���C���[�̑{�������邩�H
		int m_numPorb = 1;
		int m_probCount = 0;  //���ۂɑ{�������񐔁B

		float m_searchRange = 10.0f;  //�T������͈�
		float m_lostSeekTime = 3.0f;  //�^�[�Q�b�g�Ƃ̊Ԃɏ�Q��������ꍇ���̃��[�g�����ɂ���^�C���B

		void AddNode(const Vec3& position);
		void RemoveNode();

		/// <summary>
		/// Astar�ɑ{������Z�b�g����B
		/// </summary>
		void SetAstarRondomHideObject();

		/// <summary>
		/// �B���I�u�W�F�N�g�𒲂ׂ鏈���B
		/// </summary>
		void InvestigateHideObj();
		void RouteEnd();

		/// <summary>
		/// �B���I�u�W�F�N�g��T���A�j���[�V�����̍Đ��̏I����҂�
		/// </summary>
		void WaitInvestigateAnimationUpdateEnd();
		void TargetMove();
		void AstarMove();
		void Rotation(const Vec3& direct);

		void ResetProbe();
		/// <summary>
		/// HideObject��Collider��On,Off�̐؂�ւ�(�`���Ƃ��Ɉꎞ�I��off�ɂ���B)
		/// </summary>
		/// <param name="isUpdate">On�Ȃ�true</param>
		void SetHideObjCollisionUpdate(const bool isUpdate);

		void ChangeEndProbeState();  //�X�e�[�g�}�V���ύX���ɐ���

		void LostTimerStart();
		void LostTimerCancel();

	public:

		TargetProbe(const std::shared_ptr<GameObject>& objPtr)
			:Component(objPtr)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		/// <summary>
		/// �{���J�n
		/// </summary>
		void StartProb();  
		/// <summary>
		/// �{���J�n
		/// </summary>
		/// <param name="target">�{���^�[�Q�b�g</param>
		void StartProb(const shared_ptr<GameObject>& target);

		/// <summary>
		/// �T���A�j���[�V�������I�������Ƃ��̏���
		/// </summary>
		void EndInvestigateHideAnimation();

		//�A�N�Z�b�T--------------------------------------------------------

		//void SetTarget(const std::shared_ptr<GameObject>& target) {
		//	m_target = target;
		//}
		//std::shared_ptr<GameObject> GetTarget() const {
		//	return m_target;
		//}

		void SetSearchRange(const float& range) {
			m_searchRange = range;
		}
		float GetSearchRange() const {
			return m_searchRange;
		}

		/// <summary>
		/// ���̃X�e�[�g�𔲂��o���Ƃ��ɌĂԊ֐�
		/// </summary>
		void ExitProbState();
	};

}

//endbasecorss