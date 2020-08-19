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


float interpolate(int value, int leftMin, int leftMax, int rightMin, int rightMax) {
    int leftSpan = leftMax - leftMin;
    int rightSpan = rightMax - rightMin;

    float scale = float(value - leftMin) / (float) leftSpan;

    return (float) rightMin + (scale * (float) rightSpan);
}

int main() {

    const int height = 90;
    const int width = 200;
    SetWindow(width, height);
    setCursorPos(0, 0);


    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width - 1; ++x) {

            float b = interpolate(y, 0, height, -2, 2);
            float a = interpolate(x, 0, width, -2, 2);

            float ca = a;
            float cb = b;

            int n = 0;


            while (n < 100) {
                //a^2 - b^2 == aabb

                float aabb = a * a - b * b;

                float ab = 2 * a * b;

                a = aabb + ca;

                b = ab + cb;

                if (std::abs(a + b) > 16) {
                    break;
                }
                ++n;

            }


            if (n == 100) {
                std::cout << "O";
            } else {
                std::cout << " ";
            }

        }

        std::cout << '\n';
    }
//    setCursorPos(0, 0);
    return 0;
}