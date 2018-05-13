#pragma once

//---------------------------------------------------------------------------------------------------
//
// OpenAL管理
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
		// OpenALの初期化、及び破棄の管理
		//
		//---------------------------------------------------------------------------------------------
		class ALAudio {
		private:
			ALCdevice *m_device;
			ALCcontext *m_context;

		public:
			ALAudio();
			~ALAudio();

			// このclassはコピー禁止にする
			ALAudio(const ALAudio&) = delete;
			ALAudio& operator= (const ALAudio&) = delete;

			// listenerの位置を変更
			// float型
			static void ListenerPosition(const float _x, const float _y, const float _z);
			// glm::vec3型
			static void ListenerPosition(const vec3 &_pos);

			// listenerの向きを変更
			// float型
			// _at_x,_at_y,_at_z →向いている方向を表すベクトル
			// _up_x,_up_y,_up_z →上方向を表すベクトル
			static void ListenerOrientation(const float _at_x, const float _at_y, const float _at_z,
				const float _up_x, const float _up_y, const float _up_z);
			// glm::vec3型
			static void ListenerOrientation(const vec3 &_at, const vec3 &_up);


			// listenerの移動速度を変更
			// float型
			static void ListenerVelocity(const float _x, const float _y, const float _z);
			// glm::vec3型
			static void ListenerVelocity(const vec3 &_vec);
		};


		//---------------------------------------------------------------------------------------------
		//
		// バッファの管理
		//
		//---------------------------------------------------------------------------------------------
		class ALBuffer {
		private:
			ALuint m_id;

		public:
			ALBuffer();
			// std::string型以外が引数になったときはエラーが発生する
			explicit ALBuffer(const std::string &_path);
			~ALBuffer();

			// このclassはコピー禁止にする
			ALBuffer(const ALBuffer&) = delete;
			ALBuffer& operator= (const ALBuffer&) = delete;

			// バッファの識別子
			ALuint Id() const;

			// 波形データを割り当てる
			// TIPS:割り当てた後、データの内容は破棄できる
			void Bind(const bool _stereo, const void *_data,
				const unsigned int _size, const unsigned int _rate) const;
		};


		//---------------------------------------------------------------------------------------------
		//
		// ソースの管理
		//
		//---------------------------------------------------------------------------------------------
		class ALSource {
		private:
			ALuint m_id;

		public:
			ALSource();
			~ALSource();

			// このclassはコピーを禁止にする
			ALSource(const ALSource&) = delete;
			ALSource& operator= (const ALSource&) = delete;


			ALuint Name() const;

			// ソースにバッファを割り当てる
			void BindBuffer(const ALBuffer &_buffer) const;

			// ソースに割り当てたバッファを解除
			void UnbindBuffer() const;

			// 再生開始
			void AudioPlay() const;

			// 再生停止
			void AudioStop() const;

			// 再生一時停止…この後、再生すると続きから再生される
			void AudioPause() const;

			// 音量変更（value:0.0f～）
			void AudioGain(const float _gain) const;

			// 再生ピッチ変更（value:0.0f～）
			void AudioPitch(const float _pitch) const;

			// ループのON/OFF
			// value: true = ループのON , false = ループのOFF
			void AudioLoop(const bool _flag) const;

			// ソースの位置を変更する
			// float型
			void SourcePosition(const float _x, const float _y, const float _z) const;
			// glm::vec3型
			void SourcePosition(const vec3 &_pos) const;

			// ソースの移動速度を変更する
			// float型
			void SourceVelocity(const float _x, const float _y, const float _z) const;
			// glm::vec3型
			void SourceVelocity(const vec3 &_vec) const;

			// 再生中の判定
			bool AudioIsPlaying() const;

			// 再生位置（秒）
			float CurrentTime() const;

			// Bufferの再生キューイング
			void QueueBuffer(const ALBuffer &_buffer)const;

			// 再生完了Bufferのid取得
			ALuint UnqueueBuffer() const;

			// キューイングされたBufferの再生完了数を取得
			int Processed() const;
		};

		//---------------------------------------------------------------------------------------------
		//
		// Media classの設定
		// TIPS:このクラスを用いて音声の実装を行う
		//
		//---------------------------------------------------------------------------------------------
		class ALMedia {
		private:
			std::shared_ptr<ALBuffer> m_sharedptr_buffer;
			std::shared_ptr<ALSource> m_sharedptr_source;

		public:
			ALMedia();
			// 引数がstd::stirng型でなければエラーを表示する
			ALMedia(const std::string &_path);

			~ALMedia();

			// 再生開始
			void AudioPlay() const;

			// 再生停止
			void AudioStop() const;

			// 一時停止
			void AudioPause() const;

			// 音量変更（value 0.0f～）
			void AudioGain(const float _gain) const;

			// 再生ピッチ変更（value 0.0f～）
			void AudioPitch(const float _pitch) const;

			// ループのON/OFF
			// value: true = ループON / false = ループOFF
			void AudioLoop(const bool _flag) const;

			// ソースの位置の変更
			// float型
			void AudioPosition(const float _x, const float _y, const float _z) const;

			// glm::vec3型
			void AudioPosition(const vec3 _pos) const;

			// ソースの移動速度の変更
			// float型
			void AudioVelocity(const float _x, const float _y, const float _z) const;

			// glm::vec3型
			void AudioVelocity(const vec3 _vec) const;

			// 再生中の判定
			bool AudioIsPlaying() const;

			// 再生位置（秒）
			float CurrentTime() const;
		};

	}
}