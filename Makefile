all:
	g++ -I include -L lib -o main \
	src/main.cpp src/init/graphics.cpp src/init/game.cpp src\init\music_and_background\audioManager.cpp \
	src\dictionary\wordManager.cpp \
	src\keyboard\keyboard.cpp \
	src\logic_game\grid.cpp src\logic_game\handleInput.cpp src\logic_game\wordProcessor.cpp \
	src\utils\utils.cpp \
	src\logic_game\popup.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf