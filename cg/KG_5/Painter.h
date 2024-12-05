// Painter.h
#ifndef PAINTER_H
#define PAINTER_H

#include <vector>
#include <algorithm>
#include <cmath>
#include "Frame.h"
#include "Vector.h"
#include "Matrix.h"

// ����� �� ������ ������� ���������
float time = 0;

// ��� ��������
enum ProjectionType {
    CENTRAL,        // ����������� ��������
    ORTHOGRAPHIC    // ��������������� ��������
};
ProjectionType currentProjection = CENTRAL;

// ��������� ��� �������� ��������
struct Polygon {
    std::vector<Vector> vertices; // ������� ��������������
    COLOR color;                  // ���� ��������������
};

// ���������� ������������ ��� ��������� �����
unsigned char globalAlpha = 255; // ���������� ������������

// ������������ ��� �������
unsigned char shaderAlpha = 128; // ������������ ������� (��������������)

// ����� ��� ������������ �������� � ��������� ������
class QuadShader {
    // ���������� ������ � �������� ������� ���������
    Vector v0, v1, v2, v3;
    // ���������� ������ � ������� ������� ���������
    Vector wv0, wv1, wv2, wv3;

    // ��������������� ������� ����� ��� ���������� ������� �����
    float edge0_dx, edge0_dy;
    float edge1_dx, edge1_dy;
    float edge2_dx, edge2_dy;
    float edge3_dx, edge3_dy;

    // ����������� � ������������ ���������� ��� ������� ������������
    int minX, maxX, minY, maxY;

public:
    QuadShader(const std::vector<Vector>& screenVerts, const std::vector<Vector>& worldVerts) {
        // �����������, ����������� ������� �������� � �������� � ������� ������� ���������
        v0 = screenVerts[0];
        v1 = screenVerts[1];
        v2 = screenVerts[2];
        v3 = screenVerts[3];

        wv0 = worldVerts[0];
        wv1 = worldVerts[1];
        wv2 = worldVerts[2];
        wv3 = worldVerts[3];

        // ��������� ������� ����� ��������
        edge0_dx = v1.x - v0.x;
        edge0_dy = v1.y - v0.y;
        edge1_dx = v2.x - v1.x;
        edge1_dy = v2.y - v1.y;
        edge2_dx = v3.x - v2.x;
        edge2_dy = v3.y - v2.y;
        edge3_dx = v0.x - v3.x;
        edge3_dy = v0.y - v3.y;

        // ���������� ������� ������� ������������ ��������
        minX = (int)std::floor(std::fmin(std::fmin(v0.x, v1.x), std::fmin(v2.x, v3.x)));
        maxX = (int)std::ceil(std::fmax(std::fmax(v0.x, v1.x), std::fmax(v2.x, v3.x)));
        minY = (int)std::floor(std::fmin(std::fmin(v0.y, v1.y), std::fmin(v2.y, v3.y)));
        maxY = (int)std::ceil(std::fmax(std::fmax(v0.y, v1.y), std::fmax(v2.y, v3.y)));
    }

    // ������� ��� �������� ���������� ����� � ����������� ��������
    COLOR main(float u, float v) {
        int checkSize = 10;

        int iu = (int)(u * checkSize);
        int iv = (int)(v * checkSize);

        if ((iu + iv) % 2 == 0)
            return COLOR(200, 200, 200, shaderAlpha); // ���������� shaderAlpha
        else
            return COLOR(20, 20, 0, shaderAlpha);     // ���������� shaderAlpha
    }

    // ��������, ��������� �� ����� ������ ��������, ��������� ������� �����
    bool isInside(int x, int y) {
        float fx = (float)x + 0.5f; // ����� ������� �� x
        float fy = (float)y + 0.5f; // ����� ������� �� y

        // ��������� �������� ������� �����
        float edge0 = (fx - v0.x) * edge0_dy - (fy - v0.y) * edge0_dx;
        float edge1 = (fx - v1.x) * edge1_dy - (fy - v1.y) * edge1_dx;
        float edge2 = (fx - v2.x) * edge2_dy - (fy - v2.y) * edge2_dx;
        float edge3 = (fx - v3.x) * edge3_dy - (fy - v3.y) * edge3_dx;

        // ��������� �������������� ������� ���� ������
        return (edge0 <= 0 && edge1 <= 0 && edge2 <= 0 && edge3 <= 0);
    }

    // ������������ ��������� �������� ��� ����� (x, y)
    void interpolateTextureCoordinates(int x, int y, float& u, float& v) {
        // ���������� ������� ������������ ���������� ���������
        float denom = (v1.x - v0.x) * (v3.y - v0.y) - (v3.x - v0.x) * (v1.y - v0.y);

        float fx = (float)x + 0.5f;
        float fy = (float)y + 0.5f;

        u = ((fx - v0.x) * (v3.y - v0.y) - (v3.x - v0.x) * (fy - v0.y)) / denom;
        v = ((v1.x - v0.x) * (fy - v0.y) - (fx - v0.x) * (v1.y - v0.y)) / denom;
    }

