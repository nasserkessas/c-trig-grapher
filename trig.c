#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define PI 3.141592

void usage(char *name) {
    printf("\nUsage: %s [OPTIONS]\n\n\t-r : Range (-r < x < r) \n\t-d : Domain (0 < x < d) (in π)\n\t-x : X unit size\n\t-y : Y unit size\n\t-f : Function (sin, cos or tan)\n\n", name);
}

int arrayFind(char *element, char **list, int len) {
    for (int i=0; i < len; i++) {
        if (!strcasecmp(element, list[i])) return i;
    }
    return -1;
}

int main(int argc, char **argv) {
    char *functions[] = { "sin", "cos", "tan" };
    int function_amount = 3;

    double RANGE = 1;
    double DOMAIN = 3;
    int XUNITSIZE = 5;
    int YUNITSIZE = 5;
    int FUNCTION = 0;

    if (argc == 1) {
        usage(argv[0]);
        return 1;
    }

    for (int i=1; i<argc; i+=2) {
        char *name = argv[i]+1;

        if (*name == 'f') {
            if (isalpha(*argv[i+1])) {

                int arrayPos = arrayFind(argv[i+1], functions, function_amount);

                if (arrayPos == -1) {
                    printf("Invalid argument for function: \"%s\"\n", argv[i+1]);
                } else {
                    FUNCTION = arrayPos;
                    printf("Function: %s\n", functions[FUNCTION]);
                }
                
            } else {
                printf("Invalid argument for function: \"%s\"\n", argv[i+1]);
            }
        }
            
        if (*name == 'r'){
            if (isdigit(*argv[i+1])){
                RANGE = atof(argv[i+1]);
                printf("Range = -%.1f < x < %.1f\n", RANGE, RANGE);;
            } else {
                printf("Invalid argument for range: \"%s\"\n", argv[i+1]);
            }
        }
        
        if (*name == 'd'){
            if (isdigit(*argv[i+1])){
                DOMAIN = atof(argv[i+1]);
                printf("Domain = 0 < x < %.1fπ\n", DOMAIN);;
            } else {
                printf("Invalid argument for domain: \"%s\"\n", argv[i+1]);
            }
        }

        else if (*name == 'x'){
            if (isdigit(*argv[i+1])){
                XUNITSIZE = atoi(argv[i+1]);
                printf("X unit size = %d\n", XUNITSIZE);;
            } else {
                printf("Invalid argument for x unit size: \"%s\"\n", argv[i+1]);
            }
        }

        else if (*name == 'y'){
            if (isdigit(*argv[i+1])){
                YUNITSIZE = atoi(argv[i+1]);
                printf("Y unit size = %d\n", YUNITSIZE);;
            } else {
                printf("Invalid argument for y unit size: \"%s\"\n", argv[i+1]);
            }
        }

    }

    double v, x, y;
    double stepx, stepy;
    int axis_drawn = 0;
    int point_drawn = 0;
    stepx = (double) 1 / XUNITSIZE;
    stepy = (double) RANGE / YUNITSIZE;

    int points[(int) (DOMAIN*PI/stepx) + 1][(int) (2*RANGE/stepy) + 2];

    int x_index = 0;
    int y_index = 0;
    for (x = 0; x <= DOMAIN*PI; x += stepx) {
        // if (x == 0) {
        //     for (double i = 0; i <= RANGE * 2; i += stepy) {
        //         putchar('_');
        //     }
        //     putchar('\n');
        // }
        switch (FUNCTION) {
            case 0: v = sin(x); break;
            case 1: v = cos(x); break;
            case 2: v = tan(x); break;
        }

        axis_drawn = 0;
        point_drawn = 0;
        y_index = 0;
        for (y = -RANGE; y <= ((double) RANGE + stepy); y += stepy) {
            if (y >= v && point_drawn == 0) {
                points[x_index][y_index] = 1;
                point_drawn = 1;
                if (y >= 0) { axis_drawn = 1; }
            }
            else if (y >= 0 && axis_drawn == 0) {
                points[x_index][y_index] = 2;
                axis_drawn = 1;
            } else {
                points[x_index][y_index] = 0;
            }
            y_index++;
        }
        // putchar('\n');
        x_index++;
    }

    // for (y = -RANGE; y <= RANGE; y += stepy) {
    //     if (abs(x - y) < 1e-10) { // y == 0 with error margin of 1e-10
    //         for (double i = 0; i <= DOMAIN * 2; i += stepx) {
    //             putchar('-');
    //         }
    //     }
    //     putchar('\n');
    //     // printf("%f\n", y);
    // }

    for (int i = y_index; i > 0; i--) {
        putchar('|');
        for (int j = 0; j < x_index; j++) {
            switch ((int) points[j][i]) {
            case 0:
                putchar(' ');
                break;
            case 1:
                putchar('x');
                break;
            case 2:
                putchar('-');
                break;
            }
        }
        putchar('\n');
    }

    return 0;
}