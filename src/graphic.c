#include <stdio.h>

#define height 25
#define wight 80


void print_field(int y_racket_left,
                 int y_racket_right,
                 int x_ball, int y_ball,
                 int score_left,
                 int score_right) {
    int step_out = 3;
    for (int i = 0; i < height; i++) {
        for (int j = 0;  j < wight; j++) {
            if (i == 0 || i == height - 1)
                printf("-");
            else if (i >= y_racket_left - 1 && i <= y_racket_left + 1 && j == 0)
                printf("]");
            else if (i >= y_racket_right - 1 && i <= y_racket_right + 1 && j == wight - 1)
                printf("[");
            else if (j == x_ball && i == y_ball)
                printf("o");
            else if (score_left / 10 > 0 && j == wight / 2 - step_out - 2 && i == height / 2)
                printf("%d", score_left / 10);
            else if (j == wight / 2 - step_out - 1 && i == height / 2)
                printf("%d", score_left % 10);
            else if (score_right/ 10 > 0 && j == wight / 2 + step_out && i == height / 2)
                printf("%d", score_right / 10);
            else if (score_right/ 10 > 0 && j == wight / 2 + step_out + 1 && i == height / 2)
                printf("%d", score_right % 10);
            else if (j == wight / 2 + step_out && i == height / 2)
                printf("%d", score_right % 10);
            else if (j == wight / 2 - 1 || j == wight / 2)
                printf("|");
            else
                printf(" ");
        }
        printf("\n");
    }
}

void ending_field(int score_left, int score_right) {
    int step_out = 3;
    for (int i = 0; i < height; i++) {
        for (int j = 0;  j < wight; j++) {
            if (i == 0 || i == height - 1)
                printf("-");
            else if (i >= height / 2 - 1 && i <= height / 2 + 1 && j == 0)
                printf("]");
            else if (i >= height / 2 - 1 && i <= height / 2 + 1 && j == wight - 1)
                printf("[");
            else if (score_left / 10 > 0 && j == wight / 2 - step_out - 2 && i == height / 2)
                printf("%d", score_left / 10);
            else if (j == wight / 2 - step_out - 1 && i == height / 2)
                printf("%d", score_left % 10);
            else if (score_right/ 10 > 0 && j == wight / 2 + step_out && i == height / 2)
                printf("%d", score_right / 10);
            else if (score_right/ 10 > 0 && j == wight / 2 + step_out + 1 && i == height / 2)
                printf("%d", score_right % 10);
            else if (j == wight / 2 + step_out && i == height / 2)
                printf("%d", score_right % 10);
            else if (j == wight / 2 - 1 || j == wight / 2)
                printf("|");
            if (score_left == 21) {
                if (i == height / 2 && j == 17)
                    printf("winner");
                else if (i != height / 2 || j < 17 || j > 22)
                    printf(" ");
            } else {
                if (i == height / 2 && j == 57)
                    printf("winner");
                else if (i != height / 2 || j < 57 || j > 62)
                    printf(" ");
            }
        }
        printf("\n");
    }
}
