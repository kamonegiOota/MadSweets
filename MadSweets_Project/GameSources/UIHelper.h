#pragma once

namespace basecross
{
	class GameObject;
	class Component;
	class Stage;

	/// <summary>
	/// �\������ۂ̃A���J�[�^�C�v
	/// </summary>
	enum class AnchorType
	{
		Center,
		Up,
		Down,
		Left,
		LeftUp,
		LeftDown,
		Right,
		RightUp,
		RightDown
	};

	/// <summary>
	/// UI�`��p�g�����X�t�H�[��
	/// </summary>
	class RectTransform : public Component
	{
		/// <summary>
		/// �A���J�[�ɑΉ�����N���C�A���g�̈捶��̒��_�̃I�t�Z�b�g�����}�b�v
		/// </summary>
		static const std::unordered_map<AnchorType, Vec2> m_anchorOffsetTable;

		/// <summary>
		/// ���[�J�����W
		/// </summary>
		Vec2 m_position = Vec2(0, 0);
		/// <summary>
		/// ���[�J����]
		/// </summary>
		float m_rotation = 0.0f;
		/// <summary>
		/// ���[�J���X�P�[��
		/// </summary>
		Vec2 m_scale = Vec2(1.0f, 1.0f);

		/// <summary>
		/// �l�p�̕�
		/// </summary>
		float m_width;
		/// <summary>
		/// �l�p�̍���
		/// </summary>
		float m_height;

		/// <summary>
		/// �l�p�̃A���J�[�^�C�v
		/// </summary>
		AnchorType m_anchorType = AnchorType::Center;

