/*!
@file EyeSearchRangeParam.h
@brief EyeSearchRangeParam�Ȃ�
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
		/// <param name="target">���G�^�[�Q�b�g</param>
		/// <returns>�͈͓��Ȃ�true</returns>
		bool IsRange(const std::shared_ptr<GameObject>& target);
		/// <summary>
		/// �^�[�Q�b�g�������̍��G�͈͓��́u�����v�ɂ��邩�ǂ����𔻒f
		/// </summary>
		/// <param name="target">���G�^�[�Q�b�g</param>
		/// <returns>�͈͓��Ȃ�true</returns>
		bool IsHeight(const std::shared_ptr<GameObject>& target);
		/// <summary>
		/// �^�[�Q�b�g�������̍��G�͈͓��̊p�x�ɂ��邩���f
		/// </summary>
		/// <param name="target">���G�^�[�Q�b�g</param>
		/// <returns>�͈͓��Ȃ�true</returns>
		bool IsRad(const std::shared_ptr<GameObject>& target);
		/// <summary>
		/// Ray���΂����Ƃ��̃`�F�b�N
		/// </summary>
		/// <param name="targetParam">���G�^�[�Q�b�g</param>
		/// <returns>�͈͓��Ȃ�true</returns>
		bool IsRay(const std::shared_ptr<GameObject>& target);

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

		/// <summary>
		/// ���E���ɂ���Ȃ�true��Ԃ�
		/// </summary>
		/// <param name="target">�^�[�Q�b�g</param>
		/// <returns>���E�̒��ɂ���Ȃ�true</returns>
		bool IsInEyeRange(std::shared_ptr<GameObject>& target);

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

		void SetEyeLength(const float& length) {
			m_param.lenght = length;
		}
		float GetEyeLength() const {
			return m_param.lenght;
		}

		void SetEyeHeight(const float& height) {
			m_param.height = height;
		}
		float GetEyeHeight() const {
			return m_param.height;
		}

		void SetEyeDegree(const float& degree) {
			m_param.rad = XMConvertToRadians(degree);
		}
		float GetEyeDegree() const {
			return XMConvertToDegrees(m_param.rad);
		}

		void SetEyeRadian(const float& radian) {
			m_param.rad = radian;
		}
		float GetEyeRadian() const {
			return m_param.rad;
		}

		/// <summary>
		/// �����Ă����Ԃ��ǂ����𔻒f����
		/// </summary>
		/// <param name="target">�^�[�Q�b�g</param>
		/// <returns>���E�͈̔͂Ȃ�true</returns>
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