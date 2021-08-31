#pragma once

namespace basecross
{
	class MessageWindow;

	class ClearStage : public Stage
	{
		ex_weak_ptr<MessageWindow> m_messageWindow;

		void FadeInEnd();

		void FadeOutEnd();
	public:
		ClearStage();

		void OnCreate();
	};
}