#pragma once

namespace basecross
{
	class GameObject;
	class Component;
	class Stage;

	/// <summary>
	/// •\¦‚·‚éÛ‚ÌƒAƒ“ƒJ[ƒ^ƒCƒv
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
	/// UI•`‰æ—pƒgƒ‰ƒ“ƒXƒtƒH[ƒ€
	/// </summary>
	class RectTransform : public Component
	{
		/// <summary>
		/// ƒAƒ“ƒJ[‚É‘Î‰‚·‚éƒNƒ‰ƒCƒAƒ“ƒg—Ìˆæ¶ã‚Ì’¸“_‚ÌƒIƒtƒZƒbƒg‚ğ‚à‚Âƒ}ƒbƒv
		/// </summary>
		static const std::unordered_map<AnchorType, Vec2> m_anchorOffsetTable;

		/// <summary>
		/// ƒ[ƒJƒ‹À•W
		/// </summary>
		Vec2 m_position = Vec2(0, 0);
		/// <summary>
		/// ƒ[ƒJƒ‹‰ñ“]
		/// </summary>
		float m_rotation = 0.0f;
		/// <summary>
		/// ƒ[ƒJƒ‹ƒXƒP[ƒ‹
		/// </summary>
		Vec2 m_scale = Vec2(1.0f, 1.0f);

		/// <summary>
		/// lŠp‚Ì•
		/// </summary>
		float m_width;
		/// <summary>
		/// lŠp‚Ì‚‚³
		/// </summary>
		float m_height;

		/// <summary>
		/// lŠp‚ÌƒAƒ“ƒJ[ƒ^ƒCƒv
		/// </summary>
		AnchorType m_anchorType = AnchorType::Center;

		/// <summary>
		/// ƒsƒ{ƒbƒg
		/// </summary>
		Vec2 m_pivot = Vec2(0.0f, 0.0f);

	public:
		/// <summary>
		/// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
		/// </summary>
		/// <param name="owner">ƒQ[ƒ€ƒIƒuƒWƒFƒNƒg</param>
		RectTransform(std::shared_ptr<GameObject>& owner);

		/// <summary>
		/// UI—pÀ•W‚ğƒEƒBƒ“ƒhƒEÀ•W‚É•ÏŠ·‚·‚é
		/// </summary>
		/// <param name="uiPoint">UI—pÀ•W</param>
		/// <returns>ƒEƒBƒ“ƒhƒEÀ•W</returns>
		static Vec2 ToWindowPoint(const Vec2& uiPoint);

		/// <summary>
		/// ƒAƒ“ƒJ[ƒ^ƒCƒv‚ğİ’è‚·‚é
		/// </summary>
		/// <param name="anchorType">ƒAƒ“ƒJ[ƒ^ƒCƒv</param>
		void SetAnchor(const AnchorType anchorType);

		/// <summary>
		/// ƒAƒ“ƒJ[ƒ^ƒCƒv‚ğæ“¾‚·‚é
		/// </summary>
		/// <returns>ƒAƒ“ƒJ[ƒ^ƒCƒv</returns>
		AnchorType GetAnhor() const;

		/// <summary>
		/// ƒsƒ{ƒbƒg‚ğİ’è‚·‚é
		/// </summary>
		/// <param name="pivot">ƒsƒ{ƒbƒg</param>
		void SetPivot(Vec2 pivot);
		/// <summary>
		/// ƒsƒ{ƒbƒg‚ğİ’è‚·‚é
		/// </summary>
		/// <param name="x">ƒsƒ{ƒbƒgXÀ•W</param>
		/// <param name="y">ƒsƒ{ƒbƒgYÀ•W</param>
		void SetPivot(float x, float y);

		/// <summary>
		/// ƒsƒ{ƒbƒg‚ğæ“¾‚·‚é
		/// </summary>
		/// <returns>ƒsƒ{ƒbƒg</returns>
		Vec2 GetPivot() const;

