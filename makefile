debug:
	gcc -o build/debug/game src/*.c -O1 -Wall -std=c99 -Wno-missing-braces -I include/ -L lib/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

linux:
	gcc -o build/release/lizard src/*.c -O1 -w -std=c99 -Wno-missing-braces -I include/ -L lib/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

windows:
	gcc -o build/release/lizard.exe src/*.c -O1 -w -std=c99 -Wno-missing-braces -I include/ -L lib/ lib/libraylibwindows.a -lopengl32 -lgdi32 -lwinmm -mwindows