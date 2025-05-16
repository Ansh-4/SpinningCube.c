#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

// declaration of constants and various parameters
const float cubeWidth = 20;
const int width = 40, height = 22;
const int distancecam = 100;
const float k1 = 40;
const int backgroundASCIIcode = ' ';

// using z-buffering 
float zBuffer[40 * 22];
char buffer[40 * 22];
float A = 0, B = 0, C = 0;
float x, y, z, ooz;
int xp, yp, idx;


float CalculateX(float i, float j, float k) {
    return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C)
         + j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

float CalculateY(float i, float j, float k) {
    return j * cos(A) * cos(C) + k * sin(A) * cos(C)
         - j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C)
         - i * cos(B) * sin(C);
}

float CalculateZ(float i, float j, float k) {
    return k * cos(A) * sin(B) - j * sin(A) * cos(B) + i * sin(B);
}


void CalculateForthePoint(float i, float j, float k, int ch) {
    x = CalculateX(i, j, k);
    y = CalculateY(i, j, k);
    z = CalculateZ(i, j, k) + distancecam;
    ooz = 1 / z;
    xp = (int)(width / 2 + k1 * ooz * x * 2);
    yp = (int)(height / 2 + k1 * ooz * y);
    idx = xp + yp * width;
    if (idx >= 0 && idx < width * height) {
        if (ooz > zBuffer[idx]) {
            zBuffer[idx] = ooz;
            buffer[idx] = ch;
        }
    }
}

int main() {
    // Clear screen
    printf("\x1b[2J"); //escape code

    while (1) {
        // Clear buffers
        memset(buffer, backgroundASCIIcode, width * height);
        memset(zBuffer, 0, width * height * sizeof(float));

        for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += 1.00 {
            for (float cubeY = -cubeWidth; cubeY < cubeWidth; cubeY += 1.00) {
                // Each face of the cube
                CalculateForthePoint(cubeX, cubeY, -cubeWidth, '#');  // Front
                CalculateForthePoint(cubeWidth, cubeY, cubeX, '$');   // Right
                CalculateForthePoint(-cubeWidth, cubeY, -cubeX, '~'); // Left
                CalculateForthePoint(-cubeX, cubeY, cubeWidth, '@');  // Back
                CalculateForthePoint(cubeX, -cubeWidth, -cubeY, '%'); // Bottom
                CalculateForthePoint(cubeX, cubeWidth, cubeY, '&');   // Top
            }
        }

        // Reset cursor using escape code
        printf("\x1b[H");

        // Print buffer
        for (int k = 0; k < width * height; k++) {
            putchar(k % width ? buffer[k] : '\n');
        }

        
        A += 0.05;
        B += 0.05;
        C += 0.01;

        
        usleep(8000*2);
    }

    return 0;
}



