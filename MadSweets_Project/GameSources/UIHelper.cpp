#include"UIHelper.h"
#include"WindowSetting.h"

namespace basecross
{
	// RectTransform ----------------------------
	
	const std::unordered_map<AnchorType, Vec2> RectTransform::m_anchorOffsetTable =
	{
		std::make_pair(AnchorType::Center, Vec2(0.0f, 0.0f)),
		std::make_pair(AnchorType::Up, Vec2(0.0f, 0.5f)),
		std::make_pair(AnchorType::Down, Vec2(0.0f, -0.5f)),
		std::make_pair(AnchorType::Left, Vec2(-0.5f, 0.0f)),
		std::make_pair(AnchorType::LeftUp, Vec2(-0.5f, 0.5f)),
		std::make_pair(AnchorType::LeftDown, Vec2(-0.5f, -0.5f)),
		std::make_pair(AnchorType::Right, Vec2(0.5f, 0.0f)),
		std::make_pair(AnchorType::RightUp, Vec2(0.5f, 0.5f)),
		std::make_pair(AnchorType::RightDown, Vec2(0.5f, -0.5f))
	};

	RectTransform::RectTransform(std::shared_ptr<GameObject>& owner) :
		Component(owner)
	{
		
	}

	Vec2 RectTransform::ToWindowPoint(const Vec2& uiPoint)
	{
		Vec2 windowPoint;

		windowPoint.x = uiPoint.x + WindowSetting::WINDOW_WIDTH * 0.5f;
		windowPoint.y = -uiPoint.y + WindowSetting::WINDOW_HEIGHT * 0.5f;

		return windowPoint;
	}

	Vec2 RectTransform::GetParentAnchorOffset(const AnchorType anchorType) const
	{
		auto parentTransform = GetParentRectTransform();

		if (parentTransform)
		{
			return parentTransform->GetAnchorOffset(anchorType);
		}

		Vec2 anchorOffset = m_anchorOffsetTable.at(anchorType);

		return Vec2(WindowSetting::WINDOW_WIDTH * anchorOffset.x, WindowSetting::WINDOW_HEIGHT * anchorOffset.y);
	}


	void RectTransform::SetAnchor(const AnchorType anchorType)
	{
		m_anchorType = anchorType;
	}

	AnchorType RectTransform::GetAnhor() const
	{
		return m_anchorType;
	}

	void RectTransform::SetPivot(Vec2 pivot)
	{
		pivot.x = std::fmaxf(-0.5f, pivot.x);
		pivot.x = std::fminf( 0.5f, pivot.x);
		pivot.y = std::fmaxf(-0.5f, pivot.y);
		pivot.y = std::fminf( 0.5f, pivot.y);

		m_pivot = pivot;
	}

	void RectTransform::SetPivot(float x, float y)
	{
		SetPivot(Vec2(x, y));
	}

	Vec2 RectTransform::GetPivot() const
	{
		return m_pivot;
	}

	Vec2 RectTransform::GetAnchorOffsetWorldPosition(const AnchorType anchorType) const
	{
		Vec2 anchorOffset = m_anchorOffsetTable.at(anchorType);
		anchorOffset.y = 1.0f - anchorOffset.y;
		Vec2 offset = anchorOffset - m_pivot;

		auto scale = transform->GetWorldScale();

		return GetCenterOffsetPosition() + Vec2(m_width * offset.x * scale.x, m_height * offset.y * scale.y);
	}

	Vec2 RectTransform::GetCenterOffsetPosition(const bool isScaleble) const
	{

		auto parentRectTransform = GetParentRectTransform();

		auto position = Vec2(transform->GetPosition().x, transform->GetPosition().y);

		if (!parentRectTransform)
		{
			return position + GetParentAnchorOffset(m_anchorType);
		}

		auto parentAnchorOffset = parentRectTransform->GetCenterOffsetPosition() + GetParentAnchorOffset(m_anchorType);

		auto parentScale = isScaleble ? transform->GetParent()->GetComponent<Transform>()->GetWorldScale() : Vec3(1,1,1);

		auto positionOffset = Vec2(position.x * parentScale.x, position.y * parentScale.y);

		return parentAnchorOffset + positionOffset;
	}

