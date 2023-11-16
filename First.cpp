#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

unordered_map<char, unordered_set<char>> firstSets;

bool isTerminal(char symbol) {
    return islower(symbol) || !isalpha(symbol);
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

    for (const auto& production : productions) {
        calculateFirst(production.first, productions);
    }

    for (const auto& entry : firstSets) {
        cout << "First(" << entry.first << "): { ";
        for (char symbol : entry.second) {
            cout << symbol << ' ';
        }
        cout << "}\n";
    }
    return 0;
}
