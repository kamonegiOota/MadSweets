#pragma once
#include<vector>
#include"DelegateSystem.h"

namespace itbs
{
	namespace Utility
	{
		/// <summary>
		/// ActionTimer�o�^�f�[�^�\����
		/// </summary>
		struct ActionData
		{
			/// <summary>
			/// ���s����C�x���g
			/// </summary>
			itbs::Utility::Delegate<void()> action;
			/// <summary>
			/// �J�E���g����Ă��鎞��
			/// </summary>
			float advancedTime;
			/// <summary>
			/// �C�x���g�����s����鎞��
			/// </summary>
			float invokeTime;
		};

		/// <summary>
		/// �C�x���g�̃^�C�}�[�Ǘ��N���X
		/// </summary>
		class ActionTimer
		{
			/// <summary>
			/// �C�x���g�f�[�^�z��
			/// </summary>
			std::vector<ActionData> m_actionDatas;

		public:
			/// <summary>
			/// �^�C�}�[�Ǘ�����C�x���g��o�^
			/// </summary>
			/// <param name="actionData">�o�^����C�x���g�f�[�^</param>
			void AddAction(const ActionData& actionData);

			/// <summary>
			/// �C�x���g�̃^�C�}�[��i�߂�
			/// </summary>
			/// <param name="advancedTime">�i�߂鎞��</param>
			void AdvanceTime(const float advancedTime);
		};
	}
}