		/// <summary>
		/// �s�{�b�g
		/// </summary>
		Vec2 m_pivot = Vec2(0.0f, 0.0f);

	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="owner">�Q�[���I�u�W�F�N�g</param>
		RectTransform(std::shared_ptr<GameObject>& owner);

		/// <summary>
		/// UI�p���W���E�B���h�E���W�ɕϊ�����
		/// </summary>
		/// <param name="uiPoint">UI�p���W</param>
		/// <returns>�E�B���h�E���W</returns>
		static Vec2 ToWindowPoint(const Vec2& uiPoint);

		/// <summary>
		/// �A���J�[�^�C�v��ݒ肷��
		/// </summary>
		/// <param name="anchorType">�A���J�[�^�C�v</param>
		void SetAnchor(const AnchorType anchorType);

		/// <summary>
		/// �A���J�[�^�C�v���擾����
		/// </summary>
		/// <returns>�A���J�[�^�C�v</returns>
		AnchorType GetAnhor() const;

		/// <summary>
		/// �s�{�b�g��ݒ肷��
		/// </summary>
		/// <param name="pivot">�s�{�b�g</param>
		void SetPivot(Vec2 pivot);
		/// <summary>
		/// �s�{�b�g��ݒ肷��
		/// </summary>
		/// <param name="x">�s�{�b�gX���W</param>
		/// <param name="y">�s�{�b�gY���W</param>
		void SetPivot(float x, float y);

		/// <summary>
		/// �s�{�b�g���擾����
		/// </summary>
		/// <returns>�s�{�b�g</returns>
		Vec2 GetPivot() const;

		/// <summary>
		/// �l�p�̕���ݒ肷��
		/// </summary>
		/// <param name="width">��</param>
		void SetWidth(const float width);
		/// <summary>
		/// �l�p�̍�����ݒ肷��
		/// </summary>
		/// <param name="height">����</param>
		void SetHeight(const float height);
		/// <summary>
		/// �l�p�̃T�C�Y��ݒ肷��
		/// </summary>
		/// <param name="width">��</param>
		/// <param name="height">����</param>
		void SetRectSize(const float width, const float height);

		/// <summary>
		/// �l�p�̕����擾����
		/// </summary>
		/// <returns>��</returns>
		float GetWidth() const;
		/// <summary>
		/// �l�p�̍������擾����
		/// </summary>
		/// <returns>����</returns>
		float GetHeight() const;

		/// <summary>
		/// ���[�J�����W��ݒ肷��
		/// </summary>
		/// <param name="position">���[�J�����W</param>
		void SetPosition(const Vec2& position);
		/// <summary>
		/// ���[�J�����W��ݒ肷��
		/// </summary>
		/// <param name="x">���[�J��X���W</param>
		/// <param name="y">���[�J�����W</param>
		void SetPosition(const float x, const float y);

		/// <summary>
		/// ���[�J�����W���擾����
		/// </summary>
		/// <returns>���[�J�����W</returns>
		Vec2 GetPosition() const;

		Vec2 GetWorldPosition() const;

		/// <summary>
		/// ���[�J����]��ݒ肷��
		/// </summary>
		/// <param name="radian">���[�J��Z��]</param>
		void SetRotation(const float radian);

		/// <summary>
		/// ���[�J����]���擾����
		/// </summary>
		/// <returns>���[�J��Z��]</returns>
		float GetRotation() const;

		/// <summary>
		/// ���[�J��Z��]��ǉ�����
		/// </summary>
		/// <param name="radian">�ǉ����郍�[�J��Z��]</param>
		void Rotate(const float radian);

		/// <summary>
		/// ���[�J���X�P�[����ݒ肷��
		/// </summary>
		/// <param name="scale">���[�J���X�P�[��</param>
		void SetScale(const Vec2& scale);
		/// <summary>
		/// ���[�J���X�P�[����ݒ肷��
		/// </summary>
		/// <param name="x">���[�J��X�X�P�[��</param>
		/// <param name="y">���[�J��Y�X�P�[��</param>
		void SetScale(const float x, const float y);

		/// <summary>
		/// ���[�J���X�P�[�����擾����
		/// </summary>
		/// <returns>���[�J���X�P�[��</returns>
		Vec2 GetScale() const;

		/// <summary>
		/// ���[���h�X�P�[�����擾����
		/// </summary>
		/// <returns>���[���h�X�P�[��</returns>
		Vec2 GetWorldScale() const;

		/// <summary>
		/// �s�{�b�g����󂯎�����A���J�[�^�C�v�܂ł̒�����Ԃ�
		/// </summary>
		/// <param name="anchorType">�A���J�[�^�C�v</param>
		/// <param name="isScaleble">�X�P�[���̉e�����󂯂邩</param>
		/// <returns>�s�{�b�g����A���J�[�^�C�v�̋���</returns>
		Vec2 GetAnchorOffset(const AnchorType anchorType,const bool isScaleble = true) const;

		/// <summary>
		/// ���[���h�s����擾����
		/// </summary>
		/// <returns></returns>
		D2D1::Matrix3x2F GetWorldMatrix() const;

		/// <summary>
		/// �e��RectTransform���擾����
		/// </summary>
		/// <returns>�e��RectTransform</returns>
		std::shared_ptr<RectTransform> GetParentRectTransform() const;

		/// <summary>
		/// �e�̃A���J�[�I�t�Z�b�g���擾����
		/// </summary>
		/// <param name="anchorType">�A���J�[�^�C�v</param>
		/// <returns>�A���J�[�I�t�Z�b�g</returns>
		Vec2 GetParentAnchorOffset(const AnchorType anchorType) const;

		void OnUpdate() override;

		virtual void OnDraw() override {}
	};

	enum class ImageFillType
	{
		None,
		Horizontal,
		Vertical
	};

	/// <summary>
	/// �摜��\������R���|�[�l���g
	/// </summary>
	class Image : public PCTSpriteDraw
	{
		/// <summary>
		/// Vertices�ɕK�v�Ȓ��_��
		/// </summary>
		static constexpr int VERTICES_POINT_NUM = 4;

		/// <summary>
		/// ���_�f�[�^�z��
		/// </summary>
		static const std::vector<uint16_t> m_indices;

		/// <summary>
		/// �l�p�g�����X�t�H�[��
		/// </summary>
		ex_weak_ptr<RectTransform> rectTransform;

		/// <summary>
		/// �摜�̐؂���̈�̒��_�f�[�^
		/// </summary>
		std::array<Vec2, VERTICES_POINT_NUM> m_UVPoints;

