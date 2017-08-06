#! /usr/bin/env python
# -*- coding: utf-8 -*-

import socket
import sys


address1 = '192.168.10.103'
address2 = '127.0.0.1'
address3 = 'localhost'

sock = socket.socket()
sock.connect((address2, 3700))
sock.send("Zakeria\0")

data = sock.recv(256)
#x = bytearray(256)
#nbytes, ancdata, msg_flags, address = sock.recvfrom_into(x,256,0)
#tu = sock.recvfrom_into(x,256)
sock.close()
bata = data[:16]
print bata

