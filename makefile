# Makefile

# Comandos do compilador
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Diretórios de origem e destino
INCLUDE_DIR = include
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Nome do executável
TARGET = $(BIN_DIR)/KanBan

# Obtenção da lista de arquivos fonte
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Regra de compilação do alvo principal
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $^ -o $@

# Regra de compilação dos arquivos objeto
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Regra para limpar os arquivos objeto e o executável
clean:
	rm -rf $(BUILD_DIR)/*.o $(BIN_DIR)/*.exe

# Regra para reconstruir o projeto
rebuild: clean $(TARGET)

# Regra padrão
.DEFAULT_GOAL := $(TARGET)