		/// <summary>
		/// �摜�̓h��Ԃ��^�C�v
		/// </summary>
		ImageFillType m_fillType = ImageFillType::None;

		/// <summary>
		/// �h��Ԃ����� (1.0f �` 2.0f)
		/// </summary>
		float m_fillAmount = 1.0f;

		/// <summary>
		/// ���݂̏�Ԃ�vertices�f�[�^���쐬����
		/// </summary>
		/// <returns>vertices�f�[�^</returns>
		std::vector<VertexPositionColorTexture> CreateVertices() const;

	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="owner">�Q�[���I�u�W�F�N�g</param>
		/// <param name="width">�`�悷�镝</param>
		/// <param name="height">�`�悷�鍂��</param>
		Image(std::shared_ptr<GameObject>& owner);


		/// <summary>
		/// �摜�̐؂���̈��ݒ肷��
		/// </summary>
		/// <param name="leftUpPoint">�؂���̈�̍���̒��_�̍��W</param>
		/// <param name="width">�؂���̈�̕�</param>
		/// <param name="height">�؂���̈�̍���</param>
		/// <param name="imageSize">���摜�̕��ƍ���</param>
		void SetUVRect(const Vec2& leftUpPoint,const float width,const float height,Vec2& imageSize);

		/// <summary>
		/// Alpha�l��ݒ肷��
		/// </summary>
		/// <param name="alpha">Alpha�l</param>
		void SetAlpha(const float alpha);

		/// <summary>
		/// Alpha�l���擾����
		/// </summary>
		/// <returns>Alpha�l</returns>
		float GetAlpha() const;

		/// <summary>
		/// �h��Ԃ��^�C�v��ݒ肷��
		/// </summary>
		/// <param name="fillType">�h��Ԃ��^�C�v</param>
		void SetFillType(const ImageFillType fillType);

		/// <summary>
		/// �h��Ԃ��^�C�v���擾����
		/// </summary>
		/// <returns></returns>
		ImageFillType GetFillType() const;

		/// <summary>
		/// �h��Ԃ��ʂ�ݒ肷��
		/// </summary>
		/// <param name="fillAmount">�h��Ԃ���</param>
		void SetFillAmount(const float fillAmount);

		/// <summary>
		/// �h��Ԃ��ʂ��擾����
		/// </summary>
		/// <returns>�h��Ԃ���</returns>
		float GetFillAmount() const;

		virtual void OnCreate() override;

		void OnUpdate() override;
	};

	/// <summary>
	/// �e�L�X�g��\������R���|�[�l���g
	/// </summary>
	class TextBox : public Component
	{
	public:

		/// <summary>
		/// Box�̏c�����ɑ΂��āAText���ǂ̈ʒu�ɂ��邩
		/// </summary>
		enum class TextVerticalAlignment
		{
			/// <summary>
			/// ��l��
			/// </summary>
			Up,
			/// <summary>
			/// ������
			/// </summary>
			Center,
			/// <summary>
			/// ���l��
			/// </summary>
			Down
		};

		enum class TextSideAlignment
		{
			Left,
			Center,
			Right
		};

		enum class TextStyle
		{
			Normal,
			Italic,
			Oblique
		};

	private:
		/// <summary>
		/// �e�L�X�g�X�^�C���ɑ΂���DWRITE_FONT_STYLE�ɕϊ�����e�[�u��
		/// </summary>
		static const std::unordered_map<TextStyle, DWRITE_FONT_STYLE> m_textStypeToDWriteStyleTable;

		/// <summary>
		/// �l�p�g�����X�t�H�[��
		/// </summary>
		ex_weak_ptr<RectTransform> rectTransform;
		/// <summary>
		/// �e�L�X�g�̉��ɑ΂���ʒu
		/// </summary>
		TextSideAlignment m_textSideAlignment = TextSideAlignment::Left;
		/// <summary>
		/// �e�L�X�g�̏c�ɑ΂���ʒu
		/// </summary>
		TextVerticalAlignment m_textVerticalAlignment = TextVerticalAlignment::Up;

