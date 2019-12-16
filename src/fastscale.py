#!/usr/bin/env python

import math
import argparse
import networkx as nx

"""Input: root_rate - input rate of the whole SFC;
          root - root NF;
          edges - a list of directed edges with weights [[id1, id2, weight], ...];
          capacities - a list of node capacities [[NF_id, capacity], ...]
   Output: scale-out plan consisting of several lists, each of which specifies [NF_id, num_to_scale]
"""
def fastscale(root_rate, edges, capacities):
    # create Networkx directed graph
    DG = nx.DiGraph()
    for edge in edges:
        from_, to, weight = int(edge[0]), int(edge[1]), int(edge[2])
        DG.add_edge(from_, to, weight=weight)

    # create a dict for capacities
    capacity_dict = {}
    for item in capacities:
        key, val = item[0], item[1]
        capacity_dict[key] = val

    # start from root (0), iterate through every NF
    current = 1
    in_rate = 0
    scale_out_plan = {} # key: id, value: num
    for i in range(DG.number_of_nodes()):
        # calculate input rate
        predecessors = list(DG.predecessors(current))
        if len(predecessors) == 0: 
            in_rate = root_rate
        else: 
            for predecessor in predecessors:
                rate_pre2current = DG[predecessor][current]['weight']
                in_rate = in_rate+rate_pre2current

        # calculate scale-out plan
        current_capacity = capacity_dict[current]
        num = math.ceil(in_rate*1.0/current_capacity*1.0)
        scale_out_plan[current] = num

        # update output edge capacity
        new_out_rate = in_rate
        old_out_rate = 0
        successors = list(DG.successors(current))
        print successors
        if len(successors) != 0:
            # calculate old_out_rate
            for successor in successors:
                rate_current2succ = DG[current][successor]['weight']
                old_out_rate = old_out_rate+rate_current2succ
            # update output edge weight
            for successor in successors:
                rate_current2succ = DG[current][successor]['weight']
                proportion = rate_current2succ*1.0/old_out_rate*1.0
                new_rate_current2succ = new_out_rate*proportion
                DG[current][successor]['weight'] = new_rate_current2succ

        # find next
        in_rate = 0
        current = current+1

    return scale_out_plan

def test():
    # example1: ===100===>1(50)===50===>2(50)===50===>3(50)===50===>
    root_rate = 100
    edges = [[1,2,50],[2,3,50]]
    capacities = [[1,50],[2,50],[3,50]]
    print fastscale(root_rate=root_rate, edges=edges, capacities=capacities)
    # example2: ===100===>1(50)===30===>2(30)===30===>4(50)===40===>
    #                     1(50)===20===>3(10)===10===>4(50)
    root_rate = 100
    edges = [[1,2,30],[1,3,20],[2,4,30],[3,4,20]]
    capacities = [[1,50],[2,30],[3,10],[4,50]]
    print fastscale(root_rate=root_rate, edges=edges, capacities=capacities)

if __name__ == '__main__':
    test()


