#include <iostream>

using namespace std;

void hideCursor();
void showCursor();
int main() {
    hideCursor();
 
    return 0;
}

void hideCursor(){
    cout << "\033[?25l" << flush;
}

void showCursor(){
    cout << "\033[?25h" << flush;
}