		/// <summary>
		/// �{�b�N�X�̐F
		/// </summary>
		Col4 m_boxColor = Col4();
		/// <summary>
		/// �{�b�N�X�`��p�F�u���V
		/// </summary>
		ComPtr<ID2D1SolidColorBrush> m_boxBrush;

		/// <summary>
		/// �t�H���g�̐F
		/// </summary>
		Col4 m_fontColor = Col4(0,0,0,1);
		/// <summary>
		/// �t�H���g�̕`��p�F�u���VS
		/// </summary>
		ComPtr<ID2D1SolidColorBrush> m_fontBrush;

		/// <summary>
		/// �X�e�[�g�u���b�N
		/// </summary>
		ComPtr<ID2D1DrawingStateBlock> m_stateBlock;

		/// <summary>
		/// �t�H���g��
		/// </summary>
		std::wstring m_fontName = L"�l�r �S�V�b�N";

		/// <summary>
		/// �t�H���g�T�C�Y
		/// </summary>
		float m_fontSize = 16.0f;

		/// <summary>
		/// �e�L�X�g
		/// </summary>
		std::wstring m_text;

		/// <summary>
		/// �e�L�X�g�t�H�[�}�b�g
		/// </summary>
		ComPtr<IDWriteTextFormat> m_textFormat;
		/// <summary>
		/// �e�L�X�g���C�A�E�g
		/// </summary>
		ComPtr<IDWriteTextLayout> m_textLayout;

		/// <summary>
		/// �e�L�X�g���g���N�Xs
		/// </summary>
		DWRITE_TEXT_METRICS m_textMetrics;

		/// <summary>
		/// �e�L�X�g�X�^�C��
		/// </summary>
		TextStyle m_textStyle = TextStyle::Normal;

		/// <summary>
		/// �e�L�X�g�̃t�H�[�}�b�g���X�V����
		/// </summary>
		void TextFormatUpdate();
		/// <summary>
		/// �e�L�X�g�̃��C�A�E�g���X�V����
		/// </summary>
		void TextLayoutUpdate();
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="owner">�Q�[���I�u�W�F�N�g</param>
		TextBox(std::shared_ptr<GameObject>& owner);

		/// <summary>
		/// �{�b�N�X�̐F��ݒ肷��
		/// </summary>
		/// <param name="color">�{�b�N�X�̐F</param>
		void SetBoxColor(const Col4& color);
		/// <summary>
		/// �{�b�N�X�̐F��ݒ肷��
		/// </summary>
		/// <param name="red">��</param>
		/// <param name="green">��</param>
		/// <param name="blue">��</param>
		/// <param name="alpha">�����x</param>
		void SetBoxColor(const float red, const float green, const float blue, const float alpha);

		/// <summary>
		/// �{�b�N�X�̐F���擾����
		/// </summary>
		/// <returns>�{�b�N�X�̐F</returns>
		Col4 GetBoxColor() const;

		/// <summary>
		/// �t�H���g�̐F��ݒ肷��
		/// </summary>
		/// <param name="color">�t�H���g�̐F</param>
		void SetFontColor(const Col4& color);
		/// <summary>
		/// �t�H���g�̐F��ݒ肷��
		/// </summary>
		/// <param name="red">��</param>
		/// <param name="green">��</param>
		/// <param name="blue">��</param>
		/// <param name="alpha">�����x</param>
		void SetFontColor(const float red, const float green, const float blue, const float alpha);

		/// <summary>
		/// �t�H���g�̐F���擾����
		/// </summary>
		/// <returns>�t�H���g�̐F</returns>
		Col4 GetFontColor() const;

		/// <summary>
		/// �t�H���g�̎��̂�ݒ肷��
		/// </summary>
		/// <param name="fontName">�t�H���g��</param>
		void SetFontName(const std::wstring& fontName);

		/// <summary>
		/// �t�H���g�̃T�C�Y��ݒ肷��
		/// </summary>
		/// <param name="fontSize">�t�H���g�T�C�Y</param>
		void SetFontSize(const float fontSize);

		/// <summary>
		/// TextBox�S�̂�Alpha�l��ݒ肷��
		/// </summary>
		/// <param name="alpha">Alpha�l</param>
		void SetAlpha(const float alpha);

		/// <summary>
		/// �e�L�X�g��ݒ肷��
		/// </summary>
		/// <param name="text">�ݒ肷��e�L�X�g</param>
		void SetText(const std::wstring& text);

		/// <summary>
		/// �e�L�X�g��ǉ�����
		/// </summary>
		/// <param name="text">�ǉ�����e�L�X�g</param>
		void AddText(const std::wstring& text);

		/// <summary>
		/// �e�L�X�g���擾����
		/// </summary>
		/// <returns>�e�L�X�g</returns>
		std::wstring GetText() const;

		/// <summary>
		/// �e�L�X�g�̉��ɑ΂���ʒu��ݒ肷��
		/// </summary>
		/// <param name="textSideAlignment">���ɑ΂���ʒu</param>
		void SetTextSideAlignment(const TextSideAlignment textSideAlignment);

		/// <summary>
		/// �e�L�X�g�̉��ɑ΂���ʒu���擾����
		/// </summary>
		/// <returns>���ɑ΂���ʒu</returns>
		TextSideAlignment GetTextSideAlignment() const;

		/// <summary>
		/// �e�L�X�g�̏c�ɑ΂���ʒu��ݒ肷��
		/// </summary>
		/// <param name="textVerticalAlignment">�c�ɑ΂���ʒu</param>
		void SetTextVerticalAlignment(const TextVerticalAlignment textVerticalAlignment);

		/// <summary>
		/// �e�L�X�g�̏c�ɑ΂���ʒu���擾����
		/// </summary>
		/// <returns>�c�ɑ΂���ʒu</returns>
		TextVerticalAlignment GetTextVerticalAlignment() const;

		/// <summary>
		/// �e�L�X�g�X�^�C����ݒ肷��
		/// </summary>
		/// <param name="textStyle">�e�L�X�g�X�^�C��</param>
		void SetTextStyle(const TextStyle textStyle);

		/// <summary>
		/// �e�L�X�g�X�^�C�����擾����
		/// </summary>
		/// <returns>�e�L�X�g�X�^�C��</returns>
		TextStyle GetTextStyle() const;

		void OnUpdate() override {}

		void OnDraw() override;
	};

