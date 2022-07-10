#include <stdio.h>
#define width = 80
#define height = 25

void game() {
    int score1 = 0, score2 = 0;
    int direction_ball_y = 1, direction_ball_x = 1;

    while (score1 < 21 || score2 < 21) {
        int xball = width / 2, yball = (height / 2) + 1;
        int racket1_y = (height / 2) + 1;
        int racket2_y = (height / 2) + 1;
        char move, trash;
        direction_ball_x *= -1;

        if (score1 == 21 || score2 == 21) {
            ending_field(score1, score2);
            break;
        }
        while (1) {
            print_field(racket1_y, racket2_y, xball, yball, score1, score2);

            // racket
            scanf("%c%c", &move, &trash);
            racket1_y = racket1(move, racket1_y);
            racket2_y = racket2(move, racket2_y);
            //

            // i thing so
            direction_ball_y = BallMoveY(yball, direction_ball_y);
            direction_ball_x = BallMoveY(yball, direction_ball_x);
            //

            xball += direction_ball_x;
            yball += direction_ball_y;

            //check direction_ball_y [0, height]

            if (xball == 0) {
                score2++;
                break;
            } else if (xball == width - 1) {
                score1++;
                break;
            }
       }
    }
}

// int collision() {
// }

// int ball() {
// }


int racket1(char com, int y) {
    if ((com == 'a' || com == 'A') &&  y - 1 != 1) {
        return y - 1;
    } else if ((com == 'z' || com == 'Z') && y + 1 != height) {
        return y + 1;
    } else {
        return y;
    }
}

int racket2(char change, int y) {
    if ((change == 'k' || change == 'K') && y-1 != 1) {
        return y - 1;
    } else if ((change == 'm' || change == 'M') && y + 1 != height) {
        return y + 1;
    } else {
        return y;
    }
}

int main() {
    game();
    return 0;
}
