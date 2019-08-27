// https://leetcode.com/problems/regular-expression-matching/

#include <string>
#include <iostream>
#include <set>
#include <map>
#include <queue>

class Node {
public:
    std::map<char, std::set<Node*>> outPaths;
    char c = '-';
    int position ;

    Node(int position) {
        this->position = position;
    }

    void addPath(char key, Node* nextNode) {
        outPaths[key].insert(nextNode);
        nextNode->c = key;
    }
};


class Solution {
public:
    explicit Solution(std::string p) {
        initialize(p);
    }

    void initialize(std::string p) {
        root = new Node(0);
        auto* current_nodes = new std::set<Node*>();
        current_nodes->insert(root);
        int p_index = 0;

        while (p_index < p.size()) {
            char current_char = p[p_index];
            Node* new_node = new Node(p_index + 1);

            for (auto current_node : *current_nodes) {
                current_node->addPath(current_char, new_node);
            }

            auto* new_current_nodes = new std::set<Node*>();
            new_current_nodes->insert(new_node);

            // If the next character is a *, the current character is also linked to itself. Because * can be 0, the
            // current frontier is added to the next iteration's frontier (this is recursive as if the previous
            // character was also augmented with *, it would have been in the current frontier).
            if (p_index + 1 < p.size() && p[p_index + 1] == '*') {
                new_node->addPath(current_char, new_node);
                for (auto current_node : *current_nodes) {
                    new_current_nodes->insert(current_node);
                }
                p_index++;
            }

            current_nodes = new_current_nodes;
            p_index++;
        }
        terminals = current_nodes;
    }

    void traverse() {
        std::queue<Node*> q;
        q.push(root);
        std::set<Node*> seen;
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            if (seen.find(current) != seen.end()) {
                continue;
            } else {
                seen.insert(current);
            }
            std::cout << current->c << " " << current->position << ": ";
            for (auto it : current->outPaths) {
                std::cout << it.first << " ";
                for (auto i : it.second) {
                    std::cout << i->position << " ";
                    q.push(i);
                }
            }
            std::cout << std::endl;
        }
        std::cout << "Terminals: ";
        for (auto it : *terminals) {
            std::cout << it->c << " ";
        }
        std::cout << std::endl;
    }

    bool match(std::string s) {
        auto* positions = new std::set<Node*>();
        positions->insert(root);
        int s_index = 0;

        while (s_index < s.size()) {

            if (positions->empty()) {
                return false;
            }

            char current_char = s[s_index];
            auto* new_positions = new std::set<Node*>();

            for (auto position : *positions) {
                if (position->outPaths.find(current_char) != position->outPaths.end()) {
                    for (auto it : position->outPaths[current_char]) {
                        new_positions->insert(it);
                    }
                }
                if (position->outPaths.find('.') != position->outPaths.end()) {
                    for (auto it : position->outPaths['.']) {
                        new_positions->insert(it);
                    }
                }
            }

            positions = new_positions;
            s_index++;
        }

        for (auto position : *positions) {
            if (terminals->find(position) != terminals->end()) {
                return true;
            }
        }
        return false;
    }

private:
    Node* root = nullptr;
    std::set<Node*>* terminals;
};

int main() {
    Solution sol("c*..b*a*a.*a..*c");
    sol.traverse();
    std::cout << sol.match("baabbbaccbccacacc") << std::endl;
}
