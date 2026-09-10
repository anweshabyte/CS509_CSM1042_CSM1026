# CS509 Assignment 4 - Buddy Project(CSM1026)

## Selected Task
This buddy package implements **K-Means Clustering only**, as requested.

The Assignment 4 specification lists K-Means and FastMap as buddy tasks. This package contains the K-Means task only.

## Directory Structure
```text
CS509_Assignment4_Buddy_KMeans/
├── README.md
├── common_wrapper/
│   └── wrapper.cpp
├── assignment_04/
│   ├── src/
│   │   ├── kmeans.h
│   │   └── kmeans.cpp
│   ├── driver/
│   │   └── kmeans_driver.cpp
│   └── tests/
│       ├── km_01.txt
│       ├── km_02.txt
│       ├── km_03.txt
│       └── km_04.txt
└── outputs/
```

## Compilation
```powershell
g++ -std=c++17 -O2 -Wall -Wextra assignment_04/src/kmeans.cpp assignment_04/driver/kmeans_driver.cpp -o kmeans.exe
```

## Execution
```powershell
.\kmeans.exe assignment_04\tests\km_01.txt
```

## Algorithm
The first K input points are used as initial centroids. Each iteration performs:
1. Assignment of every point to the nearest centroid using squared Euclidean distance.
2. Recalculation of each centroid as the mean of its assigned points.
3. Convergence checking using maximum centroid shift.

Empty clusters retain their previous centroid for that iteration.

The timed region contains only the K-Means algorithm; input reading and output are outside it.

## Required Tests
- km_01: N=100, D=2, K=3
- km_02: N=1,000, D=2, K=5
- km_03: N=10,000, D=5, K=8
- km_04: N=100,000, D=5, K=10

