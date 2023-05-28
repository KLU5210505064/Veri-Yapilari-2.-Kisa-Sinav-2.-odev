#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Veri yap�s� i�in kullan�lan struct
typedef struct {
    double* features;  // �zellik vekt�r�
    int clusterID;     // K�me kimli�i
} DataPoint;

// Veri noktalar�n�n �klidyen mesafesini hesaplayan fonksiyon
double calculateDistance(DataPoint* point1, DataPoint* point2, int numFeatures) {
    double distance = 0.0;
    for (int i = 0; i < numFeatures; i++) {
        distance += pow(point1->features[i] - point2->features[i], 2);
    }
    return sqrt(distance);
}

// BIRCH algoritmas� uygulayan fonksiyon
void birchAlgorithm(DataPoint* data, int numPoints, int numFeatures, int threshold, double radius) {
    // Birinci a�ama: Veri noktalar�n� �ekirdek a�a�lar�na ekleyin veya yeni bir �ekirdek a�ac� olu�turun
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
            // Yeni bir �ekirdek a�ac� olu�tur
            clusters[numClusters] = data[i];
            clusters[numClusters].clusterID = numClusters;
            numClusters++;
        }
    }

    // �kinci a�ama: Veri noktalar�n� �ekirdek a�a�lar�na ekleyin veya mevcut �ekirdek a�a�lar�na birle�tirin
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
            // Mevcut bir �ekirdek a�ac�na en yak�n olan� ekle
            clusterIDs[i] = closestCluster;
            clusterCounts[closestCluster]++;
        } else {
            // En yak�n �ekirdek a�ac� yok, yeni bir �ekirdek a�ac� olu�tur
            clusters[numClusters] = data[i];
            clusters[numClusters].clusterID = numClusters;
            clusterIDs[i] = numClusters;
            clusterCounts[numClusters]++;
            numClusters++;
        }
    }

    // K�meleme sonu�lar�n� ekrana yazd�r
    for (int i = 0; i < numClusters; i++) {
        printf("Cluster %d: Count = %d\n", i + 1, clusterCounts[i]);
    }

    free(clusters);
    free(clusterIDs);
    free(clusterCounts);
}

int main() {
    int numPoints = 10;     // Veri noktalar�n�n say�s�
    int numFeatures = 2;    // Veri noktalar�n�n �zellik say�s�
    int threshold = 2;      // �ekirdek a�a� e�i�i
    double radius = 2.0;    // �ekirdek a�a� yar��ap�

    DataPoint* data = (DataPoint*)malloc(numPoints * sizeof(DataPoint));

    // �rnek veri noktalar�n� olu�tur
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

