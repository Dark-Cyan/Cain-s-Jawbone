#include <iostream>
#include <fstream>
#include <list>

// Column Headers
std::vector<std::string> colHeaders = {"Page Number", "Nouns", "Pronouns", "Adjectives", "Verbs", "Adverbs", "Prepositions", "Conjunctions", "Interjections", "Sentences", "Punctuation"};

// Nouns
std::unordered_map<std::string, int> Nouns;

// Pronouns - a complete list from wikipedia
std::unordered_map<std::string, int> Pronouns = {{"i",1}, {"me",1}, {"myself",1}, {"mine",1}, {"my",1}, {"we",1}, {"us",1}, {"ourselves",1}, {"ourself",1}, {"ours",1}, {"our",1}, {"you",1}, {"yourself",1}, {"yours",1}, {"your",1}, {"thou",1}, {"thee",1}, {"thyself",1}, {"thine",1}, {"thy",1}, {"yourselves",1}, {"ye",1}, {"yeerselves",1}, {"yeers",1}, {"yeer",1}, {"y'all",1}, {"y'all's",1}, {"y'all's selves",1}, {"youse",1}, {"yinz",1}, {"he",1}, {"him",1}, {"himself",1}, {"his",1}, {"she",1}, {"her",1}, {"herself",1}, {"hers",1}, {"it",1}, {"itself",1}, {"its",1}, {"they",1}, {"them",1}, {"themselves",1}, {"themself",1}, {"theirs",1}, {"their",1}, {"one",1}, {"oneself",1}, {"one's",1}, {"who",1}, {"whom",1}, {"whose",1}, {"what",1}, {"of what",1}, {"which",1}, {"of which",1}, {"whoself",1}, {"whoseself",1}, {"each other",1}, {"each other's",1}, {"another",1}, {"another's",1}, {"there",1}};

// Adjectives
std::unordered_map<std::string, int> Adjectives;

// Verbs
std::unordered_map<std::string, int> Verbs;

// Adverbs
std::unordered_map<std::string, int> Adverbs;

// Preposition
std::unordered_map<std::string, int> Prepositions;

// Conjunction
std::unordered_map<std::string, int> Conjunctions;

// Interjection
std::unordered_map<std::string, int> Interjections;



// Contractions
std::unordered_map<std::string, std::string> contractions = {{"Mr.", "Mister"}, {"Ms.", "Miss"}, {"Mrs.", "Mistress"}, {"Dr.", "Doctor"}, {"Prof.", "Professor"}, {"Revd.", "Reverend"}, {"Rev.", "Reverend"}, {"St.", "SaintOrStreet"}, {"Jr.", "Junior"}, {"Sr.", "Senior"}};

int getFileCharLength(std::fstream &file){
    file.seekg(0, std::fstream::end);
    int length = file.tellg();
    file.seekg(0, std::fstream::beg);
    return length;
}

// List Modifying Methods
void expand(std::list<std::string> &words){
    for (int i = 0; i < words.size(); i++){
        if (contractions.find(*next(words.begin(), i)) != contractions.end()){
            *next(words.begin(), i) = contractions[*next(words.begin(), i)];
        }
    }
}

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

void clean(std::list<std::string> &words){
    expand(words);
    separatePunctuation(words);
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

// Data Methods
std::vector<int> obtainData(std::list<std::string> &words){
    int nouns = 0;
    int pronouns = 0;
    int adjectives = 0;
    int verbs = 0;
    int adverbs = 0;
    int prepositions = 0;
    int conjunctions = 0;
    int interjections = 0;
    int sentences = 0;
    int punctuation = 0;

    // temporary
    std::unordered_map<std::string, int> SentenceLevelPunctuation = {{".", 2}, {"?", 2}, {"!", 2}, {";", 1}, {",", 1}, {":", 1}};

    for (int i = 0; i < words.size(); i++){
        std::string word = *next(words.begin(), i);
        if (Nouns.find(word) != Nouns.end()){
            nouns++;
        } else if (Pronouns.find(word) != Pronouns.end()){
            pronouns++;
            std::cout << word << '\n';
        } else if (Adjectives.find(word) != Adjectives.end()){
            adjectives++;
        } else if (Verbs.find(word) != Verbs.end()){
            verbs++;
        } else if (Adverbs.find(word) != Adverbs.end()){
            adverbs++;
        } else if (Prepositions.find(word) != Prepositions.end()){
            prepositions++;
        } else if (Conjunctions.find(word) != Conjunctions.end()){
            conjunctions++;
        } else if (Interjections.find(word) != Interjections.end()){
            interjections++;
        } else if (SentenceLevelPunctuation.find(word) != SentenceLevelPunctuation.end()){
            // Need to fix for elipsis
            punctuation++;
            if (SentenceLevelPunctuation.at(word) == 2){
                sentences++;
            }
        }
    }

    std::vector<int> data = {nouns, pronouns, adjectives, verbs, adverbs, prepositions, conjunctions, interjections, sentences, punctuation};
    return data;
}

std::string toCSVRow(int pageNumber, std::vector<int> &data){
    std::string row = "";
    row.push_back(static_cast<char>(pageNumber));
    for (int i = 0; i < data.size(); i++){
        row += ", " + static_cast<char>(data[i]);
    }
    std::cout << row;
    return row;
}

int main() {
    std::list<std::string> words = paragraphToList("../../../TextOrderings/OfficialText/95.txt");
    clean(words);
    for (std::string word : words){
        std::cout << word << std::endl;
    }
    std::cout << std::endl;
    std::vector<int> data = obtainData(words);
}