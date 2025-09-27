BUILD_DIR=build
PROJECT_NAME=<project_name>

all: compile run

compile: $(BUILD_DIR)
	cmake -S . -B build
	make -C $(BUILD_DIR)

test: compile
	./$(BUILD_DIR)/$(PROJECT_NAME)_tests

run:
	./$(BUILD_DIR)/$(PROJECT_NAME)

clean: $(BUILD_DIR)
	rm -rf $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
