#pragma once

//---------------------------------------------------------------------------------------------------
//
// wavデータを扱うclass
//
//---------------------------------------------------------------------------------------------------

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <d3d11.h>
#include <xaudio2.h>
#include <strsafe.h>
#include <shellapi.h>
#include <mmsyscom.h>
#include <mmiscapi.h>
#include <conio.h>

#include "Defines.h"
#include "../DirectXAudio/DxErr.h"


#define WAVEFILE_READ	1
#define WAVEFILE_WRITE	2


namespace kit {
	
	struct ALInfo {
		unsigned int id;
		unsigned int ch;
		unsigned int sample_rate;
		unsigned int bit;
		unsigned int size;
	};


	class ALWav {
	private:
		ALInfo m_info;
		float mf_time;
		std::vector<char> mvec_data;

		// 指定バイト数のメモリの内容をint型にする
		static unsigned int GetValue(const char *_ptr, const unsigned int _number);

		// wavの指定チャンクを探す
		static bool SearchChunk(std::ifstream &_fstr, const char *_chank);

		// チャンクのサイズを取得
		static unsigned int GetChumkSize(std::ifstream &_fstr);

	public:
		// std::stirng型以外が引数になった場合エラーを表示する
		explicit ALWav(const std::string &_file);

		// チャンネル数を返す
		unsigned int Channel() const;

		// データがステレオならtrueを返す
		bool IsStereo() const;

		//サンプリングレートを返す
		unsigned int SampleRate() const;

		// データサイズ（バイト数）を返す
		unsigned int Size() const;

		// 再生時間（秒）を返す
		float Time() const;

		// 波形データを返す
		const char* Data() const;

		//wavの情報を取得
		static bool AnalyzeWavFile(ALInfo& _info, std::ifstream& _fstr);

	};



	struct DXInfo {
		WAVEFORMATEX *pwfx;
		HMMIO hmmio;
		MMCKINFO ck;
		MMCKINFO ck_riff;
		DWORD dw_size;
		MMIOINFO mmio_info_out;
		DWORD dw_flags;
		BOOL b_is_reading_from_memory;
	};


	class DXWav {
	private:
		DXInfo m_info;
		BYTE *mpb_data;
		BYTE *mpb_data_cur;
		ULONG mul_data_size;
		CHAR *mpc_resource_buffer;

	protected:
		HRESULT ReadMMIO();
		HRESULT WriteMMIO(WAVEFORMATEX *_pwfx_dest);

	public:
		DXWav();
		~DXWav();

		HRESULT Open(LPWSTR _str_path, WAVEFORMATEX *_pwfx, DWORD _dw_flags);
		HRESULT OpenFromMemory(BYTE *_pb_data, ULONG _ul_datasize, WAVEFORMATEX *_pwfx, DWORD _dw_flags);
		HRESULT Close();

		HRESULT Read(BYTE *_p_buffer, DWORD _dw_sizetoread, DWORD *_pdw_sizeread);
		HRESULT Write(UINT _ni_sizetowirte, BYTE *_pb_data, UINT *_pui_sizewrote);

		inline DWORD GetSize() const {
			return m_info.dw_size;
		}
		HRESULT ResetFile();
		inline WAVEFORMATEX* GetFormat() const {
			return m_info.pwfx;
		}
	};
}
