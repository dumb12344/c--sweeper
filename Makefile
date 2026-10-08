test: dev
	./out/debug/c++sweeper

test-clang: dev-clang
	./out/debug-clang/c++sweeper

dev:
	cmake --preset debug
	cmake --build out/debug --target c++sweeper

dev-clang:
	cmake --preset debug-clang
	cmake --build out/debug-clang --target c++sweeper

release:
	cmake --preset release
	cmake --build out/release --target c++sweeper

release-clang:
	cmake --preset release-clang
	cmake --build out/release-clang --target c++sweeper

release-emscripten:
	mkdir out/emscripten -p
	cd out/emscripten && /usr/lib/emscripten/emcmake cmake ../..
	cd out/emscripten && cmake --build . --target c++sweeper
	cp src/c++sweeper.html out/emscripten/c++sweeper.html

clean:
	rm -rf out
