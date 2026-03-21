import os

def shuffle(originalList):
    newList = []
    for i in range(len(originalList)):
        n = int.from_bytes(os.urandom(4)) % len(originalList)
        newList.append(originalList.pop(n))
    return newList

def obtainText():
    text = ["TextOrderings/OfficialText/" + str(x+1) + ".txt" for x in range(100)]
    return text

def randomPageOrder(text):
    text = shuffle(text)

    output = open("TextOrderings/OrderedText.txt", "w")
    for page in text:
        txt = open(page, "rt")
        output.write(txt.read() + '\n')
        txt.close
    output.close