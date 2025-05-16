CXX = /opt/homebrew/opt/llvm/bin/clang++
SDK_PATH = $(shell xcrun --show-sdk-path)
CXXFLAGS = -std=c++14 -fsanitize=address -g -isysroot $(SDK_PATH) -stdlib=libc++

test:
	$(CXX) $(CXXFLAGS) -o testcode testcode.cpp

test_no_debug:
	$(CXX) -std=c++14 -g -o testcode testcode.cpp

tutorial:
	$(CXX) -std=c++14 -g -o tutorial tutorial.cpp
