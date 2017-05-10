
source_dir=src
build_dir=build

compiler_libs=-lGL -lglfw -lGLEW
compiler_flags = -g --std=c++14 -Wall

source_files = $(wildcard $(source_dir)/*.cpp)
obj_files = $(patsubst src/%.cpp,obj/%.o,$(source_files))


$(build_dir)/game: $(obj_files)
	mkdir -p $(build_dir)
	clang++ $(compiler_libs) -o $@ $^

obj/%.o: src/%.cpp
	mkdir -p obj
	clang++ $(compiler_flags) -c -o $@ $<

run: $(build_dir)/game
	$(build_dir)/game
