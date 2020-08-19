#include <windows.h>
#include <iostream>


//https://docs.microsoft.com/en-us/windows/console/setconsolecursorposition
void setCursorPos(short x, short y) {
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {x, y};
    SetConsoleCursorPosition(output, pos);

}

void SetWindow(int Width, int Height) {
    _COORD coord;
    coord.X = Width;
    coord.Y = Height;

    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = Height - 1;
    Rect.Right = Width - 1;

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle 
    SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size 
    SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size 
}

void setConsoleWindow(int width, int height) {
    HWND hwnd = GetConsoleWindow();
    RECT rect = {500, 500, width, height};
    MoveWindow(hwnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE);
}


float interpolate(float value, float leftMin, float leftMax, float rightMin, float rightMax) {
    float leftSpan = leftMax - leftMin;
    float rightSpan = rightMax - rightMin;

    float scale = float(value - leftMin) / (float) leftSpan;

    return (float) rightMin + (scale * (float) rightSpan);
}

int computeMandelbrot(float real_x, float imaginary_y) {
    float z_real = real_x;
    float z_imaginary = imaginary_y;

    int iterations = 100;

    for (int i = 0; i < iterations; i++) {

        float z_real_squared = z_real * z_real;
        float z_imaginary_squared = z_imaginary * z_imaginary;
        if (z_real_squared + z_imaginary_squared > 16.0) {
            return i;
        }
        z_real = z_real_squared - z_imaginary_squared + real_x;
        z_imaginary = 2.0f * z_real * z_imaginary + imaginary_y;

    }
    return iterations;
}

int main() {

    const int height = 90;
    const int width = 200;

    setCursorPos(0, 0);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width - 1; ++x) {

            float real_x = interpolate(x, 0, width, -2, 2);
            float imaginary_y = interpolate(y, 0, height, -2, 2);

            int tending_val = computeMandelbrot(real_x, imaginary_y);

            if (tending_val == 100) {
                std::cout << " ";
            } else {
                std::cout << ".";
            }

        }


        std::cout << '\n';
    }

    return 0;
}

