/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maida <maida@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:00:29 by maida             #+#    #+#             */
/*   Updated: 2025/04/01 17:00:32 by maida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

/**
 * @brief メイン関数 - コマンドライン引数または標準入力からマップを読み込んで処理する
 *
 * @param argc コマンドライン引数の数
 * @param argv コマンドライン引数の配列
 * @return int プログラムの終了コード
 */
int	main(int argc, char **argv)
{
	t_map_data	*map;
	int			i;

	i = 1;
	// 引数がない場合は標準入力から読み込む
	if (argc < 2)
	{
		map = create_map_from_file("STDIN");
		if (map)
			process_map(map);
		return (0);
	}
	// 引数として渡されたファイルを順番に処理
	while (i < argc)
	{
		map = create_map_from_file(argv[i]);
		if (map)
			process_map(map);
		// 次のマップの前に改行を出力（最後のマップ以外）
		if (++i < argc)
			write(1, "\n", 1);
	}
	return (0);
}
