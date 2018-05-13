#pragma once

//---------------------------------------------------------------------------------------------------
//
// xファイルの管理
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
		// 頂点座標
		std::vector<vertex*> mv_vertexes;
		// 面
		std::vector<index*> mv_indexes;
		// 法線
		std::vector<normal*> mv_normals;
		// テクスチャ座標
		std::vector<texture*> mv_textures;
		// カラー情報
		std::vector<color3c*> mv_texpixcels;

	public:
		// std::stirng型以外が引数だった場合エラーが発生する
		explicit XFile(const std::string _file_name);

		// それぞれのメンバ変数を取得する
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

		// 頂点座標数などの最大値を取得
		static void ReadMaxVertex(FILE *_file_name, unsigned int *_max_vertexes);
		static void ReadMaxIndex(FILE *_file_name, unsigned int *_max_indexis);
		static void ReadMaxNormal(FILE *_file_name, unsigned int *_max_normals);
		static void ReadMaxTexture(FILE *_file_name, unsigned int *_max_textures);

		// 余分なコードの読み込みをスキップする
		static void SkipFileTemplate(FILE *_file_name, char _buf[]);

		// それぞれのstd::vectorにデータを詰め込む
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