		/// <summary>
		/// lŠp‚Ì•‚ğİ’è‚·‚é
		/// </summary>
		/// <param name="width">•</param>
		void SetWidth(const float width);
		/// <summary>
		/// lŠp‚Ì‚‚³‚ğİ’è‚·‚é
		/// </summary>
		/// <param name="height">‚‚³</param>
		void SetHeight(const float height);
		/// <summary>
		/// lŠp‚ÌƒTƒCƒY‚ğİ’è‚·‚é
		/// </summary>
		/// <param name="width">•</param>
		/// <param name="height">‚‚³</param>
		void SetRectSize(const float width, const float height);

		/// <summary>
		/// lŠp‚Ì•‚ğæ“¾‚·‚é
		/// </summary>
		/// <returns>•</returns>
		float GetWidth() const;
		/// <summary>
		/// lŠp‚Ì‚‚³‚ğæ“¾‚·‚é
		/// </summary>
		/// <returns>‚‚³</returns>
		float GetHeight() const;

		/// <summary>
		/// ƒ[ƒJƒ‹À•W‚ğİ’è‚·‚é
		/// </summary>
		/// <param name="position">ƒ[ƒJƒ‹À•W</param>
		void SetPosition(const Vec2& position);
		/// <summary>
		/// ƒ[ƒJƒ‹À•W‚ğİ’è‚·‚é
		/// </summary>
		/// <param name="x">ƒ[ƒJƒ‹XÀ•W</param>
		/// <param name="y">ƒ[ƒJƒ‹À•W</param>
		void SetPosition(const float x, const float y);

		/// <summary>
		/// ƒ[ƒJƒ‹À•W‚ğæ“¾‚·‚é
		/// </summary>
		/// <returns>ƒ[ƒJƒ‹À•W</returns>
		Vec2 GetPosition() const;

		/// <summary>
		/// ƒ[ƒJƒ‹‰ñ“]‚ğİ’è‚·‚é
		/// </summary>
		/// <param name="radian">ƒ[ƒJƒ‹Z‰ñ“]</param>
		void SetRotation(const float radian);

		/// <summary>
		/// ƒ[ƒJƒ‹‰ñ“]‚ğæ“¾‚·‚é
		/// </summary>
		/// <returns>ƒ[ƒJƒ‹Z‰ñ“]</returns>
		float GetRotation() const;

		/// <summary>
		/// ƒ[ƒJƒ‹Z‰ñ“]‚ğ’Ç‰Á‚·‚é
		/// </summary>
		/// <param name="radian">’Ç‰Á‚·‚éƒ[ƒJƒ‹Z‰ñ“]</param>
		void Rotate(const float radian);

		/// <summary>
		/// ƒ[ƒJƒ‹ƒXƒP[ƒ‹‚ğİ’è‚·‚és
		/// </summary>
		/// <param name="scale">ƒ[ƒJƒ‹ƒXƒP[ƒ‹</param>
		void SetScale(const Vec2& scale);
		/// <summary>
		/// ƒ[ƒJƒ‹ƒXƒP[ƒ‹‚ğİ’è‚·‚é
		/// </summary>
		/// <param name="x">ƒ[ƒJƒ‹XƒXƒP[ƒ‹</param>
		/// <param name="y">ƒ[ƒJƒ‹YƒXƒP[ƒ‹</param>
		void SetScale(const float x, const float y);

		/// <summary>
		/// ƒ[ƒJƒ‹ƒXƒP[ƒ‹‚ğæ“¾‚·‚é
		/// </summary>
		/// <returns>ƒ[ƒJƒ‹ƒXƒP[ƒ‹</returns>
		Vec2 GetScale() const;

		/// <summary>
		/// ƒ[ƒ‹ƒhƒXƒP[ƒ‹‚ğæ“¾‚·‚é
		/// </summary>
		/// <returns>ƒ[ƒ‹ƒhƒXƒP[ƒ‹</returns>
		Vec2 GetWorldScale() const;

