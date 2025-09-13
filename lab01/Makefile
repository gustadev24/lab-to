BUILD_DIR=build

all: compile run

compile: $(BUILD_DIR)
	cmake -S . -B build
	make -C $(BUILD_DIR)

test: compile
	ctest --test-dir build --output-on-failure

run:
	./$(BUILD_DIR)/lab01

clean: $(BUILD_DIR)
	rm -rf $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
