#include <iostream> 
#include <vector> 
#include <map> 
#include <set> 
#include <string> 
#include <stack> 
#include <algorithm> 
#include <iomanip>
using namespace std; 
struct Production { 
 char lhs; 
 string rhs; 
}; 
vector<Production> grammar = { 
 {'S', "AB"}, 
 {'A', "aA"}, 
 {'A', "a"}, 
 {'B', "bB"}, 
 {'B', "b"} 
}; 
Production augmented = {'Z', "S"};  
struct Item { 
 char lhs; 
 string rhs; 
 int dot; // Position of the dot in the rhs 
 Item(char lhs, string rhs, int dot) : lhs(lhs), rhs(rhs), dot(dot) {}  
 bool operator<(const Item &other) const { 
 return tie(lhs, rhs, dot) < tie(other.lhs, other.rhs, other.dot);  } 
 bool operator==(const Item &other) const { 
 return lhs == other.lhs && rhs == other.rhs && dot == other.dot;  } 
}; 
vector<set<Item>> states; 
map<pair<int, char>, int> transitions; 
map<pair<int, char>, string> action; 
map<pair<int, char>, int> goto_table; 
set<Item> closure(const set<Item> &items) { 
 set<Item> closure_set = items; 
 bool added; 
 do { 
 added = false; 
 set<Item> new_items = closure_set; 
 for (const auto &item : closure_set) { 
 if (item.dot < item.rhs.size()) { 
 char next_symbol = item.rhs[item.dot]; 
 for (const auto &prod : grammar) { 
 if (prod.lhs == next_symbol) { 
 Item new_item(prod.lhs, prod.rhs, 0); 
 if (closure_set.find(new_item) == closure_set.end()) {  new_items.insert(new_item); 
 added = true; 
 } 
 } 
 } 
 } 
 }
 closure_set = new_items; 
 } while (added); 
 return closure_set; 
} 
set<Item> GOTO(const set<Item> &items, char symbol) {  set<Item> goto_set; 
 for (const auto &item : items) { 
 if (item.dot < item.rhs.size() && item.rhs[item.dot] == symbol) {  goto_set.insert(Item(item.lhs, item.rhs, item.dot + 1));  } 
 } 
 return closure(goto_set); 
} 
void compute_states() { 
 set<Item> start_set = {Item(augmented.lhs, augmented.rhs, 0)};  states.push_back(closure(start_set)); 
 bool added; 
 do { 
 added = false; 
 vector<set<Item>> new_states = states; 
 for (int i = 0; i < states.size(); ++i) { 
 set<Item> state = states[i]; 
 set<char> symbols; 
 for (const auto &item : state) { 
 if (item.dot < item.rhs.size()) { 
 symbols.insert(item.rhs[item.dot]); 
 } 
 } 
 for (char symbol : symbols) { 
 set<Item> goto_set = GOTO(state, symbol); 
 if (!goto_set.empty()) { 
 auto it = find(new_states.begin(), new_states.end(), goto_set);  if (it == new_states.end()) { 
 new_states.push_back(goto_set); 
 transitions[{i, symbol}] = new_states.size() - 1;  added = true; 
 } else { 
 transitions[{i, symbol}] = distance(new_states.begin(), it);  } 
 } 
 } 
 } 
 states = new_states; 
 } while (added); 
} 
void build_parsing_table() { 
 for (int i = 0; i < states.size(); ++i) { 
 set<Item> state = states[i]; 
 for (const auto &item : state) { 
 if (item.dot == item.rhs.size()) {
 if (item.lhs == augmented.lhs && item.rhs == augmented.rhs) { 
 action[{i, '$'}] = "ACC"; 
 } else { 
 for (char term : {'a', 'b', '$'}) { 
 action[{i, term}] = "r" + to_string(distance(grammar.begin(), find_if(grammar.begin(),  grammar.end(), [&](const Production &prod) { 
 return prod.lhs == item.lhs && prod.rhs == item.rhs; 
 }))); 
 } 
 } 
 } else { 
 char symbol = item.rhs[item.dot]; 
 if (isupper(symbol)) { 
 goto_table[{i, symbol}] = transitions[{i, symbol}]; 
 } else { 
 action[{i, symbol}] = "s" + to_string(transitions[{i, symbol}]); 
 } 
 } 
 } 
 } 
} 
void print_parsing_table() { 
 cout << setw(10) << "State" << setw(10) << "ACTION" << setw(20) << " " << "GOTO" << endl;  for (int i = 0; i < states.size(); ++i) { 
 cout << setw(10) << i; 
 for (char term : {'a', 'b', '$'}) { 
 if (action.find({i, term}) != action.end()) { 
 cout << setw(10) << action[{i, term}]; 
 } else { 
 cout << setw(10) << "-"; 
 } 
 } 
 cout << setw(20) << " "; // Adding extra space between ACTION and GOTO  for (char nonterm : {'S', 'A', 'B'}) { 
 if (goto_table.find({i, nonterm}) != goto_table.end()) { 
 cout << setw(10) << goto_table[{i, nonterm}]; 
 } else { 
 cout << setw(10) << "-"; 
 } 
 } 
 cout << endl; 
 } 
} 
bool parse(const string &input) { 
 stack<int> states_stack; 
 states_stack.push(0); 
 string remaining_input = input + "$"; 
 while (true) { 
 int state = states_stack.top(); 
 char symbol = remaining_input[0]; 
 string action_entry = action[{state, symbol}]; 
 if (action_entry == "ACC") { 
 return true;
 } else if (action_entry[0] == 's') { 
 int next_state = stoi(action_entry.substr(1)); 
 states_stack.push(next_state); 
 remaining_input.erase(0, 1); 
 } else if (action_entry[0] == 'r') { 
 int prod_index = stoi(action_entry.substr(1)); 
 Production prod = grammar[prod_index]; 
 for (int k = 0; k < prod.rhs.size(); ++k) { 
 states_stack.pop(); 
 } 
 state = states_stack.top(); 
 states_stack.push(goto_table[{state, prod.lhs}]); 
 } else { 
 return false; 
 } 
 } 
} 
int main() { 
 compute_states(); 
 build_parsing_table(); 
 print_parsing_table(); 
 string input; 
 cout << "Enter a string to parse: "; 
 cin >> input; 
 if (parse(input)) { 
 cout << "The string is accepted." << endl; 
 } else { 
 cout << "The string is rejected." << endl; 
 } 
 return 0; 
} 
