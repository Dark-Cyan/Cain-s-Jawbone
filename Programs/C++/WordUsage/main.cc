#include <iostream>
#include <fstream>
#include <list>

int getFileCharLength(std::fstream &file){
    file.seekg(0, std::fstream::end);
    int length = file.tellg();
    file.seekg(0, std::fstream::beg);
    return length;
}

void printNestedUnorderedMap(std::unordered_map<std::string, std::unordered_map<int, int>> uMap){
    for (auto i : uMap){
        std::cout << i.first << " : ";
        for (auto j : i.second){
            std::cout << j.first << ", ";
        }
        std::cout << '\n';
    }
}

// List Modifying Methods
void separatePunctuation(std::list<std::string> &words){
    int i = 0;
    while (i < words.size()){
        std::string &word = *next(words.begin(), i);
        if(!isalpha(word.back()) && word.size() > 1){
            std::string punctuation(1,word.back());
            word.pop_back();
            words.insert(std::next(words.begin(), i+1), punctuation);
        }
        i++;
    }
}

void uncapitalize(std::list<std::string> &words){
    for (std::string &word : words){
        if (isalpha(word[0])){
            word[0] = tolower(word[0]);
        }
    }
}

void clean(std::list<std::string> &words){
    separatePunctuation(words);
    uncapitalize(words);
}

std::list<std::string> paragraphToList(std::string relPath){    
    std::fstream page(relPath);
    int length = getFileCharLength(page);

    std::list<std::string> words;
    std::string word;
    while(page.tellg() < length){
        char nextChar = static_cast<char>(page.get());
        if (nextChar == ' '){
            words.push_back(word);
            word.clear();
        } else {
            word += nextChar;
            if (page.tellg() == length){
                words.push_back(word);
                word.clear();
            }
        }
    }

    page.close();
    return words;
}

void addListToMap(std::unordered_map<std::string, std::unordered_map<int, int>> &wordsWithPages, std::list<std::string> &words, int pageNumber){
    for (std::string word : words){
        wordsWithPages[word][pageNumber]++;
    }
}

std::unordered_map<int, int> pageConnections(std::unordered_map<std::string, std::unordered_map<int, int>> &wordsWithPages){
    for (auto i : wordsWithPages){
        for (auto j : i.second){
            
        }
    }
}

int main() {
    std::unordered_map<std::string, std::unordered_map<int, int>> wordsWithPages;

    for (int i = 1; i <= 100; i++){
        std::list<std::string> words = paragraphToList("../../../TextOrderings/OfficialText/" + std::to_string(i) + ".txt");
        clean(words);
        addListToMap(wordsWithPages, words, i);
    }
    
    // printNestedUnorderedMap(wordsWithPages);

    std::fstream out("WordLocations.txt");
    for (auto i : wordsWithPages){
        out << i.first << " : ";
        for (auto j : i.second){
            out << j.first << ", ";
        }
        out << '\n';
    }

    out.close();
}