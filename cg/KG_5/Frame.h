// Frame.h
#ifndef FRAME_H
#define FRAME_H

#include <math.h>

// C�������� ��� ������� �����
typedef struct tagCOLOR
{
    unsigned char RED;        // ���������� �������� �����
    unsigned char GREEN;      // ���������� ������� �����
    unsigned char BLUE;       // ���������� ������ �����
    unsigned char ALPHA;      // ������������ (����� �����)

    tagCOLOR(int red, int green, int blue, int alpha = 255)
        : RED(red), GREEN(green), BLUE(blue), ALPHA(alpha) { }

} COLOR;


typedef struct tagPIXEL
{
    unsigned char RED;        // ���������� �������� �����
    unsigned char GREEN;      // ���������� ������� �����
    unsigned char BLUE;       // ���������� ������ �����
    float Z;                   // ������� �������

    tagPIXEL() : RED(0), GREEN(0), BLUE(0), Z(INFINITY) { }
} PIXEL;


template<typename TYPE> void customSwap(TYPE& a, TYPE& b)
{
    TYPE t = a;
    a = b;
    b = t;
}


// ����� �����
class Frame
{
    // ��������� �� ������ ��������
    // ����� ����� ����� ������������ ����� �������, ������� ������������� � ������ � ���� ������������ �����
    PIXEL* pixels;
private:
    const int INSIDE = 0; // 0000
    const int LEFT = 1;   // 0001
    const int RIGHT = 2;  // 0010
    const int BOTTOM = 4; // 0100
    const int TOP = 8;    // 1000

    // ������� ��� ���������� outcode ����� (������������ � ��������� ���������)
    int ComputeOutCode(int x, int y) {
        int code = INSIDE;

        if (x < 0)
            code |= LEFT;
        else if (x > width - 1)
            code |= RIGHT;
        if (y < 0)
            code |= BOTTOM;
        else if (y > height - 1)
            code |= TOP;

        return code;
    }
public:
    // ������� ������ �����
    int width, height;

    Frame(int _width, int _height) : width(_width), height(_height)
    {
        int size = width * height;

        // �������� ������ ����� � ���� ����������� ������� ��������
        pixels = new PIXEL[size];

        // ���������� ����� ������ ������-����� ������
        for (int i = 0; i < size; i++)
        {
            pixels[i].RED = 211;
            pixels[i].GREEN = 211;
            pixels[i].BLUE = 211;
            // pixels[i].Z �������� ������ INFINITY
        }
    }

    // ����� ���� color ������� � ������������ (x, y) � ������ ������������
    void SetPixel(int x, int y, COLOR color) {
        if (x < 0 || x >= width || y < 0 || y >= height)
            return;

        PIXEL* pixel = pixels + (size_t)y * width + x;
        float alpha = color.ALPHA / 255.0f;

        // �����-��������: ����� ���� ������ �������������
        pixel->RED = static_cast<unsigned char>(color.RED * alpha + pixel->RED * (1.0f - alpha));
        pixel->GREEN = static_cast<unsigned char>(color.GREEN * alpha + pixel->GREEN * (1.0f - alpha));
        pixel->BLUE = static_cast<unsigned char>(color.BLUE * alpha + pixel->BLUE * (1.0f - alpha));

        // ���������� Z-������ (����������������, ��� ��� Z-����� �� ������������)
        // pixel->Z = Z;
    }

    // ���������� ���� ������� � ������������ (x, y)
    COLOR GetPixel(int x, int y)
    {
        PIXEL* pixel = pixels + (size_t)y * width + x; // ������� ������ ������� � ������� �������� pixels
        return COLOR(pixel->RED, pixel->GREEN, pixel->BLUE, 255); // ���������� ���� � ������ ���������������
    }

