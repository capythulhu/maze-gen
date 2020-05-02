#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "maze.h"

int main(int argc, char *argv[], char **envp) {
    int x,y;
    srand(time(NULL));

    maze *m = new_maze(atoi(argv[1]), atoi(argv[2]));
    carve_passage(0, 0, m);

    render_maze(m);
}