	struct ChoicesObjectAndEvent
	{
		std::wstring text;
		ex_weak_ptr<GameObject> choicesObject;
		std::function<void()> eventFunction;

		ChoicesObjectAndEvent();

		ChoicesObjectAndEvent(const std::wstring& text, std::shared_ptr<GameObject>& choicesObject, const std::function<void()>& eventFunction);
	};

	class ChoicesList : public Component
	{

		ex_weak_ptr<GameObject> m_upTextBox;
		ex_weak_ptr<GameObject> m_centerTextBox;
		ex_weak_ptr<GameObject> m_downTextBox;

		std::vector<ex_weak_ptr<ChoicesObjectAndEvent const>> m_choiceObjectAndEvents;

		bool m_isEmpty = true;

		int m_index = 0;

		void UpdateChoices();

		std::shared_ptr<GameObject> CreateChildTextBoxObject();
	public:
		itbs::Utility::Delegate<void()> selectChangeEvent;
		itbs::Utility::Delegate<void()> pushEvent;

		ChoicesList(std::shared_ptr<GameObject>& owner);

		void AddChoice(const std::shared_ptr<ChoicesObjectAndEvent const>& choicesObjectAndEvent);

		void RemoveChoice(const std::shared_ptr<GameObject>& gameObject);

		void AddIndex(const int addIndex);

		void SetIndex(const int index);

		void Invoke();

		void OnStart() override;

		void OnUpdate2() override;
	};

	class I_Selectable
	{
	public:
		virtual void OnSelect() = 0;
		virtual void OnOutSelect() = 0;
		virtual void OnPush() = 0;
		virtual bool GetIsSelectedLock() const = 0;
		virtual std::shared_ptr<I_Selectable> GetVerticalBeforeSelectable() const = 0;
		virtual std::shared_ptr<I_Selectable> GetVerticalNextSelectable() const = 0;
		virtual std::shared_ptr<I_Selectable> GetHorizontalBeforeSelectable() const = 0;
		virtual std::shared_ptr<I_Selectable> GetHorizontalNextSelectable() const = 0;
	};

