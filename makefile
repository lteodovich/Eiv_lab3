SRC_DIR = ./src
INC_DIR = ./inc
BUILD_DIR = ./build

# rutas específicas de obj intermedios y binario
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Regla principal: ahora depende del binario en la carpeta bin
all: $(BIN_DIR)/a.out

$(BIN_DIR)/a.out: $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	gcc -o $@ $(OBJ_FILES)

# Manejo de dependencias (.d)
DEPS := $(OBJ_FILES:.o=.d)
-include $(DEPS)

# Regla de compilación de objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	gcc -c $< -o $@ -I $(INC_DIR) -MMD

doc:	
	doxygen Doxyfile
