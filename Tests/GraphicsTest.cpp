#include "../Common/Graphics.h"

using namespace std;

int main() {
    EnableUTF8();
    Clear();
    DrawBox(0, 0, 10, 5, {1,1,1,1}, {1,1,1,1});
    DrawBox(0, 6, 10, 5, {2,2,2,2}, {2,2,2,2});
    DrawBox(0, 12, 10, 5, {3,3,3,3}, {3,3,3,3});
    DrawBox(0, 18, 10, 5, {4,4,4,4}, {4,4,4,4});
    DrawBox(12, 0, 10, 5, {6,6,6,6}, {5,5,5,5});
    GoToXY(0, 50);
    return 0;
}
