import os

#graphics should be first in the include order
EXCEPTION_FILES = ["PrimeEngine.h", "DllExport.h", "File.h"]
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
    while stack:
        incPath += stack.pop()
    incPath += (file + ">")
    print(incPath)
    incPath += "\n"
    return incPath

def GetAllHeaders():
    headerList = []
    for root, dirs, files in os.walk(PRIME_ENGINE_CORE_PATH):
        for file in files:
            if file.endswith(".h") and file not in EXCEPTION_FILES:
                if "Graphics" in root:
                    headerList.insert(0, ParsePath(root, file))
                else:
                    headerList.append(ParsePath(root, file))
    return headerList

def WriteHeader(outputFilePath, headers):
    file = open(outputFilePath, 'w')
    file.write("#pragma once \n")
    for header in headers:
        file.write(header)
    file.close()

print("Started adding headers...")
WriteHeader(PRIME_ENGINE_CORE_PATH + OUTPUT_HEADER, GetAllHeaders())
print("Complete!")