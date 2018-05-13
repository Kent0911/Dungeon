#pragma once

//---------------------------------------------------------------------------------------------------
//
// Xinput��p����GamePad�̐ݒ�
//
//---------------------------------------------------------------------------------------------------
#include "Defines.h"

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <Windows.h>
#include <Xinput.h>
#include <iostream>


#define MAX_GAMEPAD (4) // Xinput���F���ł���ő吔


namespace kit {
//---------------------------------------------------------------------------------------------------
// PS4�̃R���g���[���[�̃L�[�z�u
//---------------------------------------------------------------------------------------------------
	enum class GamePad_Buttons :unsigned int {
		Up	   = (1 << 0),
		Down   = (1 << 1),
		Left   = (1 << 2),
		Right  = (1 << 3),
		Start  = (1 << 4),
		Select = (1 << 5),
		L3	   = (1 << 6),
		R3	   = (1 << 7),
		L1	   = (1 << 8),
		R1	   = (1 << 9),
		B	   = (1 << 12),//�~
		A	   = (1 << 13),//��
		C	   = (1 << 14),//��
		D	   = (1 << 15) //��
	};

//---------------------------------------------------------------------------------------------------
// TIPS:dw_result��GamePad�������ɐڑ���Ԃł����ERROR_SUCCESS���Ԃ����
//		dw_number�͐ڑ���Ԃł���GamePad�̔ԍ����T����
//		assigned�͐ڑ���Ԃ�GamePad��dw_number�𑼃N���X�Ɋ���U�������ۂ��̃t���O
//---------------------------------------------------------------------------------------------------
	class DwordResult {
	private:
		bool mb_is_assigned;
		DWORD dw_result;
		DWORD dw_number;

	public:
		DwordResult();
		inline bool GetIsAssigned() const {
			return mb_is_assigned;
		}
		inline void SetIsAssigned(const bool _flag) {
			mb_is_assigned = _flag;
		}
		inline void SetResult(const DWORD _dw) {
			dw_result = _dw;
		}
		inline void SetNumber(const DWORD _number) {
			dw_number = _number;
		}
		inline DWORD GetNumber() const {
			return dw_number;
		}
		inline DWORD GetResult() const {
			return dw_result;
		}
	};

//---------------------------------------------------------------------------------------------------
// �S�Ă�GamePad���Ǘ�����
//---------------------------------------------------------------------------------------------------
	class GamePad {
	private:
		DwordResult m_results[MAX_GAMEPAD];
		XINPUT_STATE m_state;

	public:
		GamePad();
		DWORD AssignNumber();
		inline XINPUT_GAMEPAD GetState(const DWORD _dw) {
			ZeroMemory(&m_state, sizeof(XINPUT_STATE));
			XInputGetState(_dw, &m_state);
			return m_state.Gamepad;
		}
	};
}
