/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maida <maida@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:00:42 by maida             #+#    #+#             */
/*   Updated: 2025/04/01 17:00:45 by maida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include <fcntl.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

/**
 * @struct MapData
 * @brief マップのデータと最大正方形の情報を格納する構造体
 */
typedef struct s_map_data
{
	int rows;                       /* マップの行数 */
	int cols;                       /* マップの列数 */
	char empty;                     /* 空白を表す文字 */
	char obstacle;                  /* 障害物を表す文字 */
	char full;                      /* 正方形を表す文字 */
	unsigned short **grid;          /* マップのグリッド (1=空、0=障害物) */
	unsigned short max_square_size; /* 最大正方形のサイズ */
	int max_square_row;             /* 最大正方形の左上の行位置 */
	int max_square_col;             /* 最大正方形の左上の列位置 */
}			t_map_data;

/* メモリ操作関数 */
void		*memory_copy(void *dest, void *src, size_t num);
void		*memory_realloc(void *ptr, size_t old_size, size_t new_size);

/* 文字列操作関数 */
int			string_compare(char *s1, char *s2);
int			string_to_int(char *str);

/* エラー処理とメモリ解放 */
t_map_data	*report_map_error(void);
void		free_map_data(t_map_data *map);

/* 正方形検索アルゴリズム */
void		find_largest_square(t_map_data *map);
void		process_map(t_map_data *map);

/* マップ読み込み関数 */
int			read_map_line(t_map_data *map, int row_index, int file_descriptor);
int			read_first_line(t_map_data *map, int file_descriptor);
int			read_map_grid(t_map_data *map, int file_descriptor);
int			parse_map_header(t_map_data *map, int file_descriptor);
t_map_data	*create_map_from_file(char *file_name);

#endif /* BSQ_H */
