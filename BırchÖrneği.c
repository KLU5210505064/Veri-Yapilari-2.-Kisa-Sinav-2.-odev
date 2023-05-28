#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Veri yapýsý için kullanýlan struct
typedef struct {
    double x;
    double y;
} Point;

// Kümelerin merkezini temsil eden struct
typedef struct {
    double cx;
    double cy;
    int count;
} ClusterCenter;

// Veri noktalarýnýn kümelere atanmasýný saðlayan fonksiyon
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

// Kümelerin merkezlerini güncelleyen fonksiyon
void updateCenters(ClusterCenter* centers, int numCenters) {
    int i;

    for (i = 0; i < numCenters; i++) {
        centers[i].cx = centers[i].cy = centers[i].count = 0;
    }
}

// Örnek veri noktalarýný ve baþlangýç merkezlerini oluþturan fonksiyon
void generateSampleData(Point* points, int numPoints, ClusterCenter* centers, int numCenters) {
    int i;

    // Rastgele veri noktalarý oluþtur
    for (i = 0; i < numPoints; i++) {
        points[i].x = (double)rand() / RAND_MAX * 100.0;
        points[i].y = (double)rand() / RAND_MAX * 100.0;
    }

    // Baþlangýç merkezlerini belirle
    for (i = 0; i < numCenters; i++) {
        centers[i].cx = points[i].x;
        centers[i].cy = points[i].y;
        centers[i].count = 0;
    }
}

// Kümeleme sonuçlarýný ekrana yazdýran fonksiyon
void printClusters(ClusterCenter* centers, int numCenters) {
    int i;

    for (i = 0; i < numCenters; i++) {
        printf("Cluster %d: Center = (%.2f, %.2f), Count = %d\n", i + 1, centers[i].cx, centers[i].cy, centers[i].count);
    }
}

int main() {
    int numPoints = 100;  // Veri noktalarýnýn sayýsý
    int numCenters = 3;   // Baþlangýç merkezlerinin sayýsý

    Point* points = (Point*)malloc(numPoints * sizeof(Point));
    ClusterCenter* centers = (ClusterCenter*)malloc(numCenters * sizeof(ClusterCenter));

    generateSampleData(points, numPoints, centers, numCenters);

    int maxIterations = 10;  // Maksimum iterasyon sayýsý
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

