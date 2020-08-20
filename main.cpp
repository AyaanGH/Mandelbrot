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
    SetConsoleMode(Handle,0x0200);
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

    const int height = 80;
    const int width = 150;

    SetWindow(width,height+1);
    setCursorPos(0, 0);
    HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );



    for (float zoom = 1; zoom < 100 ; zoom *= 1.04) {

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width - 1; ++x) {

                float real_x = interpolate(x, 0, width, -2+zoom, 2);
                float imaginary_y = interpolate(y, 0, height, -2, 2-zoom);

                int tending_val = computeMandelbrot(real_x, imaginary_y);

                if (tending_val == 100) {
                    SetConsoleTextAttribute(h, 0);
                    printf( " ");

                }

                else {
                    const char *symbol = "#";
                    if (tending_val > 90) {
                        SetConsoleTextAttribute(h, 4);
                        printf("%s", symbol);
                    }
                    else if (tending_val > 70) {
                        SetConsoleTextAttribute(h, 12);
                        printf("%s", symbol);
                    }
                    else if (tending_val > 50) {
                        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN);
                        printf("%s", symbol);
                    }
                    else if (tending_val > 30) {
                        SetConsoleTextAttribute(h, 14);
                        printf("%s", symbol);
                    }

                    else if (tending_val > 20) {
                        SetConsoleTextAttribute(h, 10);
                        printf("%s", symbol);
                    }
                    else if (tending_val > 10) {
                        SetConsoleTextAttribute(h, 2);
                        printf("%s", symbol);
                    }

                    else if (tending_val > 5) {
                        SetConsoleTextAttribute(h, 11);
                        printf("%s", symbol);
                    }
                    else if (tending_val > 4) {
                        SetConsoleTextAttribute(h, 3);
                        printf("%s", symbol);
                    }

                    else if (tending_val > 3) {
                        SetConsoleTextAttribute(h, 9);
                        printf("%s", symbol);
                    }
                    else if (tending_val > 2) {
                        SetConsoleTextAttribute(h, 1);
                        printf("%s", symbol);
                    }
                    else if (tending_val > 1) {
                        SetConsoleTextAttribute(h, 5);
                        printf("%s", symbol);
                    }

                    else
                    {
                        SetConsoleTextAttribute(h, 13);
                        printf("%s", symbol);
                    }
                }








//                else if (tending_val > 2) {std::cout << blue << normal;}
//                else if (tending_val > 1) {std::cout << magenta << normal;}
//                else {std::cout << l_magenta << normal;}
//
//                std::cout << "\033[0m ";
//                if (tending_val == 100) {
//                    std::cout << "\033[22;32mA";
//                } else {
//                    std::cout << " ";
//                }

            }


            std::cout << '\n';
        }
        std::system("cls");
    }

    return 0;
}

