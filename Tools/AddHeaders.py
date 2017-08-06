import os

#graphics should be first in the include order
EXEPTIONS = ["PrimeEngine.h", "DllExport.h", "File.h"]
PRIME_ENGINE_CORE_PATH = "..\\PrimeEngine\\PrimeEngine-Core"
OUTPUT_HEADER = "\\PrimeEngine.h"

def ParsePath(root, file):
    incPath = "#include <"
    head = os.path.split(root)[0]
    tail = os.path.split(root)[1]
    stack = []
    while tail != "PrimeEngine-Core":
        stack.append(tail + "\\")
        tail = os.path.split(head)[1]
        head = os.path.split(head)[0]
    stack.reverse()
    for element in stack:
        incPath += element
    incPath += file
    print(incPath)
    incPath += ">\n"
    return incPath

def GetAllHeaders():
    headerList = []
    for root, dirs, files in os.walk(PRIME_ENGINE_CORE_PATH):
        for file in files:
            if file.endswith(".h") and file not in EXEPTIONS:
                headerList.append(ParsePath(root, file))
    return headerList

def WriteHeader(outputFilePath, headers):
    file = open(outputFilePath, 'w')
    file.write("#pragma once \n")
    for header in headers:
        file.write(header)
    file.close()

WriteHeader(PRIME_ENGINE_CORE_PATH + OUTPUT_HEADER, GetAllHeaders())