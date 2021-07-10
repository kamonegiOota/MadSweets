#pragma once

using namespace itbs::Input;

namespace basecross
{
	/// <summary>
	/// Basecross�p�o�^�R���g���[���[
	/// </summary>
	class BasecrossInputer : public InputerBase
	{
	protected:
		/// <summary>
		/// �p���R���X�g���N�^
		/// </summary>
		/// <returns>�Ȃ�</returns>
		BasecrossInputer() noexcept = default;

		/// <summary>
		/// InputDevice�擾�p�֐�
		/// </summary>
		/// <returns>InputDevice�|�C���^</returns>
		static const std::shared_ptr<itbs::Input::InputDevice> GetInputDevice();
	};
}