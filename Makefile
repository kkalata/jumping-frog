build:
	cd src; \
	gcc jumping_frog.c window.c frog.c cars.c -lncurses -o ../jumping_frog.bin;