		/// <summary>
		/// ƒsƒ{ƒbƒg‚©‚çó‚¯æ‚Á‚½ƒAƒ“ƒJ[ƒ^ƒCƒv‚Ü‚Å‚Ì’·‚³‚ğ•Ô‚·
		/// </summary>
		/// <param name="anchorType">ƒAƒ“ƒJ[ƒ^ƒCƒv</param>
		/// <param name="isScaleble">ƒXƒP[ƒ‹‚Ì‰e‹¿‚ğó‚¯‚é‚©</param>
		/// <returns>ƒsƒ{ƒbƒg‚©‚çƒAƒ“ƒJ[ƒ^ƒCƒv‚Ì‹——£</returns>
		Vec2 GetAnchorOffset(const AnchorType anchorType,const bool isScaleble = true) const;

		/// <summary>
		/// ƒ[ƒ‹ƒhs—ñ‚ğæ“¾‚·‚é
		/// </summary>
		/// <returns></returns>
		D2D1::Matrix3x2F GetWorldMatrix() const;

		/// <summary>
		/// e‚ÌRectTransform‚ğæ“¾‚·‚é
		/// </summary>
		/// <returns>e‚ÌRectTransform</returns>
		std::shared_ptr<RectTransform> GetParentRectTransform() const;

		/// <summary>
		/// e‚ÌƒAƒ“ƒJ[ƒIƒtƒZƒbƒg‚ğæ“¾‚·‚é
		/// </summary>
		/// <param name="anchorType">ƒAƒ“ƒJ[ƒ^ƒCƒv</param>
		/// <returns>ƒAƒ“ƒJ[ƒIƒtƒZƒbƒg</returns>
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
	/// ‰æ‘œ‚ğ•\¦‚·‚éƒRƒ“ƒ|[ƒlƒ“ƒg
	/// </summary>
	class Image : public PCTSpriteDraw
	{
		/// <summary>
		/// Vertices‚É•K—v‚È’¸“_”
		/// </summary>
		static constexpr int VERTICES_POINT_NUM = 4;

		/// <summary>
		/// ’¸“_ƒf[ƒ^”z—ñ
		/// </summary>
		static const std::vector<uint16_t> m_indices;

		/// <summary>
		/// lŠpƒgƒ‰ƒ“ƒXƒtƒH[ƒ€
		/// </summary>
		ex_weak_ptr<RectTransform> rectTransform;

		/// <summary>
		/// ï¿½æ‘œï¿½Ì“hï¿½ï¿½Â‚Ô‚ï¿½ï¿½^ï¿½Cï¿½v
		/// </summary>
		ImageFillType m_fillType = ImageFillType::None;

		/// <summary>
		/// ï¿½hï¿½ï¿½Â‚Ô‚ï¿½ï¿½ï¿½ï¿½ï¿½ (1.0f ï¿½` 2.0f)
		/// </summary>
		float m_fillAmount = 1.0f;

		/// <summary>
		/// ‰æ‘œ‚ÌØ‚èæ‚è—Ìˆæ‚Ì’¸“_ƒf[ƒ^
		/// </summary>
		std::array<Vec2, VERTICES_POINT_NUM> m_UVPoints;

		/// <summary>
		/// Œ»İ‚Ìó‘Ô‚Ìverticesƒf[ƒ^‚ğì¬‚·‚é
		/// </summary>
		/// <returns>verticesƒf[ƒ^</returns>
		std::vector<VertexPositionColorTexture> CreateVertices() const;

	public:
		/// <summary>
		/// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
		/// </summary>
		/// <param name="owner">ƒQ[ƒ€ƒIƒuƒWƒFƒNƒg</param>
		/// <param name="width">•`‰æ‚·‚é•</param>
		/// <param name="height">•`‰æ‚·‚é‚‚³</param>
		Image(std::shared_ptr<GameObject>& owner);


		/// <summary>
		/// ‰æ‘œ‚ÌØ‚èæ‚è—Ìˆæ‚ğİ’è‚·‚é
		/// </summary>
		/// <param name="leftUpPoint">Ø‚èæ‚è—Ìˆæ‚Ì¶ã‚Ì’¸“_‚ÌÀ•W</param>
		/// <param name="width">Ø‚èæ‚è—Ìˆæ‚Ì•</param>
		/// <param name="height">Ø‚èæ‚è—Ìˆæ‚Ì‚‚³</param>
		/// <param name="imageSize">Œ³‰æ‘œ‚Ì•‚Æ‚‚³</param>
		void SetUVRect(const Vec2& leftUpPoint,const float width,const float height,Vec2& imageSize);

