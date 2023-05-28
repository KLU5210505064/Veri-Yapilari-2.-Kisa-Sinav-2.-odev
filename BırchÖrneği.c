#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Veri yapýsý için kullanýlan struct
typedef struct {
    double* features;  // Özellik vektörü
    int clusterID;     // Küme kimliði
} DataPoint;

// Veri noktalarýnýn öklidyen mesafesini hesaplayan fonksiyon
double calculateDistance(DataPoint* point1, DataPoint* point2, int numFeatures) {
    double distance = 0.0;
    for (int i = 0; i < numFeatures; i++) {
        distance += pow(point1->features[i] - point2->features[i], 2);
    }
    return sqrt(distance);
}

// BIRCH algoritmasý uygulayan fonksiyon
void birchAlgorithm(DataPoint* data, int numPoints, int numFeatures, int threshold, double radius) {
    // Birinci aþama: Veri noktalarýný çekirdek aðaçlarýna ekleyin veya yeni bir çekirdek aðacý oluþturun
    int numClusters = 0;
    DataPoint* clusters = (DataPoint*)malloc(numPoints * sizeof(DataPoint));

    for (int i = 0; i < numPoints; i++) {
        int j;
        for (j = 0; j < numClusters; j++) {
            double distance = calculateDistance(&data[i], &clusters[j], numFeatures);
            if (distance < radius) {
                break;
            }
        }

        if (j == numClusters) {
            // Yeni bir çekirdek aðacý oluþtur
            clusters[numClusters] = data[i];
            clusters[numClusters].clusterID = numClusters;
            numClusters++;
        }
    }

    // Ýkinci aþama: Veri noktalarýný çekirdek aðaçlarýna ekleyin veya mevcut çekirdek aðaçlarýna birleþtirin
    int* clusterIDs = (int*)malloc(numPoints * sizeof(int));
    int* clusterCounts = (int*)calloc(numClusters, sizeof(int));

    for (int i = 0; i < numPoints; i++) {
        int closestCluster = -1;
        double minDistance = INFINITY;

        for (int j = 0; j < numClusters; j++) {
            double distance = calculateDistance(&data[i], &clusters[j], numFeatures);
            if (distance < minDistance) {
                minDistance = distance;
                closestCluster = j;
            }
        }

        if (minDistance < radius) {
            // Mevcut bir çekirdek aðacýna en yakýn olaný ekle
            clusterIDs[i] = closestCluster;
            clusterCounts[closestCluster]++;
        } else {
            // En yakýn çekirdek aðacý yok, yeni bir çekirdek aðacý oluþtur
            clusters[numClusters] = data[i];
            clusters[numClusters].clusterID = numClusters;
            clusterIDs[i] = numClusters;
            clusterCounts[numClusters]++;
            numClusters++;
        }
    }

    // Kümeleme sonuçlarýný ekrana yazdýr
    for (int i = 0; i < numClusters; i++) {
        printf("Cluster %d: Count = %d\n", i + 1, clusterCounts[i]);
    }

    free(clusters);
    free(clusterIDs);
    free(clusterCounts);
}

int main() {
    int numPoints = 10;     // Veri noktalarýnýn sayýsý
    int numFeatures = 2;    // Veri noktalarýnýn özellik sayýsý
    int threshold = 2;      // Çekirdek aðaç eþiði
    double radius = 2.0;    // Çekirdek aðaç yarýçapý

    DataPoint* data = (DataPoint*)malloc(numPoints * sizeof(DataPoint));

    // Örnek veri noktalarýný oluþtur
    for (int i = 0; i < numPoints; i++) {
        data[i].features = (double*)malloc(numFeatures * sizeof(double));
        for (int j = 0; j < numFeatures; j++) {
            data[i].features[j] = (double)rand() / RAND_MAX * 10.0;
        }
    }

    birchAlgorithm(data, numPoints, numFeatures, threshold, radius);

    // Bellek temizleme
    for (int i = 0; i < numPoints; i++) {
        free(data[i].features);
    }
    free(data);

    return 0;
}

