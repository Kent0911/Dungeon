#pragma once

//---------------------------------------------------------------------------------------------------
//
// 色に関する設定
//
//---------------------------------------------------------------------------------------------------

namespace kit {
	enum class Color {
		red,
		green,
		blue,
		alpha,
		Max
	};

	
	// 0～255で設定する、alpha値無のcolor class
	class color3c {
	public:
		unsigned char red, green, blue;

		color3c operator= (const color3c &_color);
		color3c operator+ (const color3c &_color) const;
		color3c operator+= (const color3c &_color);
		color3c operator- (const color3c &_color) const;
		color3c operator-= (const color3c &_color);
	};

	// 0～1.0で設定する、alpha値無のcolor class
	class color3f {
	public:
		float red, green, blue;

		color3f& operator= (const color3f &_color);
		color3f& operator+ (const color3f &_color) const;
		color3f& operator+= (const color3f &_color);
		color3f& operator- (const color3f &_color) const;
		color3f& operator-= (const color3f &_color);
	};

	// 0～255で設定する、alpha値有のcolor class
	class color4c {
	public:
		unsigned char red, green, blue, alpha;

		color4c operator= (const color4c &_color);
		color4c operator+ (const color4c &_color) const;
		color4c operator+= (const color4c &_color);
		color4c operator- (const color4c &_color) const;
		color4c operator-= (const color4c &_color);
		
		/* 色のみの変更を可能にする */
		color4c operator= (const color3c &_color);
		color4c operator+ (const color3c &_color) const;
		color4c operator+= (const color3c &_color);
		color4c operator- (const color3c &_color) const;
		color4c operator-= (const color3c &_color);
	};

	// 0～1.0で設定する、alpha値有のcolor class
	class color4f {
	public:
		float red, green, blue, alpha;

		color4f& operator= (const color4f &_color);
		color4f& operator+ (const color4f &_color) const;
		color4f& operator+= (const color4f &_color);
		color4f& operator- (const color4f &_color) const;
		color4f& operator-= (const color4f &_color);

		/* 色のみの変更を可能にする */
		color4f& operator= (const color3f &_color);
		color4f& operator+ (const color3f &_color) const;
		color4f& operator+= (const color3f &_color);
		color4f& operator- (const color3f &_color) const;
		color4f& operator-= (const color3f &_color);
	};

	// 定型色
	namespace stereotyped_colors {
		static const color3c black;
		static const color3c maroon;
		static const color3c green;
		static const color3c lime;
		static const color3c olive;
		static const color3c yellow;
		static const color3c navy;
		static const color3c blue;
		static const color3c purple;
		static const color3c magenta;
		static const color3c teal;
		static const color3c cyan;
		static const color3c gray;
		static const color3c white;
	}

	// キャスト関数
	const color3c CastColor(const color3f _color);
	const color3f CastColor(const color3c _color);
	const color4c CastColor(const color4f _color);
	const color4f CastColor(const color4c _color);
}