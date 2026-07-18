#include "../Common/Components/SelectComponent.h"
#include "../Common/Aligned.h"
#include "../Common/Theme.h"

using namespace std;

int main() {
    Common::EnableTrueColor();
    Common::EnableUTF8();
    Common::Clear();
    const vector<string> options = {
        "1. Option 1",
        "2. Option 2",
        "3. Option 3",
        "4. Option 4",
        "5. Option 5"
    };
    int selected = 0;
    Common::SelectComponent(0, 0, Common::BACKGROUND, Common::SELECTION_BACKGROUND, options, selected, {"[>>>] ", ""});
    Common::DrawFillRectangle(0, 0, 100, 100, " ", Common::FOREGROUND_DARK, Common::BACKGROUND);
    Common::DrawText(Common::AlignedX(0, 100, 10, "center"), 0, 10, -1, {"No se que escribir aquí", "Tampoco sé que escribir en esta línea"}, Common::COLOR_DEFAULT, Common::COLOR_DEFAULT);
    return 0;
}