		/// <summary>
		/// Alpha’l‚ğİ’è‚·‚é
		/// </summary>
		/// <param name="alpha">Alpha’l</param>
		void SetAlpha(const float alpha);

		/// <summary>
		/// Alpha’l‚ğæ“¾‚·‚é
		/// </summary>
		/// <returns>Alpha’l</returns>
		float GetAlpha() const;

		/// <summary>
		/// ï¿½hï¿½ï¿½Â‚Ô‚ï¿½ï¿½^ï¿½Cï¿½vï¿½ï¿½İ’è‚·ï¿½ï¿½
		/// </summary>
		/// <param name="fillType">ï¿½hï¿½ï¿½Â‚Ô‚ï¿½ï¿½^ï¿½Cï¿½v</param>
		void SetFillType(const ImageFillType fillType);

		/// <summary>
		/// ï¿½hï¿½ï¿½Â‚Ô‚ï¿½ï¿½^ï¿½Cï¿½vï¿½ï¿½æ“¾ï¿½ï¿½ï¿½ï¿½
		/// </summary>
		/// <returns></returns>
		ImageFillType GetFillType() const;

		/// <summary>
		/// ï¿½hï¿½ï¿½Â‚Ô‚ï¿½ï¿½Ê‚ï¿½İ’è‚·ï¿½ï¿½
		/// </summary>
		/// <param name="fillAmount">ï¿½hï¿½ï¿½Â‚Ô‚ï¿½ï¿½ï¿½</param>
		void SetFillAmount(const float fillAmount);

		/// <summary>
		/// ï¿½hï¿½ï¿½Â‚Ô‚ï¿½ï¿½Ê‚ï¿½æ“¾ï¿½ï¿½ï¿½ï¿½
		/// </summary>
		/// <returns>ï¿½hï¿½ï¿½Â‚Ô‚ï¿½ï¿½ï¿½</returns>
		float GetFillAmount() const;

		virtual void OnCreate() override;

		void OnUpdate() override;
	};

	/// <summary>
	/// ƒeƒLƒXƒg‚ğ•\¦‚·‚éƒRƒ“ƒ|[ƒlƒ“ƒg
	/// </summary>
	class TextBox : public Component
	{
	public:

		/// <summary>
		/// Box‚Ìc•ûŒü‚É‘Î‚µ‚ÄAText‚ª‚Ç‚ÌˆÊ’u‚É‚ ‚é‚©
		/// </summary>
		enum class TextVerticalAlignment
		{
			/// <summary>
			/// ã‹l‚ß
			/// </summary>
			Up,
			/// <summary>
			/// ’†‰›Šñ‚¹
			/// </summary>
			Center,
			/// <summary>
			/// ‰º‹l‚ß
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
		/// ƒeƒLƒXƒgƒXƒ^ƒCƒ‹‚É‘Î‚µ‚ÄDWRITE_FONT_STYLE‚É•ÏŠ·‚·‚éƒe[ƒuƒ‹
		/// </summary>
		static const std::unordered_map<TextStyle, DWRITE_FONT_STYLE> m_textStypeToDWriteStyleTable;

		/// <summary>
		/// lŠpƒgƒ‰ƒ“ƒXƒtƒH[ƒ€
		/// </summary>
		ex_weak_ptr<RectTransform> rectTransform;
		/// <summary>
		/// ƒeƒLƒXƒg‚Ì‰¡‚É‘Î‚·‚éˆÊ’u
		/// </summary>
		TextSideAlignment m_textSideAlignment = TextSideAlignment::Left;
		/// <summary>
		/// ƒeƒLƒXƒg‚Ìc‚É‘Î‚·‚éˆÊ’u
		/// </summary>
		TextVerticalAlignment m_textVerticalAlignment = TextVerticalAlignment::Up;

