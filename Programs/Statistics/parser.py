import os

def shuffle(originalList):
    newList = []
    for i in range(len(originalList)):
        n = int.from_bytes(os.urandom(4)) % len(originalList)
        newList.append(originalList.pop(n))
    return newList

text = ["text/" + str(x+1) + ".txt" for x in range(20)]
text = shuffle(text)

for page in text:
    txt = open(page)
    print(txt.read() + '\n')