# === CONFIGURAÇÕES GERAIS ===
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LIBS = -lncurses
BUILD_DIR = build
SRC_DIR = src
EXEC = $(BUILD_DIR)/scp

# === LISTA DE ARQUIVOS ===
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

# ===========================
# REGRAS PRINCIPAIS
# ===========================

all: dirs $(EXEC)
	@echo "Compilação concluída com sucesso!"

dirs:
	@mkdir -p $(BUILD_DIR)

$(EXEC): $(OBJ_FILES)
	@echo "Ligando o executável..."
	$(CC) $(OBJ_FILES) -o $(EXEC) $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compilando $<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR)
	@echo "Limpeza concluída."

run: all
	@echo "Executando o Sistema de Controle de Pedidos..."
	@$(EXEC)

help:
	@echo "Comandos disponíveis:"
	@echo "  make        → compila o projeto"
	@echo "  make run    → compila e executa"
	@echo "  make clean  → remove arquivos compilados"
	@echo "  make help   → mostra esta ajuda"

.PHONY: all clean run help dirs