    void Triangle(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, COLOR color)
    {
        // ����������� ����� ����� �������, ����� ����������� �������: y0 < y1 < y2
        if (y1 < y0)
        {
            customSwap(x1, x0);
            customSwap(y1, y0);
            customSwap(z1, z0);
        }
        if (y2 < y1)
        {
            customSwap(x2, x1);
            customSwap(y2, y1);
            customSwap(z2, z1);
        }
        if (y1 < y0)
        {
            customSwap(x1, x0);
            customSwap(y1, y0);
            customSwap(z1, z0);
        }

        // ���������� ������ ����� ��������, � ������� ������������� ����� ������������
        int Y0 = static_cast<int>(y0 + 0.5f);
        int Y1 = static_cast<int>(y1 + 0.5f);
        int Y2 = static_cast<int>(y2 + 0.5f);

        // ��������� ��������� ����� ������������
        if (Y0 < 0) Y0 = 0;
        else if (Y0 > height) Y0 = height;

        if (Y1 < 0) Y1 = 0;
        else if (Y1 > height) Y1 = height;

        if (Y2 < 0) Y2 = 0;
        else if (Y2 > height) Y2 = height;

        float S = (y1 - y2) * (x0 - x2) + (x2 - x1) * (y0 - y2); // ������� ������������

        // ��������� ������� ����� ������������ 
        for (int Y = Y0; Y < Y1; Y++)
        {
            float y = Y + 0.5f; // ���������� y �������� �������

            // ���������� ��������� ��������� ��������
            int X0 = static_cast<int>((y - y0) / (y1 - y0) * (x1 - x0) + x0 + 0.5f);
            int X1 = static_cast<int>((y - y0) / (y2 - y0) * (x2 - x0) + x0 + 0.5f);

            if (X0 > X1) customSwap(X0, X1); // ���������� ��������
            if (X0 < 0) X0 = 0; // ��������� ��������� �������� � ������ y
            if (X1 > width) X1 = width;

            for (int X = X0; X < X1; X++)
            {
                double x = X + 0.5; // ���������� x �������� �������

                // �������� ������� ����� ���������� (x, y)
                // �������� ���������������� ���������� ����� �������
                float h0 = ((y1 - y2) * (x - x2) + (x2 - x1) * (y - y2)) / S;
                float h1 = ((y2 - y0) * (x - x2) + (x0 - x2) * (y - y2)) / S;
                float h2 = ((y0 - y1) * (x - x1) + (x1 - x0) * (y - y1)) / S;

                float Z = h0 * z0 + h1 * z1 + h2 * z2; // ������� �������

                // ����������� ������� ����� � �������� ������� ���������
                PIXEL* pixel = pixels + (size_t)Y * width + X; // �������� ����� ������� (Y, X) � ������� �������� pixels

                // ������� ���������� ������� ��� ����� Z-������
                if (Z > -1 && Z < 1 /* && Z < pixel->Z */) // ������� � Z-������� ����������������
                {
                    // ��������� ���� ������� � ������ ������������
                    SetPixel(X, Y, color);

                    // ���������� Z-������ ����������������
                    // pixel->Z = Z;
                }
            }
        }

        // ��������� ������ ����� ������������
        for (int Y = Y1; Y < Y2; Y++)
        {
            float y = Y + 0.5f; // ���������� y �������� �������

            // ���������� ��������� ��������� ��������
            int X0 = static_cast<int>((y - y1) / (y2 - y1) * (x2 - x1) + x1 + 0.5f);
            int X1 = static_cast<int>((y - y0) / (y2 - y0) * (x2 - x0) + x0 + 0.5f);

            if (X0 > X1) customSwap(X0, X1);  // ���������� ��������
            if (X0 < 0) X0 = 0; // ��������� ��������� �������� � ������ y
            if (X1 > width) X1 = width;

            for (int X = X0; X < X1; X++)
            {
                double x = X + 0.5; // ���������� x �������� �������

                // �������� ������� ����� ���������� (x, y)
                // �������� ���������������� ���������� ����� �������
                float h0 = ((y1 - y2) * (x - x2) + (x2 - x1) * (y - y2)) / S;
                float h1 = ((y2 - y0) * (x - x2) + (x0 - x2) * (y - y2)) / S;
                float h2 = ((y0 - y1) * (x - x1) + (x1 - x0) * (y - y1)) / S;

                float Z = h0 * z0 + h1 * z1 + h2 * z2; // ������� �������

                // ����������� ������� ����� � �������� ������� ���������
                PIXEL* pixel = pixels + (size_t)Y * width + X;

                // ������� ���������� ������� ��� ����� Z-������
                if (Z > -1 && Z < 1 /* && Z < pixel->Z */)
                {
                    // ��������� ���� ������� � ������ ������������
                    SetPixel(X, Y, color);

                    // ���������� Z-������ ����������������
                    // pixel->Z = Z;
                }
            }
        }
    }

