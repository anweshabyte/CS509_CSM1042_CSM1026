## Assignment 04 - FastMap (Buddy Task)

## Student Details
- **Name:** Anwesha Roy Oishi
- **Entry No:** 2026CSM1042


### Objective:
Implement the FastMap algorithm that maps N objects described only by a pairwise distance function into a k-dimensional Euclidean space, so that Euclidean distances in the new space approximate the original distances.

### Input Format :
```
N K
d(0,0) d(0,1) ... d(0,N-1)
d(1,0) d(1,1) ... d(1,N-1)
...
d(N-1,0) d(N-1,1) ... d(N-1,N-1)

- N: number of objects
- K: target embedding dimensionality (2 or 3)
- Distance matrix is symmetric with zero diagonal
- Distances are non-negative floating-point values
```
### Directory Structure :
```
FastMap/
├── driver/
│ └── main.cpp
├── src/
│ ├── fastmap.h
│ └── fastmap.cpp
├── tests/
│ ├── fm_01.txt
│ ├── fm_02.txt
│ └── fm_03.txt
├── outputs/
│ ├── output_fm01.txt
│ ├── output_fm02.txt
│ └── output_fm03.txt
├── generate_tests.cpp
└── README.md
```

### File Structure: 
| File | Description |
|------|-------------|
| `driver/main.cpp` | Reads input, validates, times algorithm, prints output |
| `src/fastmap.h` | Header file with FastMapResult struct |
| `src/fastmap.cpp` | Core FastMap algorithm implementation |
| `tests/fm_01.txt` | N=10, k=2 - small, hand-verifiable |
| `tests/fm_02.txt` | N=100, k=2 - moderate size |
| `tests/fm_03.txt` | N=1000, k=3 - larger object set |
| `generate_tests.cpp` | C++ generator for fm_02 and fm_03 |

### Compilation:
```bash
# Generate test files
g++ -O2 -std=c++17 -o generate_tests generate_tests.cpp
./generate_tests

# Compile FastMap
g++ -O2 -std=c++17 -o fastmap driver/main.cpp src/fastmap.cpp
```

### Execution:
```bash
./fastmap tests/fm_01.txt
./fastmap tests/fm_02.txt
./fastmap tests/fm_03.txt
```

### Test Cases and Result Table

| File | N | Target K | Pivots (per dim) | Avg. Distance Error | Time | Status |
|------|---|----------|-----------------|---------------------|------|--------|
| fm_01.txt | 10 | 2 | Dim1: 9 0, Dim2: 4 5 | 0.947343 | 0.000 ms | Pass |
| fm_02.txt | 100 | 2 | Dim1: 0 5, Dim2: 56 57 | 0.000039 | 0.000 ms | Pass |
| fm_03.txt | 1000 | 3 | Dim1: 232 347, Dim2: 780 3, Dim3: 452 489 | 0.000041 | 2.014 ms | Pass |

### Complexity: 

| Step | Time Complexity | Space Complexity |
|------|----------------|-----------------|
| Pivot Selection | O(N) per dimension | O(1) |
| Projection | O(N) per dimension | O(N×k) |
| Deflation | O(k) per pair | O(1) |
| **Total** | **O(k × N)** | **O(N²)** |

