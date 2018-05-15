#pragma once

#include <d3d11.h>
#include <string>
#include <locale>
#include <codecvt>
#include <vector>

#include "../../../Library/KitLib/include/Kitlib.h"
#include "../../../Library/DirectXTK/include/SimpleMath.h"
#include "../../../Library/DirectXTK/include/GeometricPrimitive.h"
#include "../Render.h"

namespace kit {
	namespace Engine {
		// フォント表示に使用するクラス
		class Font {
		private:
			std::string			m_str;
			kit::vec2			mvec_displayPosition;
			float				mf_scale;
			DirectX::XMVECTOR	mv_color;

			DirectX::XMFLOAT2 GetDisplayPos();

		public:
			Font(std::string _str, kit::vec2 _pos);
			Font(std::string _str, kit::vec2 _pos, float _scale);
			Font(std::string _str, kit::vec2 _pos, float _scale, DirectX::XMVECTOR _color);
			Font(Font* _config);
			~Font();

			void DisplayFont();
			void DisplayFont(DirectX::XMVECTOR _color);
		};

		// シーン別フォントリスト作成用構造体
		typedef struct {
			Font f_fonts;
		}SCENEFONTS, *LPSCENEFONTS;

		class SceneFonts :public Singleton<SceneFonts> {
		private:
			friend class Singleton<SceneFonts>;
			SceneFonts();

			std::vector<Font*> mvec_sceneFonts;
			
		public:
			void AddFontList(SCENEFONTS _font[], int _max);
			void ClearFontList();
			void DisplayFont();
		};
	}
}