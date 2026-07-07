#include "../Common/Components/Select.h"
#include "../Common/Components/Aligned.h"
#include "../Common/Theme.h"

using namespace std;

int main() {
    EnableTrueColor();
    EnableUTF8();
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
    DrawFillRectangle(0, 0, 100, 100, " ", FOREGROUND, BACKGROUND);
    DrawText(AlignedX(0, 100, 10, "center"), 0, 10, -1, {"No se que escribir aquí", "Tampoco sé que escribir en esta línea"}, COLOR_DEFAULT, COLOR_DEFAULT);
    return 0;
}