	void RectTransform::SetWidth(const float width)
	{
		m_width = width;
	}

	void RectTransform::SetHeight(const float height)
	{
		m_height = height;
	}

	void RectTransform::SetRectSize(const float width, const float height)
	{
		m_width = width;
		m_height = height;
	}

	float RectTransform::GetWidth() const
	{
		return m_width;
	}

	float RectTransform::GetHeight() const
	{
		return m_height;
	}

	Vec2 RectTransform::GetAnchorOffset(const AnchorType anchorType,const bool isScaleble) const
	{
		Vec2 anchorOffset = m_anchorOffsetTable.at(anchorType);

		Vec2 offset = anchorOffset - m_pivot;

		Vec3 scale = isScaleble ? transform->GetWorldScale() : Vec3(1, 1, 1);

		return Vec2(m_width * scale.x * offset.x, m_height * scale.y * offset.y);
	}

	D2D1::Matrix3x2F RectTransform::GetWorldMatrix() const
	{
		auto centerPosition = ToWindowPoint(GetCenterOffsetPosition(false));
		auto point2F = D2D1::Point2F(centerPosition.x, centerPosition.y);

		point2F = D2D1::Point2F();

		auto position = transform->GetPosition();
		
		auto offsetPosition = GetParentAnchorOffset(m_anchorType);
		auto windowPosition = Vec2(position.x, position.y) + GetParentAnchorOffset(m_anchorType);
		auto positionMatrix = D2D1::Matrix3x2F::Translation(D2D1::SizeF(windowPosition.x, -windowPosition.y));

		auto rotation = transform->GetQuaternion().toRotVec();
		auto rotationMatrix = D2D1::Matrix3x2F::Rotation(XMConvertToDegrees(-rotation.z), point2F);

		auto scale = transform->GetScale();
		auto scaleMatrix = D2D1::Matrix3x2F::Scale(D2D1::SizeF(scale.x, scale.y), point2F);

		auto worldMatrix = scaleMatrix * rotationMatrix * positionMatrix;

		auto parentRectTransform = GetParentRectTransform();

		if (parentRectTransform)
		{
			return worldMatrix * parentRectTransform->GetWorldMatrix();
		}

		return worldMatrix;
	}
	D2D1::Matrix3x2F RectTransform::GetWorldTranslationMatrix() const
	{
		auto position = transform->GetPosition();

		auto offsetPosition = GetParentAnchorOffset(m_anchorType);
		auto windowPosition = Vec2(position.x, position.y) + GetParentAnchorOffset(m_anchorType);
		auto positionMatrix = D2D1::Matrix3x2F::Translation(D2D1::SizeF(windowPosition.x, -windowPosition.y));

		auto parentRectTransform = GetParentRectTransform();

		if (!parentRectTransform)
		{
			return positionMatrix;
		}

		return positionMatrix * parentRectTransform->GetWorldTranslationMatrix();
	}

	D2D1::Matrix3x2F RectTransform::GetWorldRotationMatrix() const
	{ 
		auto centerPosition = ToWindowPoint(GetCenterOffsetPosition(false));
		auto point2F = D2D1::Point2F(centerPosition.x, centerPosition.y);

		auto rotation = transform->GetQuaternion().toRotVec();
		auto rotationMatrix = D2D1::Matrix3x2F::Rotation(XMConvertToDegrees(-rotation.z), point2F);

		auto parentRectTransform = GetParentRectTransform();

		if (!parentRectTransform)
		{
			return rotationMatrix;
		}

		return rotationMatrix * parentRectTransform->GetWorldRotationMatrix();
	}

	D2D1::Matrix3x2F RectTransform::GetWorldScaleMatrix() const
	{
		auto centerPosition = ToWindowPoint(GetCenterOffsetPosition());
		auto point2F = D2D1::Point2F(centerPosition.x, centerPosition.y);

		auto scale = transform->GetScale();
		auto scaleMatrix = D2D1::Matrix3x2F::Scale(D2D1::SizeF(scale.x, scale.y), point2F);

		auto parentRectTransform = GetParentRectTransform();

		if (!parentRectTransform)
		{
			return scaleMatrix;
		}

		return scaleMatrix * parentRectTransform->GetWorldScaleMatrix();
	}
	std::shared_ptr<RectTransform> RectTransform::GetParentRectTransform() const
	{
		auto parent = GetGameObject()->GetParent();

		if (!parent)
		{
			return nullptr;
		}

		return parent->GetComponent<RectTransform>(false);
	}

