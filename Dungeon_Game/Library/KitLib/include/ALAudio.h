#pragma once

//---------------------------------------------------------------------------------------------------
//
// OpenAL�Ǘ�
//
//---------------------------------------------------------------------------------------------------

#include "Defines.h"

#include <string>
#include <memory>
#include <vector>
#include <iostream>

#include "../openAL/al.h"
#include "../openAL/alc.h"
#include "Vec3.h"
#include "Wav.h"

namespace kit {
	namespace Engine {
		//---------------------------------------------------------------------------------------------
		//
		// OpenAL�̏������A�y�єj���̊Ǘ�
		//
		//---------------------------------------------------------------------------------------------
		class ALAudio {
		private:
			ALCdevice *m_device;
			ALCcontext *m_context;

		public:
			ALAudio();
			~ALAudio();

			// ����class�̓R�s�[�֎~�ɂ���
			ALAudio(const ALAudio&) = delete;
			ALAudio& operator= (const ALAudio&) = delete;

			// listener�̈ʒu��ύX
			// float�^
			static void ListenerPosition(const float _x, const float _y, const float _z);
			// glm::vec3�^
			static void ListenerPosition(const vec3 &_pos);

			// listener�̌�����ύX
			// float�^
			// _at_x,_at_y,_at_z �������Ă��������\���x�N�g��
			// _up_x,_up_y,_up_z ���������\���x�N�g��
			static void ListenerOrientation(const float _at_x, const float _at_y, const float _at_z,
				const float _up_x, const float _up_y, const float _up_z);
			// glm::vec3�^
			static void ListenerOrientation(const vec3 &_at, const vec3 &_up);


			// listener�̈ړ����x��ύX
			// float�^
			static void ListenerVelocity(const float _x, const float _y, const float _z);
			// glm::vec3�^
			static void ListenerVelocity(const vec3 &_vec);
		};


		//---------------------------------------------------------------------------------------------
		//
		// �o�b�t�@�̊Ǘ�
		//
		//---------------------------------------------------------------------------------------------
		class ALBuffer {
		private:
			ALuint m_id;

		public:
			ALBuffer();
			// std::string�^�ȊO�������ɂȂ����Ƃ��̓G���[����������
			explicit ALBuffer(const std::string &_path);
			~ALBuffer();

			// ����class�̓R�s�[�֎~�ɂ���
			ALBuffer(const ALBuffer&) = delete;
			ALBuffer& operator= (const ALBuffer&) = delete;

			// �o�b�t�@�̎��ʎq
			ALuint Id() const;

			// �g�`�f�[�^�����蓖�Ă�
			// TIPS:���蓖�Ă���A�f�[�^�̓��e�͔j���ł���
			void Bind(const bool _stereo, const void *_data,
				const unsigned int _size, const unsigned int _rate) const;
		};


		//---------------------------------------------------------------------------------------------
		//
		// �\�[�X�̊Ǘ�
		//
		//---------------------------------------------------------------------------------------------
		class ALSource {
		private:
			ALuint m_id;

		public:
			ALSource();
			~ALSource();

			// ����class�̓R�s�[���֎~�ɂ���
			ALSource(const ALSource&) = delete;
			ALSource& operator= (const ALSource&) = delete;


			ALuint Name() const;

			// �\�[�X�Ƀo�b�t�@�����蓖�Ă�
			void BindBuffer(const ALBuffer &_buffer) const;

			// �\�[�X�Ɋ��蓖�Ă��o�b�t�@������
			void UnbindBuffer() const;

			// �Đ��J�n
			void AudioPlay() const;

			// �Đ���~
			void AudioStop() const;

			// �Đ��ꎞ��~�c���̌�A�Đ�����Ƒ�������Đ������
			void AudioPause() const;

			// ���ʕύX�ivalue:0.0f�`�j
			void AudioGain(const float _gain) const;

			// �Đ��s�b�`�ύX�ivalue:0.0f�`�j
			void AudioPitch(const float _pitch) const;

			// ���[�v��ON/OFF
			// value: true = ���[�v��ON , false = ���[�v��OFF
			void AudioLoop(const bool _flag) const;

			// �\�[�X�̈ʒu��ύX����
			// float�^
			void SourcePosition(const float _x, const float _y, const float _z) const;
			// glm::vec3�^
			void SourcePosition(const vec3 &_pos) const;

			// �\�[�X�̈ړ����x��ύX����
			// float�^
			void SourceVelocity(const float _x, const float _y, const float _z) const;
			// glm::vec3�^
			void SourceVelocity(const vec3 &_vec) const;

			// �Đ����̔���
			bool AudioIsPlaying() const;

			// �Đ��ʒu�i�b�j
			float CurrentTime() const;

			// Buffer�̍Đ��L���[�C���O
			void QueueBuffer(const ALBuffer &_buffer)const;

			// �Đ�����Buffer��id�擾
			ALuint UnqueueBuffer() const;

			// �L���[�C���O���ꂽBuffer�̍Đ����������擾
			int Processed() const;
		};

		//---------------------------------------------------------------------------------------------
		//
		// Media class�̐ݒ�
		// TIPS:���̃N���X��p���ĉ����̎������s��
		//
		//---------------------------------------------------------------------------------------------
		class ALMedia {
		private:
			std::shared_ptr<ALBuffer> m_sharedptr_buffer;
			std::shared_ptr<ALSource> m_sharedptr_source;

		public:
			ALMedia();
			// ������std::stirng�^�łȂ���΃G���[��\������
			ALMedia(const std::string &_path);

			~ALMedia();

			// �Đ��J�n
			void AudioPlay() const;

			// �Đ���~
			void AudioStop() const;

			// �ꎞ��~
			void AudioPause() const;

			// ���ʕύX�ivalue 0.0f�`�j
			void AudioGain(const float _gain) const;

			// �Đ��s�b�`�ύX�ivalue 0.0f�`�j
			void AudioPitch(const float _pitch) const;

			// ���[�v��ON/OFF
			// value: true = ���[�vON / false = ���[�vOFF
			void AudioLoop(const bool _flag) const;

			// �\�[�X�̈ʒu�̕ύX
			// float�^
			void AudioPosition(const float _x, const float _y, const float _z) const;

			// glm::vec3�^
			void AudioPosition(const vec3 _pos) const;

			// �\�[�X�̈ړ����x�̕ύX
			// float�^
			void AudioVelocity(const float _x, const float _y, const float _z) const;

			// glm::vec3�^
			void AudioVelocity(const vec3 _vec) const;

			// �Đ����̔���
			bool AudioIsPlaying() const;

			// �Đ��ʒu�i�b�j
			float CurrentTime() const;
		};

	}
}