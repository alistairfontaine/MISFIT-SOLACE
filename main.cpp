#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cstdint>
#include <algorithm>
#include <limits>

// Operational States
enum class AppState {
    MainMenu,
    GroundingMode, // SOLACE
    ShredderMode,  // ECHO
    SurvivalMode,  // MOMENTUM
    Exit
};

// Utilities for Terminal Rendering
void typewriterPrint(const std::string& text, unsigned int millisecondsPerChar) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(millisecondsPerChar));
    }
    std::cout << std::endl;
}

void clearScreen() {
    // Standard ANSI escape codes to clear screen and reset cursor position
    std::cout << "\033[2J\033[1;1H" << std::flush;
}

// Module 1: The Grounding Anchor (SOLACE)
void runGroundingAnchor() {
    clearScreen();
    typewriterPrint("[ MISFIT-SOLACE // KINETIC COGNITIVE ANCHOR ]", 30);
    std::cout << "---------------------------------------------\n\n";
    typewriterPrint("Match the rhythm. Breathe in as the bar expands, exhale as it shrinks.", 20);
    std::cout << "\nPress Enter to begin the 4-count calibration loop...\n";
    std::cin.ignore();
    std::cin.get();

    // Rhythmic breathing sequence loop
    for (int i = 0; i < 3; ++i) {
        std::cout << "\r[ BREATHE IN  ] [====    ] " << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "\r[ HOLD BREATH ] [========] " << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "\r[ BREATHE OUT ] [====    ] " << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "\r[ VACUUM HOLD ] [        ] " << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    std::cout << "\n\nCalibration stabilized. Press Enter to return to core loop...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Module 2: The Thought Shredder (ECHO)
void runThoughtShredder() {
    clearScreen();
    std::cout << "[ MISFIT-SOLACE // ARCHIVAL MONOLOGUE SHREDDER ]\n";
    std::cout << "------------------------------------------------\n";
    std::cout << "Type out whatever is poisoning your mind right now.\n";
    std::cout << "When you are done, press Enter twice to securely execute the buffer.\n\n";
    std::cout << ">> ";

    std::string inputBuffer;
    std::string line;
    std::cin.ignore();
    
    while (std::getline(std::cin, line) && !line.empty()) {
        inputBuffer += line + "\n";
    }

    std::cout << "\nCommencing extraction...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(800));

    // Custom ASCII execution animation
    for (int i = 0; i < 3; ++i) {
        std::cout << "[ SHREDDING BLOCK: " << i * 33 << "% ] \r" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }

    // Explicit Memory Hard Zeroing
    std::fill(inputBuffer.begin(), inputBuffer.end(), '\0');
    inputBuffer.clear();

    std::cout << "\n[ BUFFER PURGED ] Raw string memory cleared from local space.\n";
    std::cout << "\nPress Enter to return to menu...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Module 3: The Survival Protocol (MOMENTUM)
void runSurvivalProtocol() {
    clearScreen();
    // 8-bit tracking register (Bit 0: Hydrate, Bit 1: Move, Bit 2: Clear Space)
    static std::uint8_t routineRegister = 0; 

    std::cout << "[ MISFIT-SOLACE // MINIMALIST SURVIVAL PROTOCOL ]\n";
    std::cout << "-------------------------------------------------\n";
    std::cout << "No pressure. No streaks. Just check what you executed today.\n\n";

    std::cout << "[ " << ((routineRegister & (1 << 0)) ? "X" : " ") << " ] Bit 0: Hydrate (Drink water/survive metabolism)\n";
    std::cout << "[ " << ((routineRegister & (1 << 1)) ? "X" : " ") << " ] Bit 1: Move (Calisthenics / Muay Thai shadow / Walk)\n";
    std::cout << "[ " << ((routineRegister & (1 << 2)) ? "X" : " ") << " ] Bit 2: Clear Space (Reset one physical object in your room)\n\n";

    std::cout << "Enter the bit number (0, 1, or 2) to toggle execution state, or '9' to return: ";
    int choice;
    std::cin >> choice;

    if (choice >= 0 && choice <= 2) {
        routineRegister ^= (1 << choice); // Flip the specific bit using XOR mask
    }
}

int main() {
    AppState currentState = AppState::MainMenu;
    int selection = 0;

    while (currentState != AppState::Exit) {
        clearScreen();
        std::cout << "=================================================\n";
        std::cout << "           MISFIT-SOLACE // ENGINE CORE           \n";
        std::cout << "=================================================\n";
        std::cout << " 1. [SOLACE]   Run Kinetic Cognitive Anchor      \n";
        std::cout << " 2. [ECHO]     Open Archival Monologue Shredder  \n";
        std::cout << " 3. [MOMENTUM] Access Minimalist Survival Protocol\n";
        std::cout << " 4. [EXIT]     Terminate Instance                \n";
        std::cout << "-------------------------------------------------\n";
        std::cout << "Select current systemic vector: ";
        
        if (!(std::cin >> selection)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        // Clean out any leftover characters (like '\n') from the input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (selection) {
            case 1:
                currentState = AppState::GroundingMode;
                runGroundingAnchor();
                currentState = AppState::MainMenu;
                break;
            case 2:
                currentState = AppState::ShredderMode;
                runThoughtShredder();
                currentState = AppState::MainMenu;
                break;
            case 3:
                currentState = AppState::SurvivalMode;
                runSurvivalProtocol();
                currentState = AppState::MainMenu;
                break;
            case 4:
                currentState = AppState::Exit;
                break;
            default:
                break;
        }
    }

    clearScreen();
    std::cout << "[ Instance Terminated Cleanly ]\n";
    return 0;
}

