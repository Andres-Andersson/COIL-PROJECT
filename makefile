CC := gcc
OPTIONS := -Wall -Wextra -std=c99 -I. -Idata -Igame -Igame/dependencies -Imenu -Irender -Irender/data_render -Irender/gamerender -Irender/ncurses
LDFLAGS := -lncurses

OBJS := main.o \
        data/data.o \
        menu/menu.o \
        game/dependencies/levelmanager.o \
        game/dependencies/physics.o \
        game/dependencies/powers.o \
        game/gamemanager.o \
        render/data_render/datarender.o \
        render/gamerender/gamerender.o \
        render/ncurses/render.o

ARKANOID-COIL: ${OBJS}
	${CC} ${OBJS} ${OPTIONS} ${LDFLAGS} -o ARKANOID-COIL


main.o: main.c
	${CC} main.c -c ${OPTIONS} -o main.o

data/data.o: data/data.c data/data.h
	${CC} data/data.c -c ${OPTIONS} -o data/data.o

menu/menu.o: menu/menu.c menu/menu.h
	${CC} menu/menu.c -c ${OPTIONS} -o menu/menu.o

game/dependencies/levelmanager.o: game/dependencies/levelmanager.c game/dependencies/levelmanager.h game/dependencies/entities.h
	${CC} game/dependencies/levelmanager.c -c ${OPTIONS} -o game/dependencies/levelmanager.o

game/dependencies/physics.o: game/dependencies/physics.c game/dependencies/physics.h game/dependencies/entities.h
	${CC} game/dependencies/physics.c -c ${OPTIONS} -o game/dependencies/physics.o

game/dependencies/powers.o: game/dependencies/powers.c game/dependencies/powers.h game/dependencies/entities.h
	${CC} game/dependencies/powers.c -c ${OPTIONS} -o game/dependencies/powers.o

game/dependencies/gamemanager.o: game/dependencies/gamemanager.c game/dependencies/gamemanager.h
	${CC} game/dependencies/gamemanager.c -c ${OPTIONS} -o game/dependencies/gamemanager.o

render/data_render/datarender.o: render/data_render/datarender.c render/data_render/datarender.h
	${CC} render/data_render/datarender.c -c ${OPTIONS} -o render/data_render/datarender.o

render/gamerender/gamerender.o: render/gamerender/gamerender.c render/gamerender/gamerender.h
	${CC} render/gamerender/gamerender.c -c ${OPTIONS} -o render/gamerender/gamerender.o

render/ncurses/render.o: render/ncurses/render.c render/ncurses/render.h
	${CC} render/ncurses/render.c -c ${OPTIONS} -o render/ncurses/render.o

clean:
	rm *.o ARKANOID-COIL

