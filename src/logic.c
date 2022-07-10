#include <stdio.h>
#include <time.h>
#define FIELD_WIDTH 10
#define FIELD_HEIGHT 10

int ballX = 7;
int ballY = 5;

int ballSpeedXProjection = 1;
int ballSpeedYProjection = 0;

int leftRocketY = 5;
int rightRocketY = 5;

void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;
    while (time(0) < retTime);
}

int main() {
    int counter = 0;
    while (1) {
        printf("Ball X = %d  Ball Y = %d\n", ballX, ballY);

        ballX += ballSpeedXProjection;
        ballY += ballSpeedYProjection;

        if (ballY >= FIELD_HEIGHT) {
            ballY = FIELD_HEIGHT - 1;
            ballSpeedYProjection *= -1;
        }

        if (ballY < 0) {
            ballY = 0;
            ballSpeedYProjection *= -1;
        }

        if (ballX >= FIELD_WIDTH) {
            if (ballY == rightRocketY - 1) {
                if (ballSpeedYProjection > 0) {
                    ballSpeedYProjection -= 1;
                } else if (ballSpeedYProjection == 0) {
                    ballY -= 1;
                    ballSpeedYProjection = -1;
                }

                ballX = FIELD_WIDTH - 1;
            } else if (ballY == rightRocketY + 1) {
                if (ballSpeedYProjection < 0) {
                    ballSpeedYProjection += 1;
                } else if (ballSpeedYProjection == 0) {
                    ballY += 1;
                    ballSpeedYProjection = 1;
                }

                ballX = FIELD_WIDTH - 1;
            } else if (ballY == rightRocketY) {
                ballX = FIELD_WIDTH - 2;
            } else {
                printf("Score\n");                              // Edit
                break;
            }

            ballSpeedXProjection *= -1;
        }

        if (ballX < 0) {
            if (ballY == leftRocketY - 1) {
                if (ballSpeedYProjection > 0) {
                    ballSpeedYProjection -= 1;
                } else if (ballSpeedYProjection == 0) {
                    ballY -= 1;
                    ballSpeedYProjection = -1;
                }

                ballX = 0;
            } else if (ballY == leftRocketY + 1) {
                if (ballSpeedYProjection < 0) {
                    ballSpeedYProjection += 1;
                } else if (ballSpeedYProjection == 0) {
                    ballY += 1;
                    ballSpeedYProjection = 1;
                }

                ballX = 0;
            } else if (ballY == leftRocketY) {
                ballX = 1;
            } else {
                printf("Score\n");                              // Edit
                break;
            }

            ballSpeedXProjection *= -1;
        }

        counter++;
        waitFor(1);                                             // delay
    }

    return 0;
}