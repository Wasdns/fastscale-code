#!/usr/bin/env python

import time

from mininet.topo import SingleSwitchTopo
from mininet.net import Mininet
from mininet.cli import CLI

net = Mininet(SingleSwitchTopo(2))
net.start()
time1 = time.time()
s3 = net.addSwitch('s3', protocols='OpenFlow13', listenPort=6673, mac='00:00:00:00:00:03')
#s4 = net.addSwitch('s4', protocols='OpenFlow13', listenPort=6674, mac='00:00:00:00:00:04')
time2 = time.time()
net.stop()
print 'Create a switch: %0.6f ms' % ((time2-time1)*1000.0)