    // �������� ������� ��� ��������� ����� �������
    COLOR color(int x, int y) {
        if (isInside(x, y)) {
            // ���� ����� ������ ��������, ��������� ���������� ����������
            float u, v;
            interpolateTextureCoordinates(x, y, u, v);
            return main(u, v); // ���������� ���� ���������� �����
        }
        else {
            return COLOR(0, 0, 0, 0); // ���������� ���� ��� ����� ��� ��������
        }
    }

    // ���������� ������� ������� ������������ ��������
    void getBounds(int& outMinX, int& outMaxX, int& outMinY, int& outMaxY) {
        outMinX = minX; // ����������� X
        outMaxX = maxX; // ������������ X
        outMinY = minY; // ����������� Y
        outMaxY = maxY; // ������������ Y
    }
};

class Painter {
private:
    // ������� ��� ��������� ����� �����
    void GenerateLeg(std::vector<struct Polygon>& polygons, float x, float y, float z, float legWidth, COLOR color) {
        // ��������� �������� ��� ���� ������ �����
        polygons.push_back({ {Vector(x, y, z), Vector(x + legWidth, y, z), Vector(x + legWidth, y + legWidth, z), Vector(x, y + legWidth, z)}, color }); // ������� �����
        polygons.push_back({ {Vector(x, y, z - 3), Vector(x + legWidth, y, z - 3), Vector(x + legWidth, y + legWidth, z - 3), Vector(x, y + legWidth, z - 3)}, color }); // ������ �����
        polygons.push_back({ {Vector(x, y, z), Vector(x, y + legWidth, z), Vector(x, y + legWidth, z - 3), Vector(x, y, z - 3)}, color }); // ������� ����� 1
        polygons.push_back({ {Vector(x + legWidth, y, z), Vector(x + legWidth, y + legWidth, z), Vector(x + legWidth, y + legWidth, z - 3), Vector(x + legWidth, y, z - 3)}, color }); // ������� ����� 2
        polygons.push_back({ {Vector(x, y, z), Vector(x + legWidth, y, z), Vector(x + legWidth, y, z - 3), Vector(x, y, z - 3)}, color }); // �������� �����
        polygons.push_back({ {Vector(x, y + legWidth, z), Vector(x + legWidth, y + legWidth, z), Vector(x + legWidth, y + legWidth, z - 3), Vector(x, y + legWidth, z - 3)}, color }); // ������ �����
    }

    // ������� ��� ��������� ����������
    void GenerateTabletop(std::vector<struct Polygon>& polygons, float height, COLOR color) {
        // ��������� �������� ��� ���� ������ ����������
        polygons.push_back({ {Vector(-1, -1, 0), Vector(1, -1, 0), Vector(1, 1, 0), Vector(-1, 1, 0)}, color }); // ������ �����
        polygons.push_back({ {Vector(-1, -1, height), Vector(1, -1, height), Vector(1, 1, height), Vector(-1, 1, height)}, color }); // ������� �����
        polygons.push_back({ {Vector(-1, -1, 0), Vector(-1, 1, 0), Vector(-1, 1, height), Vector(-1, -1, height)}, color }); // ������� ����� 1
        polygons.push_back({ {Vector(1, -1, 0), Vector(1, 1, 0), Vector(1, 1, height), Vector(1, -1, height)}, color }); // ������� ����� 2
        polygons.push_back({ {Vector(-1, 1, 0), Vector(1, 1, 0), Vector(1, 1, height), Vector(-1, 1, height)}, color }); // �������� �����
        polygons.push_back({ {Vector(-1, -1, 0), Vector(1, -1, 0), Vector(1, -1, height), Vector(-1, -1, height)}, color }); // ������ �����
    }

    // ������� ��� ��������� ����������� ����� ������� �����
    void GenerateCrossbar(std::vector<struct Polygon>& polygons, float z, float legWidth, COLOR color) {
        // ��������� �������� ��� ���� ������ �����������
        polygons.push_back({ {Vector(-1, -1, z), Vector(-1 + legWidth, -1, z), Vector(-1 + legWidth, 1, z), Vector(-1, 1, z)}, color }); // ������ �����
        polygons.push_back({ {Vector(-1, -1, z + legWidth), Vector(-1 + legWidth, -1, z + legWidth), Vector(-1 + legWidth, 1, z + legWidth), Vector(-1, 1, z + legWidth)}, color }); // ������� �����
        polygons.push_back({ {Vector(-1, -1, z), Vector(-1, 1, z), Vector(-1, 1, z + legWidth), Vector(-1, -1, z + legWidth)}, color }); // ������� ����� 1
        polygons.push_back({ {Vector(-1 + legWidth, -1, z), Vector(-1 + legWidth, 1, z), Vector(-1 + legWidth, 1, z + legWidth), Vector(-1 + legWidth, -1, z + legWidth)}, color }); // ������� ����� 2
    }