    // ��������� ��������, ������������ �� ��� ������������
    void Quad(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, COLOR color)
    {
        Triangle(x0, y0, z0, x1, y1, z1, x2, y2, z2, color);
        Triangle(x2, y2, z2, x3, y3, z3, x0, y0, z0, color);
    }

    // ��������� ����� � �������������� ��������� ����������-�����
    void DrawLine(int x1, int y1, int x2, int y2, COLOR color)
    {
        // ��������� ��������� ��� ������ (outcode) ��� ������ �����
        int outcode0 = ComputeOutCode(x1, y1);
        // ��������� ��������� ��� ������ (outcode) ��� ������ �����
        int outcode1 = ComputeOutCode(x2, y2);

        // ���������� ��� ��������, ����� �� ������� ����� ����� ���������
        bool accept = false;

        // ��������� ���� ��� ��������� �����
        while (true) {
            // ���� ��� ����� ��������� ������ �������� ��������������
            if (!(outcode0 | outcode1)) {
                accept = true;
                break;
            }
            // ���� ��� ����� ��� �������� �������������� � ����� � ��� �� �������
            else if (outcode0 & outcode1) {
                break;
            }
            // ���� ���� ����� ��� ��������������, � ������ ������
            else {
                int x, y; // ���������� ��� ��������� ����� �����������
                // ���������� ��� ������ ��� �����, ����������� ��� ��������������
                int outcodeOut = outcode0 ? outcode0 : outcode1;

                // ��������� ����������� � ������� ��������
                if (outcodeOut & TOP) {
                    // ��������� ���������� ����������� � ������� ��������
                    x = x1 + (x2 - x1) * (height - 1 - y1) / (y2 - y1);
                    y = height - 1;
                }
                // ��������� ����������� � ������ ��������
                else if (outcodeOut & BOTTOM) {
                    // ��������� ���������� ����������� � ������ ��������
                    x = x1 + (x2 - x1) * (0 - y1) / (y2 - y1);
                    y = 0;
                }
                // ��������� ����������� � ������ ��������
                else if (outcodeOut & RIGHT) {
                    // ��������� ���������� ����������� � ������ ��������
                    y = y1 + (y2 - y1) * (width - 1 - x1) / (x2 - x1);
                    x = width - 1;
                }
                // ��������� ����������� � ����� ��������
                else if (outcodeOut & LEFT) {
                    // ��������� ���������� ����������� � ����� ��������
                    y = y1 + (y2 - y1) * (0 - x1) / (x2 - x1);
                    x = 0;
                }

                // ��������� ���������� �����, ������� ���� ��� ��������������
                if (outcodeOut == outcode0) {
                    x1 = x;
                    y1 = y;
                    outcode0 = ComputeOutCode(x1, y1); // ������������� ��� ������ ��� ����� �����
                }
                else {
                    x2 = x;
                    y2 = y;
                    outcode1 = ComputeOutCode(x2, y2); // ������������� ��� ������ ��� ����� �����
                }
            }
        }

        // ���� ����� ���� ������� ��� ���������
        if (accept) {
            // ��������� ���������� �� x � y
            int dx = abs(x2 - x1);
            int dy = abs(y2 - y1);
            // ���������� ����������� �������� �� x
            int sx = (x1 < x2) ? 1 : -1;
            // ���������� ����������� �������� �� y
            int sy = (y1 < y2) ? 1 : -1;
            // ������������� ��������� ������
            int err = dx - dy;

            // ��������� ���� ��� ��������� ����� �� ��������� ����������
            while (true) {
                // ������ ������� ������� � ������ ������������
                SetPixel(x1, y1, color);
                // ���������, �������� �� �������� �����
                if (x1 == x2 && y1 == y2) break;

                int e2 = 2 * err; // ��������� ������ ��� �������� �������

                // ���� ������ ��������� ������������� �� x
                if (e2 > -dy) {
                    err -= dy; // ��������� ������ �� dy
                    x1 += sx;  // ������������ �� x
                }

                // ���� ������ ��������� ������������� �� y
                if (e2 < dx) {
                    err += dx; // ����������� ������ �� dx
                    y1 += sy;  // ������������ �� y
                }
            }
        }
    }

    ~Frame(void)
    {
        delete[] pixels;
    }
};

#endif // FRAME_H
