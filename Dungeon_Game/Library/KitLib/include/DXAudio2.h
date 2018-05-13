#pragma once
#pragma comment (lib,"xmcore.lib")
#pragma comment (lib,"XAudio2.lib")
//-----------------------------------------------------------------------------------------------------
//
// XAudio2管理
//
//-----------------------------------------------------------------------------------------------------
#include "Defines.h"

#include <Windows.h>
#include <xaudio2.h>
#include <strsafe.h>
#include <shellapi.h>
#include <mmsystem.h>
#include <conio.h>
#include <memory>

#include "Singleton.h"
#include "Wav.h"


namespace kit {
	namespace Engine {
		//---------------------------------------------------------------------------------------------
		//
		// XAudio2の初期化、及び破棄の管理
		//
		//---------------------------------------------------------------------------------------------
		class DXAudio :public Singleton<DXAudio> {
		private:
			// XAudio2の初期化
			IXAudio2 *mp_xaudio;
			IXAudio2MasteringVoice *mp_mastar_voice;

			// 利用可能なオーディオデバイスの列挙
			UINT32 mui_device_count;
			int mi_preferred_device;

		public:
			DXAudio(HRESULT *_hr);
			~DXAudio();

			inline IXAudio2* GetIXAudio() const {
				return mp_xaudio;
			}

			HRESULT CreateDXAudio2(HRESULT *_hr);
		};

		class DXMediaInfo {
		public:
			WCHAR mwc_str_file_path;
			UINT mui_source_time;
			XAUDIO2_VOICE_STATE mx_state;
		};
	
		class DXMedia {
		private:
			DXMediaInfo mm_info;
			XAUDIO2_BUFFER m_buffer;
			IXAudio2SourceVoice *mp_source_voice;

		public:
			DXMedia();
			explicit DXMedia(HRESULT *_hr, IXAudio2 *_pXAuido2, LPCWSTR _str_file_path);
			~DXMedia();

			HRESULT FindMediaFileCch(int _cch_dest,LPCWSTR _str_file_path);

			HRESULT AudioPlay(HRESULT *_hr) const;

			HRESULT AudioPlay(HRESULT *_hr, const UINT _source_start_time);

			HRESULT AudioStop(HRESULT *_hr) const;

			HRESULT AudioPause(HRESULT *_hr) const;

			BOOL AudioIsRunning();
		};

	}
}
