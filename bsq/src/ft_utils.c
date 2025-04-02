/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maida <maida@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:12:22 by maida             #+#    #+#             */
/*   Updated: 2025/04/01 17:19:37 by maida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_utils.c
 * @brief ユーティリティ関数群
 */

#include "bsq.h"

/**
 * @brief マップエラーを報告する
 *
 * @return t_map_data* 常にNULL
 */
t_map_data	*report_map_error(void)
{
	write(STDERR_FILENO, "map error\n", 10);
	return (NULL);
}

/**
 * @brief メモリ領域をコピーする
 *
 * @param dest コピー先
 * @param src コピー元
 * @param num コピーするバイト数
 * @return void* コピー先のポインタ
 */
void	*memory_copy(void *dest, void *src, size_t num)
{
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;

	ptr_dest = (unsigned char *)dest;
	ptr_src = (unsigned char *)src;
	while (num--)
		*ptr_dest++ = *ptr_src++;
	return (dest);
}

/**
 * @brief メモリ領域を再割り当てする
 *
 * @param ptr 現在のメモリポインタ
 * @param old_size 現在のサイズ
 * @param new_size 新しいサイズ
 * @return void* 再割り当てされたメモリのポインタ
 */
void	*memory_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	// 新しいメモリを確保
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	// データをコピー (小さい方のサイズを使用)
	memory_copy(new_ptr, ptr, (old_size < new_size) ? old_size : new_size);
	// 古いメモリを解放
	free(ptr);
	return (new_ptr);
}

/**
 * @brief 文字列を比較する
 *
 * @param s1 1つ目の文字列
 * @param s2 2つ目の文字列
 * @return int 0なら等しい、それ以外は異なる
 */
int	string_compare(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return (s1[i] - s2[i]);
}

/**
 * @brief 文字列を整数に変換する
 *
 * @param str 変換する文字列
 * @return int 変換された整数
 */
int	string_to_int(char *str)
{
	int	number;
	int	sign;

	number = 0;
	sign = 1;
	// 空白をスキップ
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	// 符号を処理
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		else
			sign = 1;
		str++;
	}
	// 数字を処理
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10 + (*str - '0');
		str++;
	}
	return (sign * number);
}
