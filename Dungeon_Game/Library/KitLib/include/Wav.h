#pragma once

//---------------------------------------------------------------------------------------------------
//
// wav�f�[�^������class
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

		// �w��o�C�g���̃������̓��e��int�^�ɂ���
		static unsigned int GetValue(const char *_ptr, const unsigned int _number);

		// wav�̎w��`�����N��T��
		static bool SearchChunk(std::ifstream &_fstr, const char *_chank);

		// �`�����N�̃T�C�Y���擾
		static unsigned int GetChumkSize(std::ifstream &_fstr);

	public:
		// std::stirng�^�ȊO�������ɂȂ����ꍇ�G���[��\������
		explicit ALWav(const std::string &_file);

		// �`�����l������Ԃ�
		unsigned int Channel() const;

		// �f�[�^���X�e���I�Ȃ�true��Ԃ�
		bool IsStereo() const;

		//�T���v�����O���[�g��Ԃ�
		unsigned int SampleRate() const;

		// �f�[�^�T�C�Y�i�o�C�g���j��Ԃ�
		unsigned int Size() const;

		// �Đ����ԁi�b�j��Ԃ�
		float Time() const;

		// �g�`�f�[�^��Ԃ�
		const char* Data() const;

		//wav�̏����擾
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
