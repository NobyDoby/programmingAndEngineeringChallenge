 #include <libpynq.h>
#include <stdio.h>
#include <string.h>

#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 240
#define START 'S'       /* starting position */
#define DESTINATION 'D' /* destination */
#define WALL '#'        /* wall */
#define NOT_VISITED '.' /* corridor */
#define PATH '+'        /* part of the current path */
#define VISITED '~'     /* corridor; part of a past path */

typedef struct
{
    int x;
    int y;
} coordinate_t;
typedef struct
{
    char grid[DISPLAY_WIDTH][DISPLAY_HEIGHT];
    coordinate_t size;
} maze_t;

void inputMaze(maze_t *maze);
void printMaze(maze_t *maze);
void displayMaze(display_t *display, maze_t *maze);
coordinate_t findStartDestination(maze_t *maze, coordinate_t *destination);
void swapStartDestination(maze_t *maze, coordinate_t *start, coordinate_t *destination);
void mirrorMaze(maze_t *maze);
int findPath(maze_t *maze, coordinate_t point, int len);
void resetPath(maze_t *maze);
int longestPath(maze_t *maze, coordinate_t point, int length);

int main(void)
{
    pynq_init();
    display_t display;
    display_init(&display);

    maze_t maze = {{{'\0'}}, {-1, -1}};
    coordinate_t destination = {-1, -1};
    coordinate_t start = {-1, -1};

    char cmd;
    int len = 0;
    int length = 0;
    while (1)
    {
        printf("Command? ");
        scanf(" %c", &cmd);
        switch (cmd)
        {
        case 'l':
            resetPath(&maze);
            start = findStartDestination(&maze, &destination);
            len = longestPath(&maze, start, length);
            if (len > 0)
            {
                printf("The length of the longest path is %d\n", len);
                resetPath(&maze);
                printMaze(&maze);
            }
            else
            {
                printf("No path found\n");
            }
            break;
        case 'r':
            resetPath(&maze);
            break;
        case 'f':
            start = findStartDestination(&maze, &destination);
            len = findPath(&maze, start, length);
            if (len > 0)
            {
                printf("Found a path of length %d\n", len);
                printMaze(&maze);
            }
            else
            {
                printf("No path found\n");
                printMaze(&maze);
            }
            
            break;
        case 'm':
            mirrorMaze(&maze);
            break;
        case 'S':
            start = findStartDestination(&maze, &destination);
            swapStartDestination(&maze, &start, &destination);
            break;
        case 's':
            start = findStartDestination(&maze, &destination);
            if (start.x == -1 && destination.x == -1)
            {
                printf("Maze contains no start\n");
                printf("Maze contains no destination\n");
            }
            else if (start.x == -1)
            {
                printf("Maze contains no start\n");
            }
            else if (destination.y == -1)
            {
                printf("Maze contains no destination\n");
            }
            else if (start.x != -1 && destination.x != -1)
            {
                printf("The start is at             (%3d,%3d)\n", start.x, start.y);
                printf("The first destination is at (%3d,%3d)\n", destination.x, destination.y);
            }
            break;
             case 'd':
                displayMaze(&display, &maze);
                break;
                
        case 'p':
            printMaze(&maze);
            break;
        case 'i':
            inputMaze(&maze);
            break;
        case 'q':
            printf("Bye!\n");
            return 0;
            break;
        default:
            printf("Unknown command '%c'\n", cmd);
        }
    }

    display_destroy(&display);
    pynq_destroy();
    return EXIT_SUCCESS;
}
void inputMaze(maze_t *maze)
{
    int i, j;
    int lin, col;
    int c = -1, k = 0;
    char val;
    printf("Number of rows? ");
    scanf(" %d", &lin);
    maze->size.y = lin;
    printf("Number of columns? ");
    scanf(" %d", &col);
    if (col < 2 || lin < 2)
    {
        printf("The number of rows and columns must be at least two\n");
        maze->size.y = -1;
        return;
    }
    maze->size.x = col;
    for (i = 0; i < lin; i++)
    {
        printf("Input row  %d: ", k);
        for (j = 0; j < col; j++)
        {

            scanf(" %c", &val);
            if (val == 'S')
            {
                c++;
                if (c > 0)
                {
                    printf("Dropping extra starting point\n");
                    val = '#';
                }
            }
            maze->grid[i][j] = val;
        }
        k++;
    }
}

void printMaze(maze_t *maze)
{
    int i = 0, j = 0;
    for (i = 0; i < maze->size.y; i++)
    {
        for (j = 0; j < maze->size.x; j++)
        {
            printf("%c", maze->grid[i][j]);
        }
        printf("\n");
    }
}

void displayMaze(display_t *display, maze_t *maze)
{
  int x1 = 0, x2 = 0, y1 = 0, y2 = DISPLAY_HEIGHT / maze->size.y - 1;
  int c = 0;
  displayFillScreen(display, RGB_BLACK);
  for (int i = 0; i < maze->size.y; i++)
  {
    x1 = 0;
    x2 = DISPLAY_WIDTH / maze->size.x - 1;
    for (int j = 0; j < maze->size.x; j++)
    {
      switch (maze->grid[i][j])
      {
      case WALL:
        c = RGB_RED;
        break;
      case PATH:
        c = RGB_YELLOW;
        break;
      case START:
        c = RGB_BLUE;
        break;
      case DESTINATION:
        c = RGB_GREEN;
        break;
      case VISITED:
        c = rgb_conv(100, 100, 100);
        break;
      case NOT_VISITED:
        c = RGB_BLACK;
        break;
      }

      displayDrawFillRect(display, x1, y1, x2, y2, c);

      x1 = x2 + 1;
      x2 = x2 + DISPLAY_WIDTH / maze->size.x;
      sleep_msec(70000);
    }
    sleep_msec(70000);
    y1 = y2 + 1;
    y2 = y2 + DISPLAY_HEIGHT / maze->size.y;
  }
  sleep_msec(70000);
}