	void RectTransform::OnUpdate()
	{
	}
	// Image ------------------------------------

	const std::vector<uint16_t> Image::m_indices = { 0,1,2, 2,1,3 };

	const std::unordered_map<AnchorType, Vec2> Image::m_verticesAnchorTable =
	{
		std::make_pair(AnchorType::Center,Vec2(0.5f,0.5f)),
		std::make_pair(AnchorType::Up,Vec2(0.5f,0.0f)),
		std::make_pair(AnchorType::Down,Vec2(0.5f,1.0f)),
		std::make_pair(AnchorType::Left,Vec2(0.0f,0.5f)),
		std::make_pair(AnchorType::LeftUp,Vec2(0.0f,0.0f)),
		std::make_pair(AnchorType::LeftDown,Vec2(0.0f,1.0f)),
		std::make_pair(AnchorType::Right,Vec2(1.0f,0.5f)),
		std::make_pair(AnchorType::RightUp,Vec2(1.0f,0.0f)),
		std::make_pair(AnchorType::RightDown,Vec2(1.0f,1.0f))
	};

	Image::Image(std::shared_ptr<GameObject>& owner) :
		PCTSpriteDraw(owner),
		m_UVPoints({
			Vec2(0.0f,0.0f),
			Vec2(1.0f,0.0f),
			Vec2(0.0f,1.0f),
			Vec2(1.0f,1.0f)
			})
	{
		SetBlendState(BlendState::AlphaBlend);
		rectTransform = owner->GetComponent<RectTransform>();
	}

	std::vector<VertexPositionColorTexture> Image::CreateVertices() const
	{
		Vec2 pivot = rectTransform->GetPivot();
		Col4 color = GetDiffuse();

		float width = rectTransform->GetWidth();
		float height = rectTransform->GetHeight();

		std::vector<VertexPositionColorTexture> vertices = {
			{Vec3(width * (-0.5f - pivot.x),height * ( 0.5f - pivot.y), 0), color, m_UVPoints[0]},
			{Vec3(width * ( 0.5f - pivot.x),height * ( 0.5f - pivot.y), 0), color, m_UVPoints[1]},
			{Vec3(width * (-0.5f - pivot.x),height * (-0.5f - pivot.y), 0), color, m_UVPoints[2]} ,
			{Vec3(width * ( 0.5f - pivot.x),height * (-0.5f - pivot.y), 0), color, m_UVPoints[3]}
		};

		return vertices;

	}

	void Image::OnCreate()
	{
		PCTSpriteDraw::OnCreate();

		UpdateVertices(CreateVertices());
	}

	void Image::SetUVRect(const Vec2& leftUpPoint, const float width, const float height, Vec2& imageSize)
	{
		for (auto& point : m_UVPoints)
		{
			point = leftUpPoint;
		}

		m_UVPoints[1].x += width;
		m_UVPoints[2].y += height;
		m_UVPoints[3] += Vec2(width, height);

		for (auto& point : m_UVPoints)
		{
			point.x /= imageSize.x;
			point.y /= imageSize.y;
		}

		UpdateVertices(CreateVertices());
	}

	void Image::SetAlpha(const float alpha)
	{
		auto color = GetDiffuse();
		color.w = alpha;
		SetDiffuse(color);
	}

	float Image::GetAlpha() const
	{
		auto color = GetDiffuse();
		return color.w;
	}

	void Image::OnUpdate()
	{
		auto parentRectTransform = rectTransform->GetParentRectTransform();

		auto offset = parentRectTransform->GetAnchorOffsetWorldPosition(rectTransform->GetAnhor());

		auto position = transform->GetPosition();

		if (m_localPosition != position)
		{
			m_localPosition = position;
			transform->SetPosition(Vec3(offset.x, offset.y, 0));
		}
	}
	// TextBox ------------------------

