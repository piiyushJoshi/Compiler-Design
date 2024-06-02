#include <iostream> 
#include <cstring> 
using namespace std; 
int main() { 
char stack[20], ip[20], opt[10][10][2], ter[10]; 
int i, j, k, n, top = 0, col, row; 
for (i = 0; i < 10; i++) { 
stack[i] = '\0'; 
ip[i] = '\0'; 
for (j = 0; j < 10; j++) { 
opt[i][j][0] = '\0'; 
} 
} 
cout << "Enter the no.of terminals :\n"; 
cin >> n; 
cout << "\nEnter the terminals :\n"; 
cin >> ter; 
cout << "\nEnter the table values :\n"; 
for (i = 0; i < n; i++) { 
for (j = 0; j < n; j++) { 
cout << "Enter the value for " << ter[i] << " " << ter[j] << ": "; cin >> opt[i][j]; 
} 
} 
cout << "\n**** OPERATOR PRECEDENCE TABLE ****\n"; 
for (i = 0; i < n; i++) { 
cout << "\t" << ter[i]; 
}
cout << endl; 
for (i = 0; i < n; i++) { 
cout << endl << ter[i]; 
for (j = 0; j < n; j++) { 
cout << "\t" << opt[i][j][0]; 
} 
} 
stack[top] = '$'; 
cout << "\nEnter the input string:"; 
cin >> ip; 
i = 0; 
cout << "\nSTACK\t\t\tINPUT STRING\t\t\tACTION\n"; cout << "\n" << stack << "\t\t\t" << ip << "\t\t\t"; 
while (i <= strlen(ip)) { 
for (k = 0; k < n; k++) { 
if (stack[top] == ter[k]) 
col = k; 
if (ip[i] == ter[k]) 
row = k; 
} 
if ((stack[top] == '$') && (ip[i] == '$')) { 
cout << "String is accepted\n"; 
break; 
} else if ((opt[col][row][0] == '<') || (opt[col][row][0] == '=')) { stack[++top] = opt[col][row][0]; 
stack[++top] = ip[i]; 
cout << "Shift " << ip[i]; 
i++; 
} else { 
if (opt[col][row][0] == '>') { 
while (stack[top] != '<') { 
--top; 
}
top = top - 1; 
cout << "Reduce"; 
} else { 
cout << "\nString is not accepted"; break; 
} 
} 
cout << "\n"; 
for (k = 0; k <= top; k++) { 
cout << stack[k]; 
} 
cout << "\t\t\t"; 
for (k = i; k < strlen(ip); k++) { 
cout << ip[k]; 
} 
cout << "\t\t\t"; 
} 
return 0; 
}
