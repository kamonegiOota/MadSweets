/*!
@file SearchObject.h
@brief SearchObject�Ȃ�
�S���ҁF�ێR �T��
*/

#pragma once

#include "stdafx.h"
#include "Project.h"
#include "DelegateSystem.h"

namespace basecross {

	struct EyeTargetParam {
		std::shared_ptr<GameObject> target;
		mutable bool isFind;  //��������Ԃ��ǂ�����Ԃ�

		EyeTargetParam(const std::shared_ptr<GameObject>& target):
			target(target),
			isFind(false)
		{}
	};

	struct EyeSearchRangeParam {
		float lenght; //���G�͈�(���S�~��)
		float height; //���G�͈�(����)
		float rad;    //���G�͈�(�p�x)

		EyeSearchRangeParam()
			:EyeSearchRangeParam(20.0f,3.0f,XMConvertToRadians(30.0f))
		{}

		EyeSearchRangeParam(const float& lenght,
			const float& height,
			const float& rad
		):
			lenght(lenght),
			height(height),
			rad(rad)
		{}
	};

	/// <summary>
	/// ���E�͈͂��R���g���[������R���|�[�l���g
	/// </summary>
	class EyeSearchRange : public Component
	{
		//�͈͂ɓ����Ă��邩�̑ΏۂɂȂ�I�u�W�F�N�g
		std::vector<EyeTargetParam> m_targetParams;

		EyeSearchRangeParam m_param;

		/// <summary>
		/// �^�[�Q�b�g�������𒆐S�ɋ��̏�͈͓̔��ɂ��邩�ǂ������f
		/// </summary>
		void LengthCheck();
		/// <summary>
		/// �^�[�Q�b�g�������̍��G�͈͓��́u�����v�ɂ��邩�ǂ����𔻒f
		/// </summary>
		/// <param name="target">���G�^�[�Q�b�g</param>
		void HeightCheck(const EyeTargetParam& tagetParam);
		/// <summary>
		/// �^�[�Q�b�g�������̍��G�͈͓��̊p�x�ɂ��邩���f
		/// </summary>
		/// <param name="target">���G�^�[�Q�b�g</param>
		void RadCheck(const EyeTargetParam& targetParam);
		/// <summary>
		/// Ray���΂����Ƃ��̃`�F�b�N
		/// </summary>
		/// <param name="targetParam">���G�^�[�Q�b�g</param>
		void RayCheck(const EyeTargetParam& targetParam);

		/// <summary>
		/// �^�[�Q�b�g�����G�͈͓��ɂ���Ƃ��ɌĂяo�����֐�
		/// </summary>
		void Hit(const EyeTargetParam& targetParam);

	public:
		EyeSearchRange(const std::shared_ptr<GameObject>& objPtr);

		EyeSearchRange(const std::shared_ptr<GameObject>& objPtr,
			const EyeSearchRangeParam& param);

		void OnCreate() override {}
		void OnUpdate() override;

		//�A�N�Z�b�T-------------------------------------------------------------------------
		void AddTarget(const std::shared_ptr<GameObject>& obj) {
			m_targetParams.push_back(EyeTargetParam(obj));
		}

		void SetParam(const EyeSearchRangeParam& param) {
			m_param = param;
		}
		EyeSearchRangeParam GetParam() const {
			return m_param;
		}

		//�����Ă����Ԃ��ǂ����𔻒f����
		bool IsLookTarget(const std::shared_ptr<GameObject>& target) {
			for (auto param : m_targetParams) {
				if (target == param.target) {  //������ނ�������
					return param.isFind;
				}
			}

			return false;
		}

	};

}

//endbasecross