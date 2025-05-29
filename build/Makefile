# root/build/Makefile

EXPORT_DIR := Cognivial
EXPORT_INCLUDE := $(EXPORT_DIR)/Include
EXPORT_LIB := $(EXPORT_DIR)/Lib/Mac
PUBLIC_HEADERS := $(shell find $(SRC_DIR) -type f \( -name "*.hpp" -o -name "*.h" -o -name "*.tpp" \))

INCLUDE_DIR := ../include
PUBLIC_HEADERS := $(shell find $(SRC_DIR) -type f \( -name "*.hpp" -o -name "*.h" -o -name "*.tpp" \))

CXX       := /opt/homebrew/opt/llvm/bin/clang++
SDK_PATH  := $(shell xcrun --show-sdk-path)
CXXFLAGS  := -std=c++20 -fsanitize=address -g \
              -isysroot $(SDK_PATH) -stdlib=libc++ \
              -MMD -MP

SRC_DIR   := ../src
OBJ_DIR   := objects

# 1) grab every instantiations.cpp under src
INST_CPP  := $(shell find $(SRC_DIR) -type f -name instantiations.cpp)

# 2) map ../src/foo/bar/instantiations.cpp → objects/foo/bar/instantiations.o
OBJS      := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(INST_CPP))
DEPS      := $(OBJS:.o=.d)

# 3) name of the static library
LIB       := libcognivial.a

.PHONY: all clean
all: $(LIB)

# Archive all .o into the .a
$(LIB): $(OBJS)
	@echo "[AR] $@"
	ar rcs $@ $^

# Compile rule for nested instantiations.cpp
$(OBJ_DIR)/%/instantiations.o: $(SRC_DIR)/%/instantiations.cpp
	@echo "[CC] $< -> $@"
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile rule for top-level instantiations.cpp
$(OBJ_DIR)/instantiations.o: $(SRC_DIR)/instantiations.cpp
	@echo "[CC] $< -> $@"
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(DEPS) $(LIB)

.PHONY: all clean install

all: $(LIB)

install: all
	@echo "[INSTALL] Headers → $(EXPORT_INCLUDE)"
	@mkdir -p $(EXPORT_INCLUDE)
	@rsync -a --include '*/' --include '*.hpp' --include '*.h' --include '*.tpp' --exclude '*' $(SRC_DIR)/ $(EXPORT_INCLUDE)/

	@echo "[INSTALL] Library → $(EXPORT_LIB)"
	@mkdir -p $(EXPORT_LIB)
	@cp $(LIB) $(EXPORT_LIB)/
