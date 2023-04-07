# This project uses CMake and Git sub-modules. This Makefile is just in place
# to make common tasks easier.

.PHONY: build/eyeball_unittests

run: build/eyeball_unittests
	./build/eyeball_unittests

bench: build/eyeball_benchmarks
	./build/eyeball_benchmarks

debug:
	mkdir -p build/debug
	cmake -G Ninja -B build/debug -DCMAKE_BUILD_TYPE=Debug
	ninja -C build/debug

test: build/eyeball_unittests
	cd build && ctest -C build

build/eyeball_unittests: build/build.ninja
	ninja -C build

build/eyeball_benchmarks: build/build.ninja
	ninja -C build eyeball_benchmarks

build/build.ninja:
	mkdir -p build
	cmake -G Ninja -B build -DCMAKE_BUILD_TYPE=Release

clean:
	rm -rf build

sync:
	git submodule update --init --recursive -j 8

xcode:
	mkdir -p build/xcode
	cmake -G Xcode -B build/xcode -DCMAKE_BUILD_TYPE=Debug
	open build/xcode/sft.xcodeproj
