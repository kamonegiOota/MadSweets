#pragma once

namespace basecross
{
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

	struct RectData
	{
		Vec2 pivot;

		float width;
		float height;
	};

	class RectTransform : public Component
	{
		/// <summary>
		/// �A���J�[�ɑΉ�����N���C�A���g�̈捶��̒��_�̃I�t�Z�b�g�����}�b�v
		/// </summary>
		static const std::unordered_map<AnchorType, Vec2> m_anchorOffsetTable;

		float m_width;
		float m_height;

		AnchorType m_anchorType = AnchorType::Center;

		Vec2 m_pivot = Vec2(0.0f, 0.0f);

		D2D1::Matrix3x2F m_rotation = D2D1::Matrix3x2F::Identity();
		D2D1::Matrix3x2F m_translation = D2D1::Matrix3x2F::Identity();

	public:
		RectTransform(std::shared_ptr<GameObject>& owner);

		static Vec2 ToWindowPoint(const Vec2& uiPoint);

		void SetAnchor(const AnchorType anchorType);

		AnchorType GetAnhor() const;

		void SetPivot(Vec2 pivot);
		void SetPivot(float x, float y);

		Vec2 GetPivot() const;

		Vec2 GetAnchorOffsetWorldPosition(const AnchorType anchorType) const;

 		Vec2 GetCenterOffsetPosition(const bool isScaleble=true) const;

		void SetWidth(const float width);
		void SetHeight(const float height);
		void SetRectSize(const float width, const float height);

		float GetWidth() const;
		float GetHeight() const;

		Vec2 GetAnchorOffset(const AnchorType anchorType,const bool isScaleble = true) const;

		D2D1::Matrix3x2F GetWorldMatrix() const;

		D2D1::Matrix3x2F GetWorldTranslationMatrix() const;
		D2D1::Matrix3x2F GetWorldRotationMatrix() const;
		D2D1::Matrix3x2F GetWorldScaleMatrix() const;

		std::shared_ptr<RectTransform> GetParentRectTransform() const;

		Vec2 GetParentAnchorOffset(const AnchorType anchorType) const;

		void OnUpdate() override;

		virtual void OnDraw() override {}
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
		/// �A���J�[�ɉ�����vertices��ێ����Ă���}�b�v
		/// </summary>
		static const std::unordered_map<AnchorType, Vec2> m_verticesAnchorTable;

		ex_weak_ptr<RectTransform> rectTransform;

		/// <summary>
		/// �摜�̐؂���̈�̒��_�f�[�^
		/// </summary>
		std::array<Vec2, VERTICES_POINT_NUM> m_UVPoints;

		/// <summary>
		/// ���݂̏�Ԃ�vertices�f�[�^���쐬����
		/// </summary>
		/// <returns>vertices�f�[�^</returns>
		std::vector<VertexPositionColorTexture> CreateVertices() const;

		Vec3 m_localPosition;
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="owner">�Q�[���I�u�W�F�N�g</param>
		/// <param name="width">�`�悷�镝</param>
		/// <param name="height">�`�悷�鍂��</param>
		Image(std::shared_ptr<GameObject>& owner);

		virtual void OnCreate() override;

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
		ex_weak_ptr<RectTransform> rectTransform;
		/// <summary>
		/// �A���J�[�^�C�v
		/// </summary>
		AnchorType m_anchorType = AnchorType::Center;

		TextSideAlignment m_textSideAlignment = TextSideAlignment::Left;
		TextVerticalAlignment m_textVerticalAlignment = TextVerticalAlignment::Up;

		Col4 m_boxColor = Col4();
		ComPtr<ID2D1SolidColorBrush> m_boxBrush;

		ComPtr<ID2D1DrawingStateBlock> m_stateBlock;

		Col4 m_fontColor = Col4(0,0,0,1);
		ComPtr<ID2D1SolidColorBrush> m_fontBrush;

		std::wstring m_fontName = L"�l�r �S�V�b�N";
		float m_fontSize = 16.0f;

		std::wstring m_text;

		ComPtr<IDWriteTextFormat> m_textFormat;
		ComPtr<IDWriteTextLayout> m_textLayout;

		DWRITE_TEXT_METRICS m_textMetrics;

		static const std::unordered_map<TextStyle, DWRITE_FONT_STYLE> m_textStypeToDWriteStyleTable;
		TextStyle m_textStyle = TextStyle::Normal;

		void TextFormatUpdate();
		void TextLayoutUpdate();
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="owner">�Q�[���I�u�W�F�N�g</param>
		TextBox(std::shared_ptr<GameObject>& owner);

		void SetBoxColor(const Col4& color);
		void SetBoxColor(const float red, const float green, const float blue, const float alpha);

		Col4 GetBoxColor() const;

		void SetFontColor(const Col4& color);
		void SetFontColor(const float red, const float green, const float blue, const float alpha);

		Col4 GetFontColor() const;

		/// <summary>
		/// �A���J�[�^�C�v��ݒ肷��
		/// </summary>
		/// <param name="anchorType">�A���J�[�^�C�v</param>
		void SetAnchor(const AnchorType& anchorType);

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

		void SetText(const std::wstring& text);

		std::wstring GetText() const;

		void SetTextSideAlignment(const TextSideAlignment textSideAlignment);

		TextSideAlignment GetTextSideAlignment() const;

		void SetTextVerticalAlignment(const TextVerticalAlignment textVerticalAlignment);

		TextVerticalAlignment GetTextVerticalAlignment() const;

		void SetTextStyle(const TextStyle textStyle);

		TextStyle GetTextStyle() const;

		void OnUpdate() override {}

		void OnDraw() override;
	};
}