	class SelectableComponent : public Component, public I_Selectable
	{
		ex_weak_ptr<I_Selectable> m_verticalBeforeSelectable;
		ex_weak_ptr<I_Selectable> m_verticalNextSelectable;
		ex_weak_ptr<I_Selectable> m_horizontalBeforeSelectable;
		ex_weak_ptr<I_Selectable> m_horizontalNextSelectable;

		bool m_isSelectedLock = false;
	public:
		itbs::Utility::Delegate<void()> pushEvent;

		itbs::Utility::Delegate<void()> selectEvent;

		itbs::Utility::Delegate<void()> outSelectEvent;

		SelectableComponent(std::shared_ptr<GameObject>& owner);

		void SetIsSelectedLock(const bool isSelectedLock);

		bool GetIsSelectedLock() const override;

		virtual void OnSelect() override;

		virtual void OnPush() override;

		virtual void OnOutSelect() override;

		void SetVerticalBeforeSelectable(const std::shared_ptr<I_Selectable>& verticalBeforeSelectable);
		void SetVerticalNextSelectable(const std::shared_ptr<I_Selectable>& verticalNextSelectable);
		void SetHorizontalBeforeSelectable(const std::shared_ptr<I_Selectable>& horizontalBeforeSelectable);
		void SetHorizontalNextSelectable(const std::shared_ptr<I_Selectable>& horizontalNextSelectable);

		std::shared_ptr<I_Selectable> GetVerticalBeforeSelectable() const override;
		std::shared_ptr<I_Selectable> GetVerticalNextSelectable() const override;
		std::shared_ptr<I_Selectable> GetHorizontalBeforeSelectable() const override;
		std::shared_ptr<I_Selectable> GetHorizontalNextSelectable() const override;
	};

	class itbs::Input::I_BasicInputer;

	class EventSystem : public Component
	{
	public:
		static const std::wstring EVENTSYSTEM_OBJECT_KEY;

	private:
		static ex_weak_ptr<EventSystem> m_eventSystem;

		std::shared_ptr<itbs::Input::I_BasicInputer> m_basicInputer;

		ex_weak_ptr<I_Selectable> m_nowSelectable;
		std::stack<ex_weak_ptr<I_Selectable>> m_stackSelectable;

		void MoveCheck(bool(itbs::Input::I_BasicInputer::*isDown)()const, std::shared_ptr<I_Selectable>(I_Selectable::*func)() const);
	public:
		EventSystem(std::shared_ptr<GameObject>& owner);

		void SetNowSelectable(const std::shared_ptr<I_Selectable>& nowSelectable);

		void PushSelectable(const std::shared_ptr<I_Selectable>& nowSelectable);

		void PopSelectable();

		std::shared_ptr<I_Selectable> GetNowSelectable() const;

		static ex_weak_ptr<EventSystem> GetInstance(const std::shared_ptr<Stage>& stage);

		void SetBasicInputer(const std::shared_ptr<itbs::Input::I_BasicInputer>& basicInputer);

		void OnCreate() override;

		void OnUpdate() override;
	};

	/// <summary>
	/// �{�^��UI
	/// </summary>
	class Button : public SelectableComponent
	{
		ex_weak_ptr<Image> m_image;

		std::wstring m_normalButtonImageKey;
		std::wstring m_selectedButtonImageKey;

	public:

		Button(std::shared_ptr<GameObject>& owner);

		void SetNormalButtonImage(const std::wstring& normalButtonImageKey);

		void SetSelectedButtonImage(const std::wstring& selectedButtonImageKey);

		void SetAllButtonImage(const std::wstring& allButtonImageKey);

		void OnSelect() override;

		void OnOutSelect() override;

		void OnCreate() override;
	};

	/// <summary>
	/// UI�pGameObject
	/// </summary>
	class UIObject : public GameObject
	{
	protected:
		ex_weak_ptr<RectTransform> rectTransform;

	public:
		UIObject(std::shared_ptr<Stage>& stage);

		void OnPreCreate() override;
	};
}