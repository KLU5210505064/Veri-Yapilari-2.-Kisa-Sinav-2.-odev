#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Veri yap�s� i�in kullan�lan struct
typedef struct {
    double x;
    double y;
} Point;

// K�melerin merkezini temsil eden struct
typedef struct {
    double cx;
    double cy;
    int count;
} ClusterCenter;

// Veri noktalar�n�n k�melere atanmas�n� sa�layan fonksiyon
void assignToClusters(Point* points, int numPoints, ClusterCenter* centers, int numCenters) {
    int i, j;
    double minDist, dist;
    int assignedCluster;

    for (i = 0; i < numPoints; i++) {
        minDist = INFINITY;
        assignedCluster = 0;

        for (j = 0; j < numCenters; j++) {
            dist = sqrt(pow(points[i].x - centers[j].cx, 2) + pow(points[i].y - centers[j].cy, 2));

            if (dist < minDist) {
                minDist = dist;
                assignedCluster = j;
            }
        }

        centers[assignedCluster].cx = (centers[assignedCluster].cx * centers[assignedCluster].count + points[i].x) / (centers[assignedCluster].count + 1);
        centers[assignedCluster].cy = (centers[assignedCluster].cy * centers[assignedCluster].count + points[i].y) / (centers[assignedCluster].count + 1);
        centers[assignedCluster].count++;
    }
}

// K�melerin merkezlerini g�ncelleyen fonksiyon
void updateCenters(ClusterCenter* centers, int numCenters) {
    int i;

    for (i = 0; i < numCenters; i++) {
        centers[i].cx = centers[i].cy = centers[i].count = 0;
    }
}

// �rnek veri noktalar�n� ve ba�lang�� merkezlerini olu�turan fonksiyon
void generateSampleData(Point* points, int numPoints, ClusterCenter* centers, int numCenters) {
    int i;

    // Rastgele veri noktalar� olu�tur
    for (i = 0; i < numPoints; i++) {
        points[i].x = (double)rand() / RAND_MAX * 100.0;
        points[i].y = (double)rand() / RAND_MAX * 100.0;
    }

    // Ba�lang�� merkezlerini belirle
    for (i = 0; i < numCenters; i++) {
        centers[i].cx = points[i].x;
        centers[i].cy = points[i].y;
        centers[i].count = 0;
    }
}

// K�meleme sonu�lar�n� ekrana yazd�ran fonksiyon
void printClusters(ClusterCenter* centers, int numCenters) {
    int i;

    for (i = 0; i < numCenters; i++) {
        printf("Cluster %d: Center = (%.2f, %.2f), Count = %d\n", i + 1, centers[i].cx, centers[i].cy, centers[i].count);
    }
}

int main() {
    int numPoints = 100;  // Veri noktalar�n�n say�s�
    int numCenters = 3;   // Ba�lang�� merkezlerinin say�s�

    Point* points = (Point*)malloc(numPoints * sizeof(Point));
    ClusterCenter* centers = (ClusterCenter*)malloc(numCenters * sizeof(ClusterCenter));

    generateSampleData(points, numPoints, centers, numCenters);

    int maxIterations = 10;  // Maksimum iterasyon say�s�
    int iteration;

    for (iteration = 0; iteration < maxIterations; iteration++) {
        assignToClusters(points, numPoints, centers, numCenters);
        updateCenters(centers, numCenters);
    }

    printClusters(centers, numCenters);

    free(points);
    free(centers);

    return 0;
}