		/// <summary>
		/// ƒ{ƒbƒNƒX‚ÌF
		/// </summary>
		Col4 m_boxColor = Col4();
		/// <summary>
		/// ƒ{ƒbƒNƒX•`‰æ—pFƒuƒ‰ƒV
		/// </summary>
		ComPtr<ID2D1SolidColorBrush> m_boxBrush;

		/// <summary>
		/// ƒtƒHƒ“ƒg‚ÌF
		/// </summary>
		Col4 m_fontColor = Col4(0,0,0,1);
		/// <summary>
		/// ƒtƒHƒ“ƒg‚Ì•`‰æ—pFƒuƒ‰ƒVS
		/// </summary>
		ComPtr<ID2D1SolidColorBrush> m_fontBrush;

		/// <summary>
		/// ƒXƒe[ƒgƒuƒƒbƒN
		/// </summary>
		ComPtr<ID2D1DrawingStateBlock> m_stateBlock;

		/// <summary>
		/// ƒtƒHƒ“ƒg–¼
		/// </summary>
		std::wstring m_fontName = L"‚l‚r ƒSƒVƒbƒN";

		/// <summary>
		/// ƒtƒHƒ“ƒgƒTƒCƒY
		/// </summary>
		float m_fontSize = 16.0f;

		/// <summary>
		/// ƒeƒLƒXƒg
		/// </summary>
		std::wstring m_text;

		/// <summary>
		/// ƒeƒLƒXƒgƒtƒH[ƒ}ƒbƒg
		/// </summary>
		ComPtr<IDWriteTextFormat> m_textFormat;
		/// <summary>
		/// ƒeƒLƒXƒgƒŒƒCƒAƒEƒg
		/// </summary>
		ComPtr<IDWriteTextLayout> m_textLayout;

		/// <summary>
		/// ƒeƒLƒXƒgƒƒgƒŠƒNƒXs
		/// </summary>
		DWRITE_TEXT_METRICS m_textMetrics;

		/// <summary>
		/// ƒeƒLƒXƒgƒXƒ^ƒCƒ‹
		/// </summary>
		TextStyle m_textStyle = TextStyle::Normal;

		/// <summary>
		/// ƒeƒLƒXƒg‚ÌƒtƒH[ƒ}ƒbƒg‚ğXV‚·‚é
		/// </summary>
		void TextFormatUpdate();
		/// <summary>
		/// ƒeƒLƒXƒg‚ÌƒŒƒCƒAƒEƒg‚ğXV‚·‚é
		/// </summary>
		void TextLayoutUpdate();
	public:
		/// <summary>
		/// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
		/// </summary>
		/// <param name="owner">ƒQ[ƒ€ƒIƒuƒWƒFƒNƒg</param>
		TextBox(std::shared_ptr<GameObject>& owner);

		/// <summary>
		/// ƒ{ƒbƒNƒX‚ÌF‚ğİ’è‚·‚é
		/// </summary>
		/// <param name="color">ƒ{ƒbƒNƒX‚ÌF</param>
		void SetBoxColor(const Col4& color);
		/// <summary>
		/// ƒ{ƒbƒNƒX‚ÌF‚ğİ’è‚·‚é
		/// </summary>
		/// <param name="red">Ô</param>
		/// <param name="green">—Î</param>
		/// <param name="blue">Â</param>
		/// <param name="alpha">“§–¾“x</param>
		void SetBoxColor(const float red, const float green, const float blue, const float alpha);

		/// <summary>
		/// ƒ{ƒbƒNƒX‚ÌF‚ğæ“¾‚·‚é
		/// </summary>
		/// <returns>ƒ{ƒbƒNƒX‚ÌF</returns>
		Col4 GetBoxColor() const;

		/// <summary>
		/// ƒtƒHƒ“ƒg‚ÌF‚ğİ’è‚·‚é
		/// </summary>
		/// <param name="color">ƒtƒHƒ“ƒg‚ÌF</param>
		void SetFontColor(const Col4& color);
		/// <summary>
		/// ƒtƒHƒ“ƒg‚ÌF‚ğİ’è‚·‚é
		/// </summary>
		/// <param name="red">Ô</param>
		/// <param name="green">—Î</param>
		/// <param name="blue">Â</param>
		/// <param name="alpha">“§–¾“x</param>
		void SetFontColor(const float red, const float green, const float blue, const float alpha);

