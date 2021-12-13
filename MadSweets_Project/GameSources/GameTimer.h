
/*!
@file GameTimer.h
@brief GameTimer�N���X
�S���F�ێR�T��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class GameTimer {
	public:

		struct Parametor {
			float intervalTime = 0.0f;
			float elapsedTime = 0.0f;
			std::function<void()> endFunc = nullptr;

			Parametor(float intervalTime, const std::function<void()>& func);

			/// <summary>
			/// �^�C���I�����ɂ��鏈��
			/// </summary>
			/// <param name="isEndFunc">�I���֐����Ăяo�����ǂ���</param>
			void EndTimer(bool isEndFunc = true);
		};

	private:

		Parametor m_param;

	public:

		GameTimer(const float& intervalTime, const std::function<void()>& func);
		GameTimer(const Parametor& param = Parametor(0.0f, nullptr));

		/// <summary>
		/// ���Ԃ̍X�V
		/// </summary>
		/// <param name="countSpeed">�X�V���Ԃ�speed</param>
		/// <returns>Update�I������true��Ԃ�</returns>
		bool UpdateTimer(const float& countSpeed = 1.0f);

		/// <summary>
		/// �o�ߎ��ԃ��Z�b�g
		/// </summary>
		void ResetTimer() {
			m_param.elapsedTime = 0.0f;
		}

		/// <summary>
		/// �o�ߎ��ԃ��Z�b�g
		/// </summary>
		/// <param name="intervalTime">�ݒ莞��</param>
		void ResetTimer(const float& intervalTime) {
			ResetTimer(intervalTime, nullptr);
		}

		/// <summary>
		/// �o�ߎ��ԃ��Z�b�g
		/// </summary>
		/// <param name="intervalTime">�ݒ莞��</param>
		/// <param name="func">�I�����ɌĂяo�������C�x���g</param>
		void ResetTimer(const float& intervalTime, const std::function<void()>& func) {
			m_param.intervalTime = intervalTime;
			m_param.endFunc = func;
			m_param.elapsedTime = 0.0f;
		}

		/// <summary>
		/// �����I��
		/// </summary>
		/// <param name="isEndFunc">�I�����ɌĂяo���C�x���g���Ăяo�����ǂ���</param>
		void ForceEndTimer(const bool isEndFunc) {
			m_param.EndTimer(isEndFunc);
		}

		//�A�N�Z�b�T-------------------------------------------

		//�o�ߎ��Ԃ𒴂������ǂ���
		bool IsTimeUp() {
			return m_param.intervalTime <= m_param.elapsedTime;
		}

		//�o�ߎ��� / �ݒ莞�� == �o�ߎ��Ԃ̊���
		float GetTimeRate() {
			if (IsTimeUp()) {
				return 1.0f;
			}

			return m_param.elapsedTime / m_param.intervalTime;
		}

		//1.0f - ( �o�ߎ��� / �ݒ莞�� )
		float GetIntervalTimeRate() {
			return 1.0f - GetTimeRate();
		}

		//�c�莞��
		float GetLeftTime() {
			return m_param.intervalTime - m_param.elapsedTime;
		}

		//�o�ߎ���
		float GetElapsedTime() {
			return m_param.elapsedTime;
		}

		//�ݒ莞��
		float GetIntervalTime() {
			return m_param.intervalTime;
		}
	};

}

//endbasecross