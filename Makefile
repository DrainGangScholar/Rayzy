run:
	gcc -o main main.c -O3 -lSDL3 -lm && export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH && ./main
  
