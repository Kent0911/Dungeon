#pragma once

#include <d3d11.h>
#include <memory>
#include <list>

#include "CWindow\CWindow.h"
#include "AssetsManager\AssetsManager.h"
#include "SceneManager\Scene\Scene.h"
#include "SceneManager\SceneManager.h"
#include "Render\Render.h"
#include "Render\Fonts\Fonts.h"
#include "../Library/DirectXTK/include/SpriteBatch.h"

#pragma comment(lib,"d3d11.lib")

// externの警告の非表示
#pragma warning (disable:4091)


namespace kit {
	namespace Engine {

#define DEFAULT_NUMRATOR (UINT)60
#define DEFALUT_DENOMINATOR (UINT)1
		

		//------------------------------------------------------------------------------------------------------------
		//
		// DirectX11で使用するグローバル変数
		//
		//------------------------------------------------------------------------------------------------------------
		extern HINSTANCE                           g_hInst;
		extern HWND                                g_hWnd;
		extern D3D_DRIVER_TYPE                     g_driverType;
		extern D3D_FEATURE_LEVEL                   g_featureLevel;
		extern ID3D11Device*                       g_pd3dDevice;
		extern ID3D11DeviceContext*                g_pImmediateContext;
		extern IDXGISwapChain*					   g_pSwapChain;
		extern ID3D11RenderTargetView*             g_pRenderTargetView;
		extern ID3D11Texture2D*                    g_pDepthStencil;
		extern ID3D11DepthStencilView*             g_pDepthStencilView;
		
		//------------------------------------------------------------------------------------------------------------
		//
		// KitEngineで使用するグローバル変数
		//
		//------------------------------------------------------------------------------------------------------------
		extern AssetsManager							g_assetsManager;


		class FrameRate {
		private:
			UINT numerator, denominator;
		public:
			FrameRate();
			~FrameRate();
			FrameRate operator=(const FrameRate _frameRate);

			inline void Numerator(const UINT _num) {
				numerator = _num;
			}
			inline UINT Numerator() const {
				return numerator;
			}
			inline UINT Denominator() const {
				return denominator;
			}
		};

		extern class Scene;
		extern class SceneManager;

		class Config {
		public:
			LPSTR						mlp_str;
			FrameRate					mc_frameRate;
			kit::vec2					mv_windowSize;
			std::shared_ptr<Scene>		msptr_startScene;
		};

		class KitEngine {
		private:
			Config							mc_config;
			std::unique_ptr<CWindow>		muptr_window;
			std::unique_ptr<SceneManager>	muptr_sceneManager;

			HRESULT InitDevice();
			HRESULT HCreateWindow(HINSTANCE _hInstance, int _nCmdShow);

		public:
			KitEngine(HINSTANCE _hInstance, int _nCmdShow, Config* _config);
			~KitEngine();

			void ChangeScene(std::shared_ptr<Scene> _changeScene);

			void Update();
			void Render();
		};
	}
}