	const std::unordered_map<TextBox::TextStyle, DWRITE_FONT_STYLE> TextBox::m_textStypeToDWriteStyleTable = {
		std::make_pair(TextBox::TextStyle::Normal,DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL),
		std::make_pair(TextBox::TextStyle::Italic,DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_ITALIC),
		std::make_pair(TextBox::TextStyle::Oblique,DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_OBLIQUE)
	};

	TextBox::TextBox(std::shared_ptr<GameObject>& owner) :
		Component(owner)
	{
		rectTransform = owner->GetComponent<RectTransform>();

		// デバイスに依存するリソースを作成します。
		auto Dev = App::GetApp()->GetDeviceResources();
		auto D2DFactory = Dev->GetD2DFactory();
		auto DWriteFactory = Dev->GetDWriteFactory();
		auto D2DDeviceContext = Dev->GetD2DDeviceContext();

		SetFontColor(m_fontColor);

		SetBoxColor(m_boxColor);

		TextFormatUpdate();

		TextLayoutUpdate();

		D2DFactory->CreateDrawingStateBlock(&m_stateBlock);
	}

	void TextBox::TextFormatUpdate()
	{
		auto deviceResources = App::GetApp()->GetDeviceResources();
		auto DWriteFactory = deviceResources->GetDWriteFactory();

		DWriteFactory->CreateTextFormat(
			m_fontName.c_str(),
			NULL,
			DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_NORMAL,
			m_textStypeToDWriteStyleTable.at(m_textStyle),
			DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL,
			m_fontSize,
			L"ja",
			&m_textFormat
		);
	}

	void TextBox::TextLayoutUpdate()
	{
		auto Dev = App::GetApp()->GetDeviceResources();
		auto D2DDeviceContext = Dev->GetD2DDeviceContext();
		auto DWriteFactory = Dev->GetDWriteFactory();

		DWriteFactory->CreateTextLayout(
			m_text.c_str(),
			(uint32)m_text.length(),
			m_textFormat.Get(),
			rectTransform->GetWidth(), // 入力テキストの最大幅。
			rectTransform->GetHeight(), // 入力テキストの最大高さ。
			&m_textLayout
		);

		m_textLayout->GetMetrics(&m_textMetrics);

		SetTextSideAlignment(m_textSideAlignment);
	}

	void TextBox::SetBoxColor(const Col4& color)
	{
		m_boxColor = color;

		auto colorF = D2D1::ColorF(color.x, color.y, color.z, color.w);

		auto deviceResources = App::GetApp()->GetDeviceResources();
		auto D2DDeviceContext = deviceResources->GetD2DDeviceContext();

		D2DDeviceContext->CreateSolidColorBrush(colorF, &m_boxBrush);
	}

	void TextBox::SetBoxColor(const float red, const float green, const float blue, const float alpha)
	{
		SetBoxColor(Col4(red, green, blue, alpha));
	}

	Col4 TextBox::GetBoxColor() const
	{
		return m_boxColor;
	}

	void TextBox::SetFontColor(const Col4& color)
	{
		m_fontColor = color;

		auto colorF = D2D1::ColorF(color.x, color.y, color.z, color.w);

		auto deviceResources = App::GetApp()->GetDeviceResources();
		auto D2DDeviceContext = deviceResources->GetD2DDeviceContext();

		D2DDeviceContext->CreateSolidColorBrush(colorF, &m_fontBrush);
	}

	void TextBox::SetFontColor(const float red, const float green, const float blue, const float alpha)
	{
		TextBox::SetFontColor(Col4(red, green, blue, alpha));
	}

	Col4 TextBox::GetFontColor() const
	{
		return m_fontColor;
	}

	void TextBox::SetAnchor(const AnchorType& anchorType)
	{
		m_anchorType = anchorType;
	}

	void TextBox::SetFontName(const std::wstring& fontName)
	{
		m_fontName = fontName;

		TextFormatUpdate();
	}

	void TextBox::SetFontSize(const float fontSize)
	{
		m_fontSize = fontSize;

		TextFormatUpdate();
	}

	void TextBox::SetAlpha(const float alpha)
	{
		Col4 color = GetFontColor();
		color.w = alpha;
		SetFontColor(color);

		color = GetBoxColor();
		color.w = alpha;
		SetBoxColor(color);
	}

