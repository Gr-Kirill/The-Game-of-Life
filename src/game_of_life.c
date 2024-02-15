#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define lenght 80
#define height 25

void main_change_array(int **, int **, int, int);
int count_neighbour(int **, int, int, int, int);
void clear_array(int **, int, int);
int check_static(int **, int **, int, int);
int check_life(int **, int, int);
void copy_mas(int **, int **, int, int);
void output_ans(int **, int, int);

int main(void) {
    int buf_time = 22500, flag_static = 1, flag_exit = 1;
    int **matr = malloc(lenght * height * sizeof(int) + height * sizeof(int *));
    int *ptr = (int *)(matr + height);
    int **result = malloc(lenght * height * sizeof(int) + height * sizeof(int *));
    int *start = (int *)(result + height);
    for (int i = 0; i < height; i++) {
        matr[i] = ptr + lenght * i;
        result[i] = start + lenght * i;
    }

    for (int i = 0; i < height; i++)
        for (int j = 0; j < lenght; j++) scanf("%d", &matr[i][j]);

    if (freopen("/dev/tty", "r", stdin) == NULL) {
        printf("n/a");
        flag_exit = 0;
    }

    initscr();

    while (flag_exit && check_life(matr, height, lenght) && flag_static) {
        nodelay(stdscr, true);
        output_ans(matr, height, lenght);
        printw("Сurrent speed = %.1lf\n", 1.e6 / buf_time);
        refresh();
        clear();
        usleep(buf_time * 10);

        clear_array(result, height, lenght);
        main_change_array(matr, result, height, lenght);           // в result новая матрица
        flag_static = check_static(matr, result, height, lenght);  // = 1 если изменения есть
        clear_array(matr, height, lenght);
        copy_mas(matr, result, height, lenght);

        char move = getch();
        switch (move) {
            case 's':
                if (buf_time < 115000) buf_time += 1000;
                break;
            case 'w':
                if (buf_time > 1000) buf_time -= 1000;
                break;
            case 'q':
                flag_exit = 0;
                break;
            default:
                break;
        }
    }
    endwin();

    free(result);
    free(matr);

    return 0;
}

int check_static(int **array, int **mas, int row, int col) {
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (array[i][j] != mas[i][j]) return 1;
    return 0;
}

int check_life(int **array, int row, int col) {
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (array[i][j]) return 1;
    return 0;
}

void copy_mas(int **array_to, int **array_from, int row, int col) {
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++) array_to[i][j] = array_from[i][j];
}

void clear_array(int **array, int row, int col) {
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++) array[i][j] = 0;
}

void output_ans(int **array, int row, int col) {
    printw("Press Q to exit the program!\n");
    printw("Press W to increase the speed\n");
    printw("Press S to decrease the speed\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (array[i][j])
                printw("%c", '*');
            else
                printw("%c", ' ');
        }
        printw("%c", '\n');
    }
    refresh();
}

void main_change_array(int **array, int **result, int row, int col) {
    int count_n;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            count_n = count_neighbour(array, i, j, row, col);
            if (array[i][j]) {  //Значит в ячейке что то есть
                if (count_n == 2 || count_n == 3) result[i][j] = 1;
            } else {  //Значит она пустая, значит смотрим рождается или нет
                if (count_n == 3) result[i][j] = 1;
            }
        }
    }
}

int count_neighbour(int **mas, int i, int j, int row, int col) {
    int ans = 0;
    if (mas[i][(j + 1) % col]) ans++;
    if (mas[(i + 1) % row][(j + 1) % col]) ans++;
    if (mas[(i + 1) % row][j]) ans++;
    if (mas[(i + 1) % row][(col + (j - 1)) % col]) ans++;
    if (mas[i][(col + (j - 1)) % col]) ans++;
    if (mas[(row + (i - 1)) % row][(col + (j - 1)) % col]) ans++;
    if (mas[(row + (i - 1)) % row][j]) ans++;
    if (mas[(row + (i - 1)) % row][(j + 1) % col]) ans++;
    return ans;
}