    // ������� ��� ��������� ���� � ������� ������� ��� ������ �����
    void GenerateCube(std::vector<struct Polygon>& polygons, float size) {
        // ���������� �������� ������� ����
        float halfSize = size / 2.0f;

        // ���������� ������ ����� ��� ������ ����� ����
        COLOR frontColor(255, 0, 0, 128);     // �������� ����� - �������
        COLOR backColor(0, 255, 0, 128);      // ������ ����� - �������
        COLOR leftColor(0, 0, 255, 128);      // ����� ����� - �����
        COLOR rightColor(255, 255, 0, 128);   // ������ ����� - ������
        COLOR topColor(0, 255, 255, 128);     // ������� ����� - �������
        COLOR bottomColor(255, 0, 255, 128);  // ������ ����� - ���������

        // ����� ����
        polygons.push_back({ {Vector(-halfSize, -halfSize, -halfSize), Vector(halfSize, -halfSize, -halfSize), Vector(halfSize, halfSize, -halfSize), Vector(-halfSize, halfSize, -halfSize)}, bottomColor }); // ������ �����
        polygons.push_back({ {Vector(-halfSize, -halfSize, halfSize), Vector(halfSize, -halfSize, halfSize), Vector(halfSize, halfSize, halfSize), Vector(-halfSize, halfSize, halfSize)}, topColor }); // ������� �����
        polygons.push_back({ {Vector(-halfSize, -halfSize, -halfSize), Vector(-halfSize, halfSize, -halfSize), Vector(-halfSize, halfSize, halfSize), Vector(-halfSize, -halfSize, halfSize)}, leftColor }); // ����� �����
        polygons.push_back({ {Vector(halfSize, -halfSize, -halfSize), Vector(halfSize, halfSize, -halfSize), Vector(halfSize, halfSize, halfSize), Vector(halfSize, -halfSize, halfSize)}, rightColor }); // ������ �����
        polygons.push_back({ {Vector(-halfSize, halfSize, -halfSize), Vector(halfSize, halfSize, -halfSize), Vector(halfSize, halfSize, halfSize), Vector(-halfSize, halfSize, halfSize)}, frontColor }); // �������� �����
        polygons.push_back({ {Vector(-halfSize, -halfSize, -halfSize), Vector(halfSize, -halfSize, -halfSize), Vector(halfSize, -halfSize, halfSize), Vector(-halfSize, -halfSize, halfSize)}, backColor }); // ������ �����
    }

public:
    // ������� ��� ��������� ����� � ����
    void Draw(Frame& frame, float legWidth, float zoomScale, float rotationX, float rotationY) {
        // ������ ����
        float cubeSize = 7.0f; // ����������� ������ ����

        // �������� ������� ��������
        Matrix projection_matrix;

        switch (currentProjection) {
        case CENTRAL:
            // ����������� ��������
            projection_matrix = Matrix::Frustum(-0.5f * frame.width / frame.height, 0.5f * frame.width / frame.height, -0.5f, 0.5f, 1.0f, 20.0f);
            break;
        case ORTHOGRAPHIC:
            // ��������������� ��������
            projection_matrix = Matrix::Ortho(-4.0f * frame.width / frame.height, 4.0f * frame.width / frame.height, -4.0f, 4.0f, 4.0f, 400.0f);
            break;
        }

        // ����� ������� ��������������
        Matrix general_matrices =
            Matrix::Scale(zoomScale, zoomScale, zoomScale) * // ���������������
            Matrix::RotationX(rotationX) *                  // ������� ������ ��� X
            Matrix::RotationY(rotationY) *                  // ������� ������ ��� Y
            Matrix::Translation(0, 0, -8) *                 // ����������� �� ��� Z
            projection_matrix *                             // ��������
            Matrix::Viewport(frame.width / 4, frame.height / 4, frame.width / 2, frame.height / 2);

        Matrix current_matrix = general_matrices;
        std::vector<struct Polygon> polygons;

        // ��������� ������
        GenerateLeg(polygons, -1, -1, 0, legWidth, COLOR(230, 35, 35, globalAlpha)); // ����� �����
        GenerateLeg(polygons, 1 - legWidth, -1, 0, legWidth, COLOR(230, 35, 35, globalAlpha));
        GenerateLeg(polygons, -1, 1 - legWidth, 0, legWidth, COLOR(230, 35, 35, globalAlpha));
        GenerateLeg(polygons, 1 - legWidth, 1 - legWidth, 0, legWidth, COLOR(230, 35, 35, globalAlpha));
        GenerateTabletop(polygons, 0.2f, COLOR(255, 255, 255, globalAlpha));         // ����������
        GenerateCrossbar(polygons, -2.5f, legWidth, COLOR(0, 0, 255, globalAlpha));  // �����������

        // ��������� ����
        GenerateCube(polygons, cubeSize); // �������������� ��� � ������� ������� ������

        // �������� ��������� ��� ���������� ���������
        std::vector<std::pair<float, struct Polygon>> sortedPolygons;
        for (struct Polygon& poly : polygons) {
            // ���������� �������� �������� Z-����������
            float averageZ = 0.0f;
            for (const Vector& vertex : poly.vertices) {
                Vector transformedVertex = vertex * current_matrix;     // ������������������ �������
                averageZ += transformedVertex.z / transformedVertex.w;  // ��������� �����������
            }
            averageZ /= poly.vertices.size();                           // ������� �������� Z
            sortedPolygons.emplace_back(averageZ, poly);                // ��������� ������� � ������ � ������������� ������
        }

        // ��������� �������� �� �������� Z (�� ������� � �������)
        std::sort(sortedPolygons.begin(), sortedPolygons.end(),
                  [](const std::pair<float, struct Polygon>& a, const std::pair<float, struct Polygon>& b) {
            return a.first > b.first;
            });

        // ��������� ��������������� ���������
        for (const auto& sortedPair : sortedPolygons) {
            const struct Polygon& poly = sortedPair.second;

            // �������������� �������
            std::vector<Vector> transformed_vertices;
            for (const Vector& v : poly.vertices) {
                Vector tv = v * current_matrix; // ��������������
                tv.x /= tv.w; // ��������� ������������� �������
                tv.y /= tv.w;
                tv.z /= tv.w;
                transformed_vertices.push_back(tv);
            }

            // ��������, �������� �� ����� ������� �������� ����������
            bool isTabletopTopFace = false;
            if (poly.vertices.size() == 4 &&
                poly.vertices[0].z == 0.2f &&
                poly.vertices[1].z == 0.2f &&
                poly.vertices[2].z == 0.2f &&
                poly.vertices[3].z == 0.2f) {
                isTabletopTopFace = true;
            }

            // ��������, �������� �� ����� �������� ������ ����
            bool isCubeFrontFace = false;
            float halfSize = cubeSize / 2.0f; // �������� ������� ����
            const float epsilon = 1e-3f; // ���������� ����������� ��� ���������
            if (poly.vertices.size() == 4 &&
                std::abs(poly.vertices[0].z - halfSize) < epsilon &&
                std::abs(poly.vertices[1].z - halfSize) < epsilon &&
                std::abs(poly.vertices[2].z - halfSize) < epsilon &&
                std::abs(poly.vertices[3].z - halfSize) < epsilon) {
                isCubeFrontFace = true;
            }

            if (isTabletopTopFace) {
                // ������������ ������� ����� ���������� � ��������� ������
                QuadShader shader(transformed_vertices, poly.vertices);

                int minX, maxX, minY, maxY;
                shader.getBounds(minX, maxX, minY, maxY); // ������� ������������

                for (int y = minY; y <= maxY; y++) {
                    for (int x = minX; x <= maxX; x++) {
                        COLOR color = shader.color(x, y); // ���� �������
                        if (color.ALPHA > 0) {
                            frame.SetPixel(x, y, color); // ��������� �������
                        }
                    }
                }
            }
            else if (isCubeFrontFace) {
                // ������������ �������� ����� ���� � ��������� ������
                QuadShader shader(transformed_vertices, poly.vertices);

                int minX, maxX, minY, maxY;
                shader.getBounds(minX, maxX, minY, maxY); // ������� ������������

                for (int y = minY; y <= maxY; y++) {
                    for (int x = minX; x <= maxX; x++) {
                        COLOR color = shader.color(x, y); // ���� �������
                        if (color.ALPHA > 0) {
                            frame.SetPixel(x, y, color); // ��������� �������
                        }
                    }
                }
            }
            else {
                // ��������� ��������� ������
                frame.Quad(transformed_vertices[0].x, transformed_vertices[0].y, transformed_vertices[0].z,
                    transformed_vertices[1].x, transformed_vertices[1].y, transformed_vertices[1].z,
                    transformed_vertices[2].x, transformed_vertices[2].y, transformed_vertices[2].z,
                    transformed_vertices[3].x, transformed_vertices[3].y, transformed_vertices[3].z,
                    poly.color);
            }
        }
    }
};

#endif // PAINTER_H