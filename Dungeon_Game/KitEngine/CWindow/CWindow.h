#pragma once

#include <d3d11.h>

#include "../../Library/KitLib/include/Kitlib.h"
#include "../../Library/DirectXTK/include/Keyboard.h"
#include "../../Library/DirectXTK/include/Mouse.h"

#define IDI_SAMPLE1 107

namespace kit {
	namespace Engine {

		// CALLBACK関数定義
		typedef LRESULT(CALLBACK *LPONMESSAGE)(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

		// Window管理クラス
		class CWindow {
		private:
			WNDCLASSEX	m_wcex;

			// RECT = { left,top,right,bottom }
			RECT		mrec_window_size;

			static LRESULT CALLBACK WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

			HRESULT InitWindow(HINSTANCE _hInstance, int _nCmdShow);
			

		public:
			CWindow(HINSTANCE _hInstance, int _nCmdShow);
			CWindow(HINSTANCE _hInstance, int _nCmdShow, RECT _createWindowSize);
			CWindow(HINSTANCE _hInstance, int _nCmdShow, kit::vec2 _createWindowSize);
			~CWindow();

			inline WNDCLASSEX GetWcex() {
				return m_wcex;
			}
			inline RECT GetRect() {
				return mrec_window_size;
			}
		};

	}// namespace Engine end
}// namespace Kit end