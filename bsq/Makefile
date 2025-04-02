# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maida <maida@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/01 17:09:44 by maida             #+#    #+#              #
#    Updated: 2025/04/01 17:10:20 by maida            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# プログラム名
NAME = bsq

# ソースファイル
SRC_DIR = src
SRC_FILES = main.c ft_map_creation.c ft_map_grid.c ft_map_processing.c ft_utils.c
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# オブジェクトファイル
OBJ_DIR = obj
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ヘッダーファイル
INCLUDE_DIR = include

# コンパイラとフラグ
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I$(INCLUDE_DIR)

# その他のコマンド
RM = rm -rf
MKDIR = mkdir -p

# ルール
.PHONY: all clean fclean re

# デフォルトターゲット
all: $(NAME)

# オブジェクトファイルディレクトリの作成
$(OBJ_DIR):
	$(MKDIR) $(OBJ_DIR)

# オブジェクトファイルの生成
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 実行ファイルの生成
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Compilation complete: $(NAME)"

# オブジェクトファイルの削除
clean:
	$(RM) $(OBJ_DIR)
	@echo "Object files removed"

# すべての生成ファイルの削除
fclean: clean
	$(RM) $(NAME)
	@echo "Executable removed"

# 完全に再ビルド
re: fclean all
