#!/usr/bin/env python

import time
import argparse
from fastscale import fastscale

def get_parser():
    parser = argparse.ArgumentParser(description='FastScale benchmark')
    parser.add_argument('-n', "--num", help="Number",
                        type=int, action="store", default=0)
    parser.add_argument('-m', "--mode", help="Mode, mode=0: nodes; mode=1: branches",
                        type=int, action="store", default=0)
    parser.add_argument('-l', "--loop", help="Loop",
                        type=int, action="store", default=1)
    return parser

def main():
    args = get_parser().parse_args()
    if args.mode == 0:
        res = []
        for i in range(args.loop):
            root_rate = 100
            edges, capacities = [], []
            for i in range(args.num):
                from_, to = i+1, i+2
                if from_ > args.num: break
                weight = 5
                edge = [from_, to, weight]
                if to <= args.num: edges.append(edge)
                capacities.append([from_, weight])
            time1 = time.time()
            fastscale(root_rate=root_rate, edges=edges, capacities=capacities)
            time2 = time.time()
            print '%d NFs: %0.6f ms' % (args.num, (time2-time1)*1000.0)
            res.append((time2-time1)*1000.0)
        print 'Result: \n', res
    else:
        res = []
        for i in range(args.loop):
            root_rate = 1000
            edges, capacities = [], []
            from_ = 1
            capacities.append([from_, 100])
            for i in range(args.num):
                to = from_+i+1
                weight = 100/args.num*1.0
                edge = [from_, to, weight]
                edges.append(edge)
                capacities.append([to, 5])
            time1 = time.time()
            fastscale(root_rate=root_rate, edges=edges, capacities=capacities)
            time2 = time.time()
            print '%d branches: %0.6f ms' % (args.num, (time2-time1)*1000.0)
            res.append((time2-time1)*1000.0)
        print 'Result: \n', res

if __name__ == '__main__':
    main()
