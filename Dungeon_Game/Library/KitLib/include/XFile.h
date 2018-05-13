#pragma once

//---------------------------------------------------------------------------------------------------
//
// x�t�@�C���̊Ǘ�
//
//---------------------------------------------------------------------------------------------------

#include "Defines.h"

#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <assert.h>

#include "Graphic.h"
#include "Color.h"

namespace kit {
	class XFile {
	private:
		// ���_���W
		std::vector<vertex*> mv_vertexes;
		// ��
		std::vector<index*> mv_indexes;
		// �@��
		std::vector<normal*> mv_normals;
		// �e�N�X�`�����W
		std::vector<texture*> mv_textures;
		// �J���[���
		std::vector<color3c*> mv_texpixcels;

	public:
		// std::stirng�^�ȊO�������������ꍇ�G���[����������
		explicit XFile(const std::string _file_name);

		// ���ꂼ��̃����o�ϐ����擾����
		inline std::vector<vertex*> GetVertexes() {
			return mv_vertexes;
		}
		inline std::vector<index*> GetIndexes() {
			return mv_indexes;
		}
		inline std::vector<normal*> GetNormals() {
			return mv_normals;
		}
		inline std::vector<texture*> GetTextures() {
			return mv_textures;
		}
		inline std::vector<color3c*> GetColors() {
			return mv_texpixcels;
		}

		// ���_���W���Ȃǂ̍ő�l���擾
		static void ReadMaxVertex(FILE *_file_name, unsigned int *_max_vertexes);
		static void ReadMaxIndex(FILE *_file_name, unsigned int *_max_indexis);
		static void ReadMaxNormal(FILE *_file_name, unsigned int *_max_normals);
		static void ReadMaxTexture(FILE *_file_name, unsigned int *_max_textures);

		// �]���ȃR�[�h�̓ǂݍ��݂��X�L�b�v����
		static void SkipFileTemplate(FILE *_file_name, char _buf[]);

		// ���ꂼ���std::vector�Ƀf�[�^���l�ߍ���
		static void PushVector(FILE *_file_name,
			std::vector<vertex*> *_vertexes_vector, const unsigned int &_max_vertexes);
		static void PushVector(FILE *_file_name,
			std::vector<index*> *_indexes_vector, const unsigned int &_max_indexes);
		static void PushVector(FILE *_file_name,
			std::vector<normal*> *_normals_vector, const unsigned int &_max_normals);
		static void PushVector(FILE *_file_name,
			std::vector<texture*> *_textures_vector, const unsigned int &_max_textures);
		static void PushVector(FILE *_file_name,
			std::vector<color3c*> *_colors_vector, const unsigned int &_max_colors);
	};
}