		/// <summary>
		/// ƒtƒHƒ“ƒg‚ÌF‚ğæ“¾‚·‚é
		/// </summary>
		/// <returns>ƒtƒHƒ“ƒg‚ÌF</returns>
		Col4 GetFontColor() const;

		/// <summary>
		/// ƒtƒHƒ“ƒg‚Ìš‘Ì‚ğİ’è‚·‚é
		/// </summary>
		/// <param name="fontName">ƒtƒHƒ“ƒg–¼</param>
		void SetFontName(const std::wstring& fontName);

		/// <summary>
		/// ƒtƒHƒ“ƒg‚ÌƒTƒCƒY‚ğİ’è‚·‚é
		/// </summary>
		/// <param name="fontSize">ƒtƒHƒ“ƒgƒTƒCƒY</param>
		void SetFontSize(const float fontSize);

		/// <summary>
		/// TextBox‘S‘Ì‚ÌAlpha’l‚ğİ’è‚·‚é
		/// </summary>
		/// <param name="alpha">Alpha’l</param>
		void SetAlpha(const float alpha);

		/// <summary>
		/// ƒeƒLƒXƒg‚ğİ’è‚·‚é
		/// </summary>
		/// <param name="text">İ’è‚·‚éƒeƒLƒXƒg</param>
		void SetText(const std::wstring& text);

		/// <summary>
		/// ƒeƒLƒXƒg‚ğ’Ç‰Á‚·‚é
		/// </summary>
		/// <param name="text">’Ç‰Á‚·‚éƒeƒLƒXƒg</param>
		void AddText(const std::wstring& text);

		/// <summary>
		/// ƒeƒLƒXƒg‚ğæ“¾‚·‚é
		/// </summary>
		/// <returns>ƒeƒLƒXƒg</returns>
		std::wstring GetText() const;

		/// <summary>
		/// ƒeƒLƒXƒg‚Ì‰¡‚É‘Î‚·‚éˆÊ’u‚ğİ’è‚·‚é
		/// </summary>
		/// <param name="textSideAlignment">‰¡‚É‘Î‚·‚éˆÊ’u</param>
		void SetTextSideAlignment(const TextSideAlignment textSideAlignment);

		/// <summary>
		/// ƒeƒLƒXƒg‚Ì‰¡‚É‘Î‚·‚éˆÊ’u‚ğæ“¾‚·‚é
		/// </summary>
		/// <returns>‰¡‚É‘Î‚·‚éˆÊ’u</returns>
		TextSideAlignment GetTextSideAlignment() const;

		/// <summary>
		/// ƒeƒLƒXƒg‚Ìc‚É‘Î‚·‚éˆÊ’u‚ğİ’è‚·‚é
		/// </summary>
		/// <param name="textVerticalAlignment">c‚É‘Î‚·‚éˆÊ’u</param>
		void SetTextVerticalAlignment(const TextVerticalAlignment textVerticalAlignment);

		/// <summary>
		/// ƒeƒLƒXƒg‚Ìc‚É‘Î‚·‚éˆÊ’u‚ğæ“¾‚·‚é
		/// </summary>
		/// <returns>c‚É‘Î‚·‚éˆÊ’u</returns>
		TextVerticalAlignment GetTextVerticalAlignment() const;

		/// <summary>
		/// ƒeƒLƒXƒgƒXƒ^ƒCƒ‹‚ğİ’è‚·‚é
		/// </summary>
		/// <param name="textStyle">ƒeƒLƒXƒgƒXƒ^ƒCƒ‹</param>
		void SetTextStyle(const TextStyle textStyle);

		/// <summary>
		/// ƒeƒLƒXƒgƒXƒ^ƒCƒ‹‚ğæ“¾‚·‚é
		/// </summary>
		/// <returns>ƒeƒLƒXƒgƒXƒ^ƒCƒ‹</returns>
		TextStyle GetTextStyle() const;

		void OnUpdate() override {}

		void OnDraw() override;
	};
}