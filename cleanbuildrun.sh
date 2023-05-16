# !bin/sh

rm -r build; mkdir build; cmake -DCMAKE_BUILD_TYPE=Debug -S src/ -B build/; make -C build/; ./build/desktop-engine