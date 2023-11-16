#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

unordered_map<char, unordered_set<char>> followSets;
unordered_map<char, unordered_set<char>> firstSets;

bool isTerminal(char symbol) {
    return islower(symbol) || !isalpha(symbol);
}

void calculateFirst(char nonTerminal, const unordered_map<char, vector<vector<char>>>& grammar);

void calculateFollow(char nonTerminal, const unordered_map<char, vector<vector<char>>>& grammar) {
    if (followSets.find(nonTerminal) == followSets.end()) {
        followSets[nonTerminal]; 
    }

    if (nonTerminal == 'S') {
        followSets[nonTerminal].insert('$');
    }

    for (const auto& entry : grammar) {
        char nonTerm = entry.first;
        const vector<vector<char>>& productions = entry.second;

        for (const auto& production : productions) {
            auto it = find(production.begin(), production.end(), nonTerminal);
            if (it != production.end()) {

                size_t index = distance(production.begin(), it) + 1;
                while (index < production.size()) {
                    calculateFirst(production[index], grammar);
                    followSets[nonTerminal].insert(firstSets[production[index]].begin(), firstSets[production[index]].end());

                    if (firstSets[production[index]].find(' ') == firstSets[production[index]].end()) {
                        break;
                    }

                    index++;
                }

                if (index == production.size() || firstSets[production[index - 1]].find(' ') != firstSets[production[index - 1]].end()) {
                    calculateFollow(nonTerm, grammar);
                    followSets[nonTerminal].insert(followSets[nonTerm].begin(), followSets[nonTerm].end());
                }
            }
        }
    }
}

void calculateFirst(char nonTerminal, const unordered_map<char, vector<vector<char>>>& grammar) {
    if (isTerminal(nonTerminal)) {
        firstSets[nonTerminal].insert(nonTerminal);
        return;
    }

    if (firstSets.find(nonTerminal) != firstSets.end()) {
        return;
    }

    for (const auto& production : grammar.at(nonTerminal)) {
        for (char symbol : production) {
            calculateFirst(symbol, grammar);
            firstSets[nonTerminal].insert(firstSets[symbol].begin(), firstSets[symbol].end());

            if (firstSets[symbol].find(' ') == firstSets[symbol].end()) {
                break;
            }
        }
    }

    firstSets[nonTerminal].erase(' ');
}

int main() {
    unordered_map<char, vector<vector<char>>> productions = {
        {'S', {{'a', 'A', 'b'}, {'B'}}},
        {'A', {{'c'}, {' '}}},
        {'B', {{'d'}, {'e'}}}
    };
    for (const auto& entry : productions) {
        calculateFirst(entry.first, productions);
    }
    for (const auto& entry : productions) {
        calculateFollow(entry.first, productions);
    }
    for (const auto& entry : followSets) {
        cout << "Follow(" << entry.first << "): { ";
        for (char symbol : entry.second) {
            cout << symbol << ' ';
        }
        cout << "}\n";
    }
    return 0;
}
