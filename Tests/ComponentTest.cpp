#include "../Common/Components/Select.h"
#include "../Common/Theme.h"

using namespace std;

int main() {
    Clear();
    const vector<string> options = {
        "1. Option 1",
        "2. Option 2",
        "3. Option 3",
        "4. Option 4",
        "5. Option 5"
    };
    int selected = 0;
    ComponentSelect(0, 0, BACKGROUND, SELECTION_BACKGROUND, options, selected, {"[>>>] ", ""});
    return 0;
}
