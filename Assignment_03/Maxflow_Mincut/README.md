# CS509 Buddy Assignment 3 — Maxflow-Mincut

## Assignment Mode

This project implements the **Maxflow-Mincut** buddy task from CS509 Assignment 3 using C++ and Dinic's algorithm.

## Language and Environment

- Language: C++
- Recommended standard: C++17
- Compiler: g++
- Build command:

```bash
g++ -std=c++17 -O2 -o maxflow_driver assignment_03/driver/maxflow_driver.cpp
```

The supplied driver contains the CSR helper and Dinic implementation.

## Objective

Given a directed graph with positive integer edge capacities, compute:

1. Maximum flow from source `s` to sink `t`.
2. A corresponding minimum `s-t` cut.
3. The minimum-cut capacity.
4. The source-side and sink-side vertex partitions.
5. The cut edges.
6. Algorithm execution time.

The expected invariant is:

**Maximum flow = Minimum cut capacity**

## Directory Structure

```text
CS509_Buddy_Maxflow_Mincut/
├── README.md
├── common_wrapper.cpp
└── assignment_03/
    ├── src/
    │   ├── csr_helper.h
    │   └── maxflow_mincut.cpp
    ├── driver/
    │   └── maxflow_driver.cpp
    ├── tests/
    │   ├── maxflow_10.txt
    │   ├── maxflow_100.txt
    │   ├── maxflow_1000.txt
    │   ├── maxflow_10000.txt
    │   └── maxflow_50000.txt
    └── outputs/
```

## Required Test Cases

| Test file | V | E | Source | Sink |
|---|---:|---:|---:|---:|
| maxflow_10.txt | 10 | 18 | 0 | 9 |
| maxflow_100.txt | 100 | 250 | 0 | 99 |
| maxflow_1000.txt | 1000 | 3000 | 0 | 999 |
| maxflow_10000.txt | 10000 | 30000 | 0 | 9999 |
| maxflow_50000.txt | 50000 | 150000 | 0 | 49999 |

The generated large graphs are sparse and contain a guaranteed source-to-sink path.

## Compilation

From the project root:

```bash
g++ -std=c++17 -O2 -o maxflow_driver assignment_03/driver/maxflow_driver.cpp
```

## Execution

```bash
./maxflow_driver assignment_03/tests/maxflow_10.txt
```

For Windows with MinGW:

```text
maxflow_driver.exe assignment_03/tests/maxflow_10.txt
```

## Common Wrapper

Compile:

```bash
g++ -std=c++17 -O2 -o wrapper common_wrapper.cpp
```

Run:

```bash
./wrapper maxflow assignment_03/tests/maxflow_10.txt
```

## Complexity

For Dinic's algorithm on general directed graphs, a standard worst-case bound is:

**O(V²E)**

For sparse practical networks, Dinic is generally much faster than the worst-case bound and is recommended by the assignment for the larger required inputs.

CSR storage uses:

**O(V + E)**

## Result Table

| Mode | Test File | Input Type | Input Size | Expected Flow | Actual Flow | Cut Capacity | Algorithm Time | Status |
|---|---|---|---|---:|---:|---:|---:|---|
| Double | maxflow_10.txt | Directed CSR | V=10, E=18 | 3 | 3 | 3 | 0.005318 ms | Pass |
| Double | maxflow_100.txt | Directed CSR | V=100, E=250 | 20 | 20 | 20 | 0.040099 ms | Pass |
| Double | maxflow_1000.txt | Directed CSR | V=1000, E=3000 | 14 | 14 | 14 | 0.370629 ms | Pass |
| Double | maxflow_10000.txt | Directed CSR | V=10000, E=30000 | 55 | 55 | 55 | 8.289732 ms | Pass |
| Double | maxflow_50000.txt | Directed CSR | V=50000, E=150000 | 31 | 31 | 31 | 27.319647 ms | Pass |

