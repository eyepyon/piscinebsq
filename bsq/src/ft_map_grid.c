/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maida <maida@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:02:56 by maida             #+#    #+#             */
/*   Updated: 2025/04/01 17:13:59 by maida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_map_grid.c
 * @brief マップのグリッドデータを読み込む関数群
 */

#include "bsq.h"

/**
 * @brief マップの行を読み込む
 *
 * @param map マップデータ構造体
 * @param row_index 読み込む行のインデックス
 * @param file_descriptor ファイルディスクリプタ
 * @return int エラーなら1、成功なら0
 */
int	read_map_line(t_map_data *map, int row_index, int file_descriptor)
{
	int		j;
	int		reading;
	char	buffer;

	j = 0;
	while (1)
	{
		reading = read(file_descriptor, &buffer, 1);
		// 行の終端処理
		if (j == map->cols)
		{
			return ((buffer == '\n') ? 0 : 1); // 行末が改行でなければエラー
		}
		// 読み込みエラーまたは不正な文字
		if ((buffer != map->empty && buffer != map->obstacle) || reading < 1)
			return (1);
		// マップデータを格納 (空き=1, 障害物=0)
		map->grid[row_index][j++] = (buffer == map->empty) ? 1 : 0;
	}
	return (1); // ここに到達すべきではない
}

/**
 * @brief マップの最初の行を読み込み、列数を決定する
 *
 * @param map マップデータ構造体
 * @param file_descriptor ファイルディスクリプタ
 * @return int エラーなら1、成功なら0
 */
int	read_first_line(t_map_data *map, int file_descriptor)
{
	char	buffer;
	int		columns;
	int		reading;

	columns = 0;
	int initial_allocation = 128; // 初期メモリ割り当て
	// 最初の行のメモリを確保
	map->grid[0] = (unsigned short *)malloc(initial_allocation
			* sizeof(unsigned short));
	if (!map->grid[0])
		return (1);
	map->cols = initial_allocation;
	// 行を読み込む
	while (1)
	{
		reading = read(file_descriptor, &buffer, 1);
		if (buffer == '\n')
			break ;
		// 読み込みエラーまたは不正な文字
		if ((buffer != map->empty && buffer != map->obstacle) || reading < 1)
			return (1);
		// マップデータを格納
		map->grid[0][columns++] = (buffer == map->empty) ? 1 : 0;
		// 必要に応じてメモリを拡張
		if (columns == map->cols)
		{
			map->grid[0] = (unsigned short *)memory_realloc(map->grid[0],
					map->cols * sizeof(unsigned short), map->cols * 2
					* sizeof(unsigned short));
			map->cols *= 2;
		}
	}
	// 実際の列数に合わせてメモリサイズを調整
	if (columns > 0)
	{
		map->grid[0] = (unsigned short *)memory_realloc(map->grid[0], map->cols
				* sizeof(unsigned short), columns * sizeof(unsigned short));
	}
	map->cols = columns;
	return ((columns == 0) ? 1 : 0); // 列数が0ならエラー
}

/**
 * @brief グリッドの各要素をNULLに初期化
 *
 * @param map マップデータ構造体
 */
static void	initialize_grid_nulls(t_map_data *map)
{
	int	i;

	i = 0;
	while (i < map->rows)
	{
		map->grid[i] = NULL;
		i++;
	}
}

/**
 * @brief マップのグリッド全体を読み込む
 *
 * @param map マップデータ構造体
 * @param file_descriptor ファイルディスクリプタ
 * @return int エラーなら1、成功なら0
 */
int	read_map_grid(t_map_data *map, int file_descriptor)
{
	int		i;
	char	buffer;

	// グリッド用のメモリを確保
	map->grid = (unsigned short **)malloc(map->rows * sizeof(unsigned short *));
	if (!map->grid)
		return (1);
	initialize_grid_nulls(map);
	// 最初の行を読み込み、列数を決定
	if (read_first_line(map, file_descriptor))
		return (1);
	// 残りの行を読み込む
	i = 1;
	while (i < map->rows)
	{
		map->grid[i] = (unsigned short *)malloc(map->cols
				* sizeof(unsigned short));
		if (!map->grid[i])
			return (1);
		if (read_map_line(map, i, file_descriptor))
			return (1);
		i++;
	}
	// ファイルに余分なデータがないことを確認
	if (read(file_descriptor, &buffer, 1) > 0)
		return (1);
	return (0);
}
