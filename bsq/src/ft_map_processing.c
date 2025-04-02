/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_processing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maida <maida@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:04:10 by maida             #+#    #+#             */
/*   Updated: 2025/04/01 17:34:38 by maida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_map_processing.c
 * @brief マップから最大正方形を探索・表示する関数群
 */

#include "bsq.h"

/**
 * @brief マップデータを解放する
 *
 * @param map 解放するマップデータ構造体
 */
void	free_map_data(t_map_data *map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	// グリッドが存在する場合、行ごとに解放
	if (map->grid)
	{
		while (i < map->rows && map->grid[i])
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	// マップ構造体自体を解放
	free(map);
}

/**
 * @brief 3つの値の最小値を返す
 *
 * @param a 1つ目の値
 * @param b 2つ目の値
 * @param c 3つ目の値
 * @return int 最小値
 */
static int	min_of_three(int a, int b, int c)
{
	if (a <= b && a <= c)
		return (a);
	else if (b <= a && b <= c)
		return (b);
	else
		return (c);
}

/**
 * @brief 動的計画法を使って最大正方形を見つける
 *
 * @param map マップデータ構造体
 */
void	find_largest_square(t_map_data *map)
{
	int row, col;
	// 右下から左上へと探索
	row = map->rows - 1;
	while (row >= 0)
	{
		col = map->cols - 1;
		while (col >= 0)
		{
			// 空きスペースの場合のみ処理
			if (map->grid[row][col])
			{
				// 端の場合はそのまま (1x1の正方形)
				if (row < map->rows - 1 && col < map->cols - 1)
				{
					// 右、下、右下の3マスの最小値に1を加えた値が、
					// そのマスを左上とする最大正方形のサイズ
					map->grid[row][col] = min_of_three(map->grid[row + 1][col],
							map->grid[row][col + 1], map->grid[row + 1][col
							+ 1]) + 1;
				}
				// より大きな正方形が見つかった場合は更新
				if (map->grid[row][col] > map->max_square_size)
				{
					map->max_square_size = map->grid[row][col];
					map->max_square_row = row;
					map->max_square_col = col;
				}
				// 同じサイズの場合は、より上か左にある解を優先
				else if (map->grid[row][col] == map->max_square_size)
				{
					if (row < map->max_square_row || (row == map->max_square_row
							&& col < map->max_square_col))
					{
						map->max_square_row = row;
						map->max_square_col = col;
					}
				}
			}
			col--;
		}
		row--;
	}
}

/**
 * @brief マップと最大正方形を出力する
 *
 * @param map マップデータ構造体
 * @param start_row 正方形の開始行
 * @param start_col 正方形の開始列
 */
static void	print_solution(t_map_data *map, int start_row, int start_col)
{
	int	end_row;
	int	end_col;

	end_row = start_row + map->max_square_size - 1;
	end_col = start_col + map->max_square_size - 1;
	int i, j;
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (!map->grid[i][j])
			{
				// 障害物
				write(1, &(map->obstacle), 1);
			}
			else if (i >= start_row && i <= end_row && j >= start_col
				&& j <= end_col)
			{
				// 最大正方形の内部
				write(1, &(map->full), 1);
			}
			else
			{
				// 空きスペース
				write(1, &(map->empty), 1);
			}
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

/**
 * @brief マップを処理し、最大正方形を見つけて出力する
 *
 * @param map マップデータ構造体
 */
void	process_map(t_map_data *map)
{
	// 最大正方形を探索
	find_largest_square(map);
	// 結果を出力
	print_solution(map, map->max_square_row, map->max_square_col);
	// メモリ解放
	free_map_data(map);
}
