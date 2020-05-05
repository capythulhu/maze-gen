#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Maze structure
typedef struct _maze {
    unsigned **grid;
    unsigned wid, hei;
} maze;

// Useful directions vars
enum direction { N = 1, S = 2, E = 4, W = 8 };
unsigned dirMap[] = { N, S, E, W };

// Creates a new, empty maze
maze *new_maze(int wid, int hei) {
    maze *m = malloc(sizeof(maze));
    m->wid = wid;
    m->hei = hei;
    m->grid = malloc(sizeof(int*) * wid);

    int i;
    for(i = 0; i < wid; i++) m->grid[i] = calloc(sizeof(int), hei);
    return m;
}

// Carve a passage through a wall (used recursively)
void carve_passage(int x, int y, maze *m) {
    int nx, ny;

    int i, j = rand() % 4;
    for(i = 0; i < 4; i++, j = (j + 1) % 4) {
        nx = x, ny = y;
        switch(dirMap[j]) {
            case N: ny--; break;
            case S: ny++; break;
            case E: nx++; break;
            case W: nx--; break;
        }

        if (nx < m->wid && nx >= 0 && ny < m->hei && ny >= 0 && !m->grid[nx][ny]) {
            m->grid[x][y] |= dirMap[j];
            m->grid[nx][ny] |= dirMap[j + (j & 1 ? -1 : 1)];
            carve_passage(nx, ny, m);
        }
    }
}

// Prints the maze
void render_maze(maze *m) {
    int x, y;
    printf(" ");
    for(x = 0; x < (m->wid * 2) - 1; x++) {
        printf("_");
    }
    printf("\n");

    for(y = 0; y < m->hei; y++) {
        printf("|");
        for(x = 0; x < m->wid; x++) {
            printf((m->grid[x][y] & S) ? " " : "_");
            if(m->grid[x][y] & E){
                printf(((m->grid[x][y] | m->grid[x + 1][y]) & S) ? " " : "_");
            } else {
                printf("|");
            }
        }
        printf("\n");
    }
}