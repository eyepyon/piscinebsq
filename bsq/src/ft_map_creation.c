/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maida <maida@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:01:58 by maida             #+#    #+#             */
/*   Updated: 2025/04/01 17:18:08 by maida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

/**
 * @brief 文字列が数字のみで構成されているか確認する
 *
 * @param str 確認する文字列
 * @return bool 数字のみならtrue、それ以外はfalse
 */
static bool	is_numeric(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (false);
		str++;
	}
	return (true);
}

/**
 * @brief マップのヘッダーを解析する
 *
 * @param map マップデータ構造体
 * @param file_descriptor 読み込むファイルのディスクリプタ
 * @return int エラーなら1、成功なら0
 */
int	parse_map_header(t_map_data *map, int file_descriptor)
{
	char	buffer;
	char	*prows;

	char rows[13]; // 32bit整数の最大桁数+余裕
	prows = rows;
	// 行数と使用する文字を読み込む
	while (1)
	{
		if (read(file_descriptor, &buffer, 1) < 1 || (prows - rows == 13))
			return (1);
		if (buffer == '\n')
			break ;
		*prows++ = buffer;
	}
	// ヘッダーの妥当性チェック
	if (prows - rows < 4) // 最低でも行数+3文字が必要
		return (1);
	// 文字の設定
	map->full = *(prows - 1);
	map->obstacle = *(prows - 2);
	map->empty = *(prows - 3);
	*(prows - 3) = '\0'; // 行数文字列の終端
	// 行数が数値でない、または文字が重複している場合はエラー
	if (!is_numeric(rows) || map->empty == map->obstacle
		|| map->empty == map->full || map->obstacle == map->full)
		return (1);
	// 行数を設定し、0ならエラー
	map->rows = string_to_int(rows);
	return ((map->rows == 0) ? 1 : 0);
}

/**
 * @brief ファイルからマップを作成する
 *
 * @param file_name ファイル名 ("STDIN"なら標準入力から読み込む)
 * @return t_map_data* 作成されたマップデータ、エラー時はNULL
 */
t_map_data	*create_map_from_file(char *file_name)
{
	t_map_data	*map;
	int			file;

	// ファイルを開く (STDINなら標準入力を使用)
	if (!string_compare(file_name, "STDIN"))
		file = STDIN_FILENO;
	else
		file = open(file_name, O_RDONLY);
	// ファイルが開けない場合はエラー
	if (file == -1)
		return (report_map_error());
	// マップデータ構造体のメモリ確保
	map = (t_map_data *)malloc(sizeof(t_map_data));
	if (!map)
		return (report_map_error());
	// ヘッダー情報の解析
	if (parse_map_header(map, file))
	{
		free(map);
		return (report_map_error());
	}
	// マップのグリッドを読み込む
	if (read_map_grid(map, file))
	{
		free_map_data(map);
		return (report_map_error());
	}
	// ファイルを閉じる
	close(file);
	// 最大正方形サイズを初期化
	map->max_square_size = 0;
	return (map);
}
