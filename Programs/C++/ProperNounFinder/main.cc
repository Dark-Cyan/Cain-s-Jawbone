#include <iostream>
#include <fstream>
#include "list.h"

std::unordered_map<std::string, std::string> contractions = {{"Mr.", "Mister"}, {"Ms.", "Miss"}, {"Mrs.", "Mistress"}, {"Dr.", "Doctor"}, {"Prof.", "Professor"}, {"Revd.", "Reverend"}, {"Rev.", "Reverend"}, {"St.", "SaintOrStreet"}, {"Jr.", "Junior"}, {"Sr.", "Senior"}};

list pagesToList(std::vector<std::string> pages){
  list words = list();

  for (std::string relPath : pages){
    std::fstream page(relPath);

    page.seekg(0, std::fstream::end);
    int length = page.tellg();
    page.seekg(0, std::fstream::beg);

    std::string word = "";
    while (page.tellg() < length){
      char nextChar = static_cast<char>(page.get());
      if (nextChar == ' '){
        words.add(word,-1);
        word.clear();
      } else {
        word += nextChar;
      }
    }
    if (!word.empty()){
      words.add(word, -1);
      word.clear();
    }
    page.close();
  }
  return words;
}

list removeAbbrev(list unabbrev){
  int i = 0;
  while (i < unabbrev.size()){
    std::string word = unabbrev.get(i);
    if (contractions.find(word) != contractions.end()){
      unabbrev.removeAt(i);
      unabbrev.add(contractions[word],i);
    }
    i++;
  }

  return unabbrev;
}

list attachNouns(list unattached){
  int i = 0;
  while (i < unattached.size() - 1){
    std::string wordOne = unattached.get(i);
    std::string wordTwo = unattached.get(i+1);
    if (isupper(wordOne.front()) && islower(wordOne.back()) && isupper(wordTwo.front())){
      unattached.add(wordOne + " " + wordTwo, i);
      unattached.removeAt(i+1);
      unattached.removeAt(i+1);
      i--;
    }
    i++;
  } 

  return unattached;
}

list removeLowercase(list lowercase){
  int i = 0;
  while (i < lowercase.size()){
    std::string word = lowercase.get(i);
    if (!isupper(word.front())){
      lowercase.removeAt(i);
      i--;
    }
    i++;
  }

  return lowercase;
}

list removePunctuation(list punctuated){
  int i = 0;
  while (i < punctuated.size()){
    std::string word = punctuated.get(i);
    if (!isalpha(word.back())){
      word.pop_back();
      punctuated.removeAt(i);
      punctuated.add(word,i);
    }
    i++;
  }

  return punctuated;
}

std::unordered_map<std::string, int> listToUMap(list linkedList){
  std::unordered_map<std::string, int> uMap;
  for (int i = 0; i < linkedList.size(); i++){
    uMap[linkedList.get(i)]++;
  }
  return uMap;
}

int main() {

  // Creates a relative path to each file(page) of text as a vector
  std::vector<std::string> pages;
  for (int i = 1; i <= 100; i++){
    pages.push_back("../../../TextOrderings/OfficialText/" + std::to_string(i) + ".txt");
  }
  list words = pagesToList(pages);

  words = removeAbbrev(words);
  words = attachNouns(words);
  words = removeLowercase(words);
  words = removePunctuation(words);

  std::unordered_map<std::string, int> mappedWords = listToUMap(words);

  std::fstream out("../../../CapitalWords.txt");
  for (auto i : mappedWords){
    out << i.first << ": " << i.second << std::endl;
  }

  out.close();

  return 0;
}