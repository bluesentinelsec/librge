.PHONY: build

build:
	cmake -B build -S ./
	cmake --build build

run: build
	./build/test_main

clean:
	rm -rf build
