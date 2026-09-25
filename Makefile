dev: dev-build
	./out/build/debug/c++sweeper

dev-build:
	cmake --preset debug
	cmake --build out/build/debug --target c++sweeper

release:
	cmake --preset release
	cmake --build out/build/release --target c++sweeper --target c++sweeper