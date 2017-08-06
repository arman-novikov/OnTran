#!/usr/bin/env python
# -*- coding: utf-8 -*-

def exe(word,init):
    exestr = "~/KRPR/trans/preftree"
    exestr += ' ' + word + ' ' + init
    os.system(exestr)
    return


def wordadd(dict, word, trans, pos, descr):
    filetoken = r"/home/arman/KRPR/OnTran/" + dict + r"/"
    filetoken +=   word[0].upper() + r".txt"

    fileFORadd = open(filetoken, "a")

    tempstr = ("=\n"+ "%" + word + "%\n"
        + "*" + trans + "*\n" + "^" + str(pos) + "^\n"
        + "+" + descr + "+\n\n")

    fileFORadd.write(tempstr)
    fileFORadd.close()
    exe(word , word)
    return

mydict = "En-Ru"
myword = "winter"
mytrans = "зима"
mypos = 1
mydescr = "winter is a cold season of year"

wordadd(mydict, myword, mytrans, mypos, mydescr)



