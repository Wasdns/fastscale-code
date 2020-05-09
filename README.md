# FastScale 

This repository contains the simulation scripts of FastScale algorithms. 
- mcmf: MCMF (Minimum-Cost Maximum Flow) - based FastScale algorithm;
- toposort: TopoSort (Topological Sorting) - based FastScale algorithm.

For more implementation details, please see our paper in INFOCOM WNA Workshop 2020:
```
Xiang Chen, Yuxin Chen, Qun Huang, Haifeng Zhou, Dong Zhang, Chunming Wu, Junchi Xing,
"FastScale: Fast Scaling Out of Network Functions", in IEEE INFOCOM WNA, 2020.
```

Author: Yuxin Chen, Xiang Chen

## MCMF

```
make
benchmark -l 1000 -M 5 -m 100
```

### Parameter

```
-l: loop
-M: how many layers are there
-m: how many nodes per layer
```

## Toposort

```
make
benchmark -m 0 -n 1001 -l 1000
```

### Parameter

```
-l: loop
-m: mode, 0 means nodes and 1 means branchs
-n: num of nodes or branchs
```