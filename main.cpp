#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include <fstream>
#include <map> // Added map header
#include <ctime> // Added ctime header for srand
using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1; // Exit with error
    }

    string filename = argv[1];
    ifstream in(filename);
    if (!in) {
        cerr << "Error: Unable to open file: " << filename << endl;
        return 1; // Exit with error
    }

    vector<string> tokens;
    set<string> unique;
    string next_line;
    while (getline(in, next_line)) {
        istringstream iss(next_line);
        string token;
        while (iss >> token) {
            string nopunct = "";
            for (auto &c : token) {
                if (isalpha(c)) {
                    nopunct += c;
                }
            }
            tokens.push_back(nopunct);
            unique.insert(nopunct);
        }
    }

    cout << "Number of words: " << tokens.size() << endl;
    cout << "Number of unique words: " << unique.size() << endl;

    ofstream setfile(filename + "_set.txt");
    if (!setfile) {
        cerr << "Error: Unable to create output file: " << filename + "_set.txt" << endl;
        return 1; // Exit with error
    }

    for (const string &word : unique) {
        cout << ' ' << word;
        setfile << ' ' << word;
    }

    cout << endl;

    // Create map
    map<string, vector<string>> wordmap;
    string state = "";
    // Populate the map with strings from tokens
    for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); ++it) {
        wordmap[state].push_back(*it);
        state = *it;
    }

    // Print out the map content
    int count = 0;
    for (const auto &entry : wordmap) {
        cout << "string: " << entry.first << endl;
        if (++count == 6) { // Print only the 6th entry
            cout << "6th Entry:" << endl;
            for (const auto &word : entry.second) {
                cout << word << " ";
            }
            cout << endl;
            break;
        }
    }

    srand(time(NULL)); // Initialize random seed

    state = "";
    // Generate 100 words that sound like the author from the text file.
    for (int i = 0; i < 100; i++) {
        int ind = rand() % wordmap[state].size(); // Pick a random word that comes after state
        cout << wordmap[state][ind] << " ";
        state = wordmap[state][ind]; // Update state to be the next word
    }
    cout << endl;

    return 0;
}
