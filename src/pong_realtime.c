#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

struct termios savedAttributes;

void to_noncanon();
void to_canon();
void game(const int width, const int height);
void ballMove(const int width, const int height,
                int* ballY, int* ballX,
                int* ballSpeedYProjection, int* ballSpeedXProjection,
                int leftRocketY, int rightRocketY);
int racket1(const int height, char com, int y);
int racket2(const int height, char com, int y);
void print_field(const int width, const int height,
                    int y_racket_left, int y_racket_right,
                    int x_ball, int y_ball,
                    int score_left, int score_right);
void ending_field(const int width, const int height,
                    int score_left, int score_right);

int main() {
    const int WIDTH = 80;
    const int HEIGHT = 25;

    to_noncanon();
    game(WIDTH, HEIGHT);
    to_canon();

    return 0;
}

void to_noncanon() {
    struct termios tattr;
    int flags = fcntl(0, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(0, F_SETFL, flags);
    tcgetattr(0, &savedAttributes);
    atexit(to_canon);
    tcgetattr(0, &tattr);
    tattr.c_lflag &= ~(ICANON|ECHO);
    tattr.c_cc[VMIN] = 1;
    tattr.c_cc[VTIME] = 0;
    tcsetattr(0, TCSAFLUSH, &tattr);
}

void to_canon() {
    tcsetattr(0, TCSAFLUSH, &savedAttributes);
}

void game(const int width, const int height) {
    int score1 = 0, score2 = 0;
    int last_start = 1;

    while (1) {
        int direction_ball_y = 1, direction_ball_x = 1;
        int xball = width / 2, yball = (height / 2) + 1;
        int racket1_y = (height / 2) + 1;
        int racket2_y = (height / 2) + 1;

        last_start *= -1;
        direction_ball_x *= last_start;

        if (score1 == 21 || score2 == 21) {
            ending_field(width, height, score1, score2);
            break;
        }

        while (1) {
            print_field(width, height, racket1_y, racket2_y, xball, yball, score1, score2);

            char move = getchar();

            racket1_y = racket1(height, move, racket1_y);
            racket2_y = racket2(height, move, racket2_y);

            ballMove(width, height, &yball, &xball,
                &direction_ball_y, &direction_ball_x,
                racket1_y, racket2_y);

            if (xball == 0) {
                score2++;
                break;
            }

            if (xball == width - 1) {
                score1++;
                break;
            }

            usleep(100000);
       }
    }
}

void ballMove(const int width, const int height,
                int* ballY, int* ballX,
                int* ballSpeedYProjection, int* ballSpeedXProjection,
                int leftRocketY, int rightRocketY) {
    *ballX += *ballSpeedXProjection;
    *ballY += *ballSpeedYProjection;

    if (*ballY >= height - 1) {
        *ballY = height - 2;
        *ballSpeedYProjection *= -1;
        *ballY += *ballSpeedYProjection;
    }

    if (*ballY <= 0) {
        *ballY = 1;
        *ballSpeedYProjection *= -1;
        *ballY += *ballSpeedYProjection;
    }

    if (*ballX >= width - 1) {
        if (*ballY == rightRocketY - 2) {
            if (*ballSpeedYProjection < 0) {
                *ballSpeedYProjection -= 1;
                *ballX = width - 2;
            }
        } else if (*ballY == rightRocketY - 1) {
            if (*ballSpeedYProjection < 0) {
                *ballSpeedYProjection -= 1;
            } else if (*ballSpeedYProjection == 0) {
                *ballSpeedYProjection -= 1;
            }

            *ballX = width - 2;
        } else if (*ballY == rightRocketY + 1) {
            if (*ballSpeedYProjection > 0) {
                *ballSpeedYProjection += 1;
            } else if (*ballSpeedYProjection == 0) {
                *ballSpeedYProjection += 1;
            }

            *ballX = width - 2;
        } else if (*ballY == leftRocketY + 2) {
            if (*ballSpeedYProjection > 0) {
                *ballSpeedYProjection += 1;
                *ballX = width - 2;
            }
        } else if (*ballY == rightRocketY) {
            *ballX = width - 3;
        }

        *ballSpeedXProjection *= -1;
    }

    if (*ballX < 1) {
        if (*ballY == leftRocketY - 2) {
            if (*ballSpeedYProjection < 0) {
                *ballSpeedYProjection -= 1;
                *ballX = 1;
            }
        } else if (*ballY == leftRocketY - 1) {
            if (*ballSpeedYProjection > 0) {
                *ballSpeedYProjection -= 1;
            } else if (*ballSpeedYProjection < 0) {
                *ballSpeedYProjection -= 1;
            } else {
                *ballSpeedYProjection -= 1;
            }

            *ballX = 1;
        } else if (*ballY == leftRocketY + 1) {
             if (*ballSpeedYProjection > 0) {
                *ballSpeedYProjection += 1;
            } else if (*ballSpeedYProjection < 0) {
                *ballSpeedYProjection += 1;
            } else {
                *ballSpeedYProjection += 1;
            }

            *ballX = 1;
        } else if (*ballY == leftRocketY + 2) {
            if (*ballSpeedYProjection > 0) {
                *ballSpeedYProjection += 1;
                *ballX = 1;
            }
        } else if (*ballY == leftRocketY) {
            *ballX = 2;
        }

        *ballSpeedXProjection *= -1;
    }
}

int racket1(const int height, char com, int y) {
    if ((com == 'a' || com == 'A') &&  y > 2) {
        return y - 1;
    }

    if ((com == 'z' || com == 'Z') && y + 3 < height) {
        return y + 1;
    }

    return y;
}

int racket2(const int height, char change, int y) {
    if ((change == 'k' || change == 'K') && y > 2) {
        return y - 1;
    }

    if ((change == 'm' || change == 'M') && y + 3 < height) {
        return y + 1;
    }

    return y;
}

void print_field(const int width, const int height,
                    int y_racket_left, int y_racket_right,
                    int x_ball, int y_ball,
                    int score_left, int score_right) {
    int step_out = 3;

    printf("\033[2J");

    for (int i = 0; i < height; i++) {
        for (int j = 0;  j < width; j++) {
            if (i == 0 || i == height - 1)
                printf("-");
            else if (i >= y_racket_left - 1 && i <= y_racket_left + 1 && j == 0)
                printf("]");
            else if (i >= y_racket_right - 1 && i <= y_racket_right + 1 && j == width - 1)
                printf("[");
            else if (j == x_ball && i == y_ball)
                printf("o");
            else if (score_left / 10 > 0 && j == width / 2 - step_out - 2 && i == height / 2)
                printf("%d", score_left / 10);
            else if (j == width / 2 - step_out - 1 && i == height / 2)
                printf("%d", score_left % 10);
            else if (score_right/ 10 > 0 && j == width / 2 + step_out && i == height / 2)
                printf("%d", score_right / 10);
            else if (score_right/ 10 > 0 && j == width / 2 + step_out + 1 && i == height / 2)
                printf("%d", score_right % 10);
            else if (j == width / 2 + step_out && i == height / 2)
                printf("%d", score_right % 10);
            else if (j == width / 2 - 1 || j == width / 2)
                printf("|");
            else
                printf(" ");
        }

        printf("\n");
    }
}

void ending_field(const int width, const int height,
                    int score_left, int score_right) {
    int step_out = 3;

    for (int i = 0; i < height; i++) {
        for (int j = 0;  j < width; j++) {
            if (i == 0 || i == height - 1) {
                printf("-");
            } else if (i >= height / 2 - 1 && i <= height / 2 + 1 && j == 0) {
                printf("]");
            } else if (i >= height / 2 - 1 && i <= height / 2 + 1 && j == width - 1) {
                printf("[");
            } else if (score_left / 10 > 0 && j == width / 2 - step_out - 2 && i == height / 2) {
                printf("%d", score_left / 10);
            } else if (j == width / 2 - step_out - 1 && i == height / 2) {
                printf("%d", score_left % 10);
            } else if (score_right/ 10 > 0 && j == width / 2 + step_out && i == height / 2) {
                printf("%d", score_right / 10);
            } else if (score_right/ 10 > 0 && j == width / 2 + step_out + 1 && i == height / 2) {
                printf("%d", score_right % 10);
            } else if (j == width / 2 + step_out && i == height / 2) {
                printf("%d", score_right % 10);
            } else if (j == width / 2 - 1 || j == width / 2) {
                printf("|");
            } else if (score_left == 21) {
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
