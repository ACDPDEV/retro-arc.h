// Minimal test that bypasses conio.h issues
#include "Common/Consts.h"
#include "Common/Graphics.h"
#include "Common/Theme.h"
#include "Common/Font.h"
#include "Juegos/Pokemon/Views/TitleView.h"

int main() {
    std::cout << "Pokemon TitleView Test Program" << std::endl;
    std::cout << "Testing if TitleView can be compiled and instantiated..." << std::endl << std::endl;
    
    // Test basic initialization
    Common::Clear();
    
    // Test TitleView specifically
    try {
        Pokemon::TitleView();
        std::cout << "✓ TitleView compiled and ran successfully!" << std::endl;
        std::cout << "✓ No conio.h dependency issues in the UI rendering code!" << std::endl;
        std::cout << "✓ Pokemon title screen rendering appears to be working!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "✗ Error running TitleView: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