	void TextBox::SetText(const std::wstring& text)
	{
		m_text = text;
	}

	std::wstring TextBox::GetText() const
	{
		return m_text;
	}

	void TextBox::SetTextSideAlignment(const TextSideAlignment textSideAlignment)
	{
		m_textSideAlignment = textSideAlignment;

		DWRITE_TEXT_ALIGNMENT alignment;

		switch (m_textSideAlignment)
		{
		case basecross::TextBox::TextSideAlignment::Left:
			alignment = DWRITE_TEXT_ALIGNMENT_LEADING;
			break;
		case basecross::TextBox::TextSideAlignment::Center:
			alignment = DWRITE_TEXT_ALIGNMENT_CENTER;
			break;
		case basecross::TextBox::TextSideAlignment::Right:
			alignment = DWRITE_TEXT_ALIGNMENT_TRAILING;
			break;
		}

		m_textLayout->SetTextAlignment(alignment);
	}

	TextBox::TextSideAlignment TextBox::GetTextSideAlignment() const
	{
		return m_textSideAlignment;
	}

	void TextBox::SetTextVerticalAlignment(const TextVerticalAlignment textVerticalAlignment)
	{
		m_textVerticalAlignment = textVerticalAlignment;
	}

	TextBox::TextVerticalAlignment TextBox::GetTextVerticalAlignment() const
	{
		return m_textVerticalAlignment;
	}

	void TextBox::SetTextStyle(const TextStyle textStyle)
	{
		m_textStyle = textStyle;
		TextFormatUpdate();
	}

	TextBox::TextStyle TextBox::GetTextStyle() const
	{
		return m_textStyle;
	}

	void TextBox::OnDraw()
	{
		auto deviceResources = App::GetApp()->GetDeviceResources();
		auto D2DDeviceContext = deviceResources->GetD2DDeviceContext();
		auto DWriteFactory = deviceResources->GetDWriteFactory();

		auto defaultTranslation = D2D1::Matrix3x2F::Translation(D2D1::SizeF(
			WindowSetting::WINDOW_WIDTH * 0.5f,
			WindowSetting::WINDOW_HEIGHT * 0.5f
		));

		auto translation = defaultTranslation * rectTransform->GetWorldTranslationMatrix();
		auto rotation = rectTransform->GetWorldRotationMatrix();
		auto scale = rectTransform->GetWorldScaleMatrix();

		auto worldMatrix = rectTransform->GetWorldMatrix();

		//D2DDeviceContext->SetTransform(translation * scale * rotation);

		D2DDeviceContext->SetTransform(worldMatrix * defaultTranslation);

		Vec2 offset = rectTransform->GetPivot();

		float width = rectTransform->GetWidth();
		float height = rectTransform->GetHeight();

		D2D1_RECT_F boxRectangle = D2D1::RectF(
			width * (-0.5f - offset.x), height * (-0.5f + offset.y),
			width * ( 0.5f - offset.x), height * ( 0.5f + offset.y)
		);

		D2DDeviceContext->SaveDrawingState(m_stateBlock.Get());
		D2DDeviceContext->BeginDraw();

		//バックグラウンドの描画
		D2DDeviceContext->FillRectangle(&boxRectangle, m_boxBrush.Get());

		float heightOffset = 0;

		switch (m_textVerticalAlignment)
		{
		case basecross::TextBox::TextVerticalAlignment::Up:
			heightOffset = 0;
			break;
		case basecross::TextBox::TextVerticalAlignment::Center:
			heightOffset = rectTransform->GetHeight() * 0.5f - m_textMetrics.height * 0.5f;
			break;
		case basecross::TextBox::TextVerticalAlignment::Down:
			heightOffset = rectTransform->GetHeight() - m_textMetrics.height;
			break;
		}

		TextLayoutUpdate();

		D2DDeviceContext->DrawTextLayout(
			D2D1::Point2F(boxRectangle.left, boxRectangle.top + heightOffset),
			m_textLayout.Get(),
			m_fontBrush.Get()
		);

		D2DDeviceContext->EndDraw();

		D2DDeviceContext->RestoreDrawingState(m_stateBlock.Get());

	}
}