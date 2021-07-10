#pragma once

namespace basecross
{
	/// <summary>
	/// 表示する際のアンカータイプ
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
		/// アンカーに対応するクライアント領域左上の頂点のオフセットをもつマップ
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
	/// 画像を表示するコンポーネント
	/// </summary>
	class Image : public PCTSpriteDraw
	{
		/// <summary>
		/// Verticesに必要な頂点数
		/// </summary>
		static constexpr int VERTICES_POINT_NUM = 4;

		/// <summary>
		/// 頂点データ配列
		/// </summary>
		static const std::vector<uint16_t> m_indices;

		/// <summary>
		/// アンカーに応じたverticesを保持しているマップ
		/// </summary>
		static const std::unordered_map<AnchorType, Vec2> m_verticesAnchorTable;

		ex_weak_ptr<RectTransform> rectTransform;

		/// <summary>
		/// 画像の切り取り領域の頂点データ
		/// </summary>
		std::array<Vec2, VERTICES_POINT_NUM> m_UVPoints;

		/// <summary>
		/// 現在の状態のverticesデータを作成する
		/// </summary>
		/// <returns>verticesデータ</returns>
		std::vector<VertexPositionColorTexture> CreateVertices() const;

		Vec3 m_localPosition;
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="owner">ゲームオブジェクト</param>
		/// <param name="width">描画する幅</param>
		/// <param name="height">描画する高さ</param>
		Image(std::shared_ptr<GameObject>& owner);

		virtual void OnCreate() override;

		/// <summary>
		/// 画像の切り取り領域を設定する
		/// </summary>
		/// <param name="leftUpPoint">切り取り領域の左上の頂点の座標</param>
		/// <param name="width">切り取り領域の幅</param>
		/// <param name="height">切り取り領域の高さ</param>
		/// <param name="imageSize">元画像の幅と高さ</param>
		void SetUVRect(const Vec2& leftUpPoint,const float width,const float height,Vec2& imageSize);

		/// <summary>
		/// Alpha値を設定する
		/// </summary>
		/// <param name="alpha">Alpha値</param>
		void SetAlpha(const float alpha);

		/// <summary>
		/// Alpha値を取得する
		/// </summary>
		/// <returns>Alpha値</returns>
		float GetAlpha() const;

		void OnUpdate() override;
	};

	/// <summary>
	/// テキストを表示するコンポーネント
	/// </summary>
	class TextBox : public Component
	{
	public:

		/// <summary>
		/// Boxの縦方向に対して、Textがどの位置にあるか
		/// </summary>
		enum class TextVerticalAlignment
		{
			/// <summary>
			/// 上詰め
			/// </summary>
			Up,
			/// <summary>
			/// 中央寄せ
			/// </summary>
			Center,
			/// <summary>
			/// 下詰め
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
		/// アンカータイプ
		/// </summary>
		AnchorType m_anchorType = AnchorType::Center;

		TextSideAlignment m_textSideAlignment = TextSideAlignment::Left;
		TextVerticalAlignment m_textVerticalAlignment = TextVerticalAlignment::Up;

		Col4 m_boxColor = Col4();
		ComPtr<ID2D1SolidColorBrush> m_boxBrush;

		ComPtr<ID2D1DrawingStateBlock> m_stateBlock;

		Col4 m_fontColor = Col4(0,0,0,1);
		ComPtr<ID2D1SolidColorBrush> m_fontBrush;

		std::wstring m_fontName = L"ＭＳ ゴシック";
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
		/// コンストラクタ
		/// </summary>
		/// <param name="owner">ゲームオブジェクト</param>
		TextBox(std::shared_ptr<GameObject>& owner);

		void SetBoxColor(const Col4& color);
		void SetBoxColor(const float red, const float green, const float blue, const float alpha);

		Col4 GetBoxColor() const;

		void SetFontColor(const Col4& color);
		void SetFontColor(const float red, const float green, const float blue, const float alpha);

		Col4 GetFontColor() const;

		/// <summary>
		/// アンカータイプを設定する
		/// </summary>
		/// <param name="anchorType">アンカータイプ</param>
		void SetAnchor(const AnchorType& anchorType);

		/// <summary>
		/// フォントの字体を設定する
		/// </summary>
		/// <param name="fontName">フォント名</param>
		void SetFontName(const std::wstring& fontName);

		/// <summary>
		/// フォントのサイズを設定する
		/// </summary>
		/// <param name="fontSize">フォントサイズ</param>
		void SetFontSize(const float fontSize);

		/// <summary>
		/// TextBox全体のAlpha値を設定する
		/// </summary>
		/// <param name="alpha">Alpha値</param>
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