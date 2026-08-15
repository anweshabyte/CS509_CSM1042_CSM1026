# Gradient Descent

## System Configuration

- **Algorithm:** Gradient Descent
- **Input Type:** Polynomial Coefficients + Scalar Parameters 
- **Language:** C++
- **Compiler:** g++ (C++17)

---

## Folder Layout

```
Assignment_03/
└── Gradient_Descent/
    ├── include/gradient_descent.h
    ├── src/gradient_descent.cpp
    ├── src/main.cpp
    ├── tests/gd_01.txt ... gd_05.txt
    └── outputs/gd_01_output.txt ... gd_05.txt
```

---

## Run Command

**Linux / macOS:**
```bash
cd Assignment_03/Gradient_Descent
g++ -std=c++17 -O2 -Wall -Iinclude src/gradient_descent.cpp src/main.cpp -o gradient_descent
./gradient_descent tests/gd_01.txt 5000
```

**Windows PowerShell:**
```powershell
cd Assignment_03\Gradient_Descent
g++ -std=c++17 -O2 -Wall -Iinclude src/gradient_descent.cpp src/main.cpp -o gradient_descent
.\gradient_descent.exe tests\gd_01.txt 5000
```

---

## Results

| File | Degree | x₀ | Rate | Tol. | Max Iter. | Exp. x\* | Exp. f(x\*) | Actual x | Actual f(x) | Iter. / Time | Status |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---|:---:|
| gd_01.txt | 2 | 0 | 0.10  | 1e-6 | 5,000   | 3 | 0 | 3.0000 | 0.0000 | 70 / 0.000408 ms   | Pass |
| gd_02.txt | 4 | 2 | 0.02  | 1e-6  | 10,000  | 0 | 0 | 0.0000| 0.0000 | 180 / 0.002460 ms  | Pass |
| gd_03.txt | 6  | 2 | 0.02  | 1e-6  | 20,000  | 0 | 0 | 0.0000 | 0.0000 | 349 / 0.006453 ms  | Pass |
| gd_04.txt | 8  | 2 | 0.01  | 1e-8  | 50,000  | 0 | 0 | 0.0000 | 0.0000 | 948 / 0.019484 ms  | Pass |
| gd_05.txt | 10 | 2 | 0.005 | 1e-10 | 100,000 | 0 | 0 | 0.0000 | 0.0000 | 2364 / 0.075969 ms | Pass |


---

## Complexity

 **Time Complexity:** O(d · k) -- d = Polynomial Degree, k = Iterations to Convergence    
 **Space Complexity:** O(d) -- Stores d+1 coefficients; O(1) Extra Scalar variables

### Observed Scaling
| Degree | Iterations | Time (avg 5000 runs) |
|---:|---:|---:|
| 2  | 70    | 0.000408 ms |
| 4  | 180   | 0.002460 ms |
| 6  | 349   | 0.006453 ms |
| 8  | 948   | 0.019484 ms |
| 10 | 2364  | 0.075969 ms |

