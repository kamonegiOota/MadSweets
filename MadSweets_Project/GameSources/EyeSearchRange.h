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

	struct EyeSearchRangeParam {
		float lenght; //���G�͈�(���S�~��)
		float height; //���G�͈�(����)
		float rad;    //���G�͈�(�p�x)

		EyeSearchRangeParam()
			:EyeSearchRangeParam(5.0f,3.0f,XMConvertToRadians(30.0f))
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
		std::vector<std::shared_ptr<GameObject>> m_targets;

		EyeSearchRangeParam m_param;

		/// <summary>
		/// �^�[�Q�b�g�������𒆐S�ɋ��̏�͈͓̔��ɂ��邩�ǂ������f
		/// </summary>
		void LengthCheck();
		/// <summary>
		/// �^�[�Q�b�g�������̍��G�͈͓��́u�����v�ɂ��邩�ǂ����𔻒f
		/// </summary>
		/// <param name="target">���G�^�[�Q�b�g</param>
		void HeightCheck(const std::shared_ptr<GameObject>& target);
		/// <summary>
		/// �^�[�Q�b�g�������̍��G�͈͓��̊p�x�ɂ��邩���f
		/// </summary>
		/// <param name="target">���G�^�[�Q�b�g</param>
		void RadCheck(const std::shared_ptr<GameObject>& target);
		/// <summary>
		/// �^�[�Q�b�g�����G�͈͓��ɂ���Ƃ��ɌĂяo�����֐�
		/// </summary>
		void Hit(const std::shared_ptr<GameObject>& target);

	public:
		EyeSearchRange(const std::shared_ptr<GameObject>& objPtr);

		EyeSearchRange(const std::shared_ptr<GameObject>& objPtr,
			const EyeSearchRangeParam& param);

		void OnCreate() override {}
		void OnUpdate() override;

		//�A�N�Z�b�T-------------------------------------------------------------------------
		void AddTarget(const std::shared_ptr<GameObject>& obj) {
			m_targets.push_back(obj);
		}

		void SetParam(const EyeSearchRangeParam& param) {
			m_param = param;
		}
		EyeSearchRangeParam GetParam() const {
			return m_param;
		}

	};

}

//endbasecross