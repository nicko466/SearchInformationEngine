#!/usr/bin/env python
# -*- coding: utf-8 -*- 

def clearFile (path, export):
    file = open(path,"r")
    res= ""
    for line in file:
        newLine = line.replace("é","e")
        newLine = newLine.replace("ê","e")
        newLine = newLine.replace("è","e")
        newLine = newLine.replace("ç","c")
        newLine = newLine.replace("à","a")
        newLine = newLine.replace("â","a")
        newLine = newLine.replace("ô","o")
        newLine = newLine.replace("û","u")
        res += newLine
    file = open(export,"w")
    file.write(res)

def clearCorpus ():
    clearFile("corpus/french.txt","corpus/frenchClear.txt")
    clearFile("corpus/dutch.txt","corpus/dutchClear.txt")
    clearFile("corpus/italian.txt","corpus/italianClear.txt")
    clearFile("corpus/english.txt","corpus/englishClear.txt")
    
clearCorpus()