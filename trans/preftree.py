#!/usr/bin/env python

import os

def exe(word,init):
    exestr = "~/KRPR/trans/preftree"
    exestr += ' ' + word + ' ' + init
    os.system(exestr)

fpar = "Zak"
spar = "Zakeria"

exe(fpar, spar)

#x = r"~/KRPR/trans/preftree dolly doll"