coordinate_t findStartDestination(maze_t *maze, coordinate_t *destination)
{
    coordinate_t start = {-1, -1};
    int k = 0, c = 0;

    for (int i = 0; i < maze->size.y; i++)
    {
        for (int j = 0; j < maze->size.x; j++)
        {
            if (maze->grid[i][j] == START)
            {
                start.y = i;
                start.x = j;
                k++;
            }
            else if (maze->grid[i][j] == DESTINATION && c == 0)
            {
                destination->y = i;
                destination->x = j;
                c++;
            }
        }
    }

    if (k == 0)
    {
        start.x = -1;
        start.y = -1;
    }
    if (c == 0)
    {
        destination->x = -1;
        destination->y = -1;
    }

    return start;
}

void swapStartDestination(maze_t *maze, coordinate_t *start, coordinate_t *destination)
{
    char tmp[2][2];
    int k1 = 0, k2 = 0;

    k1 = start->x;
    k2 = start->y;
    start->x = destination->x;
    start->y = destination->y;
    destination->x = k1;
    destination->y = k2;

    tmp[0][0] = maze->grid[start->y][start->x];
    maze->grid[start->y][start->x] = maze->grid[destination->y][destination->x];
    maze->grid[destination->y][destination->x] = tmp[0][0];
}

void mirrorMaze(maze_t *maze)
{
    char aux = {'\0'};
    for (int i = 0; i < maze->size.y; i++)
    {
        for (int j = i + 1; j < maze->size.x; j++)
        {
            aux = maze->grid[i][j];
            maze->grid[i][j] = maze->grid[j][i];
            maze->grid[j][i] = aux;
        }
    }
    int k = maze->size.x;
    maze->size.x = maze->size.y;
    maze->size.y = k;
}

int findPath(maze_t *maze, coordinate_t point, int length)
{   // printf("%d %d %d\n", point.x, point.y, len);
    int j = point.x;
    int i = point.y;
    if (point.y < 0 || point.x < 0 || point.x >= maze->size.x || point.y >= maze->size.y)
    {
        return 0;
    }
    else if (maze->grid[i][j] == WALL || maze->grid[i][j] == VISITED || maze->grid[i][j] == PATH || (maze->grid[i][j] == START && length != 0))
    {
        return 0;
    }
    else if (maze->grid[i][j] == DESTINATION)
    {
        return length;
    }
    else if (maze->grid[i][j] != START && maze->grid[i][j] == NOT_VISITED)
    {
        maze->grid[i][j] = PATH;
    }

    int len = 0;
    coordinate_t nord = {-1, -1};
    nord.x = point.x;
    nord.y = point.y - 1;
    len = findPath(maze, nord, length + 1);
    if (len > 0)
    {
        return len;
    }

    coordinate_t east = {-1, -1};
    east.x = point.x + 1;
    east.y = point.y;
    len = findPath(maze, east, length + 1);
    if (len > 0)
    {
        return len;
    }

    coordinate_t sud = {-1, -1};
    sud.x = point.x;
    sud.y = point.y + 1;
    len = findPath(maze, sud, length + 1);
    if (len > 0)
    {
        return len;
    }
    coordinate_t west = {-1, -1};
    west.x = point.x - 1;
    west.y = point.y;
    len = findPath(maze, west, length + 1);
    if (len > 0)
    {
        return len;
    }
    j = point.x;
    i = point.y;
    if (maze->grid[i][j] != START)
    {

        maze->grid[i][j] = VISITED;
    }

    return 0;
}

void resetPath(maze_t *maze)
{
    for (int i = 0; i < maze->size.y; i++)
    {
        for (int j = 0; j < maze->size.x; j++)
        {
            if (maze->grid[i][j] == PATH || maze->grid[i][j] == VISITED)
            {
                maze->grid[i][j] = NOT_VISITED;
            }
        }
    }
}

int longestPath(maze_t *maze, coordinate_t point, int length) {
    int j = point.x;
    int i = point.y;
    //printf("%d %d %d\n", point.x, point.y, length);
    if (point.y < 0 || point.x < 0 || point.x >= maze->size.x || point.y >= maze->size.y) {
        return 0;
    } else if (maze->grid[i][j] == WALL || maze->grid[i][j] == PATH || (maze->grid[i][j] == START && length != 0)){
        return 0;
    } else if (maze->grid[i][j] == DESTINATION) {
        printf("Found a path of length %d\n", length);
        return length;
    
    } else if(maze->grid[i][j] != START && maze->grid[i][j] == NOT_VISITED){
        maze->grid[i][j] = PATH;
    }

    int len = 0;
    int maxPathLength = 0;

    coordinate_t north = {point.x, point.y - 1};
    len = longestPath(maze, north, length + 1);
    if (len > maxPathLength) {
        maxPathLength = len;
    }

    coordinate_t east = {point.x + 1, point.y};
    len = longestPath(maze, east, length + 1);
    if (len > maxPathLength) {
        maxPathLength = len;
    }

    coordinate_t south = {point.x, point.y + 1};
    len = longestPath(maze, south, length + 1);
    if (len > maxPathLength) {
        maxPathLength = len;
    }

    coordinate_t west = {point.x - 1, point.y};
    len = longestPath(maze, west, length + 1);
    if (len > maxPathLength) {
        maxPathLength = len;
    }
    if(maze->grid[i][j]!= START){
    maze->grid[i][j] = NOT_VISITED;
        
    }
   
    return maxPathLength;
}