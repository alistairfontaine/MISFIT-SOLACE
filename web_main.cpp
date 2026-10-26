#include <iostream>
#include <string>
#include <cstdint>
#include <limits>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
extern "C" {
    // Intercepts keys asynchronously from the global javascript buffer window array
    int _stdin_getchar();
}
#endif

enum class AppState {
    MainMenu,
    GroundingMode,
    ShredderMode,
    SurvivalMode,
    Exit
};

AppState g_currentState = AppState::MainMenu;
int g_selection = 0;
bool g_menuNeedsRedraw = true;
int g_subStateStep = 0;
long long g_frameCounter = 0;
long long g_lastStateFrame = 0;
std::string g_thoughtBuffer = "";
static std::uint8_t g_routineRegister = 0;

void clearScreen() {
    std::cout << "\033[2J\033[1;1H" << std::flush;
}

void runGroundingAnchorAsync() {
    if (g_subStateStep == 0) {
        clearScreen();
        std::cout << "[ MISFIT-SOLACE // KINETIC COGNITIVE ANCHOR ]\n";
        std::cout << "---------------------------------------------\n\n";
        std::cout << "Match the rhythm. Breathe in as the bar expands, exhale as it shrinks.\n\n";
        std::cout << "[ SYSTEM CALIBRATING: Stand by for frame synchronization... ]\n\n";
        g_subStateStep = 1;
        g_lastStateFrame = g_frameCounter;
        return;
    }

    if (g_subStateStep >= 1 && g_subStateStep <= 12) {
        // Step forward exactly every 60 frames (2 seconds at 30 FPS)
        if (g_frameCounter - g_lastStateFrame >= 60) {
            g_subStateStep++;
            g_lastStateFrame = g_frameCounter;
            
            int pattern = (g_subStateStep - 1) % 4;
            switch (pattern) {
                case 0: std::cout << "[ BREATHE IN  ] [====    ]\n" << std::flush; break;
                case 1: std::cout << "[ HOLD BREATH ] [========]\n" << std::flush; break;
                case 2: std::cout << "[ BREATHE OUT ] [====    ]\n" << std::flush; break;
                case 3: std::cout << "[ VACUUM HOLD ] [        ]\n" << std::flush; break;
            }
        }
    } else {
        std::cout << "\nCalibration stabilized. Send '4' to return to core loop.\n";
        g_subStateStep = 0;
        g_currentState = AppState::MainMenu;
        g_menuNeedsRedraw = true;
    }
}

void runThoughtShredderAsync(int inputChar) {
    if (g_subStateStep == 0) {
        clearScreen();
        std::cout << "[ MISFIT-SOLACE // ARCHIVAL MONOLOGUE SHREDDER ]\n";
        std::cout << "------------------------------------------------\n";
        std::cout << "Type whatever is poisoning your mind into the input box below.\n";
        std::cout << "Send '0' on a new line to execute the memory clearance protocol.\n\n>> " << std::flush;
        g_thoughtBuffer = "";
        g_subStateStep = 1;
        return;
    }

    if (inputChar == '0') {
        std::cout << "\n\nCommencing structural extraction matrix...\n";
        // Explicit volatile block overwrite to prevent browser swap memory mining leaks
        for (char &c : g_thoughtBuffer) c = '\0';
        g_thoughtBuffer.clear();
        std::cout << "[ BUFFER PURGED ] Raw string memory cleared from local space.\n";
        std::cout << "\nSend '4' to return to menu.\n";
        g_subStateStep = 0;
        g_currentState = AppState::MainMenu;
        g_menuNeedsRedraw = true;
    } else if (inputChar != 0 && inputChar != 10) { // Filter out structural carriage returns
        g_thoughtBuffer += (char)inputChar;
        std::cout << (char)inputChar << std::flush;
    }
}

void runSurvivalProtocolAsync(int inputChar) {
    if (g_menuNeedsRedraw) {
        clearScreen();
        std::cout << "[ MISFIT-SOLACE // MINIMALIST SURVIVAL PROTOCOL ]\n";
        std::cout << "-------------------------------------------------\n";
        std::cout << "No pressure. No streaks. Just check what you executed today.\n\n";
        std::cout << "[ " << ((g_routineRegister & (1 << 0)) ? "X" : " ") << " ] Bit 0: Hydrate (Drink water/survive metabolism)\n";
        std::cout << "[ " << ((g_routineRegister & (1 << 1)) ? "X" : " ") << " ] Bit 1: Move (Calisthenics / Muay Thai shadow / Walk)\n";
        std::cout << "[ " << ((g_routineRegister & (1 << 2)) ? "X" : " ") << " ] Bit 2: Clear Space (Reset one physical object in your room)\n\n";
        std::cout << "Enter bit number (0, 1, or 2) to toggle, or '4' to return: " << std::flush;
        g_menuNeedsRedraw = false;
    }

    if (inputChar >= '0' && inputChar <= '2') {
        int bit = inputChar - '0';
        g_routineRegister ^= (1 << bit);
        g_menuNeedsRedraw = true;
    } else if (inputChar == '4') {
        g_currentState = AppState::MainMenu;
        g_menuNeedsRedraw = true;
    }
}

void engineFrameTick() {
    g_frameCounter++;
    
    int ch = 0;
#ifdef __EMSCRIPTEN__
    ch = _stdin_getchar();
#endif

    if (g_currentState == AppState::MainMenu) {
        if (g_menuNeedsRedraw) {
            clearScreen();
            std::cout << "=================================================\n";
            std::cout << "           MISFIT-SOLACE // ENGINE CORE           \n";
            std::cout << "=================================================\n";
            std::cout << " 1. [SOLACE]   Run Kinetic Cognitive Anchor      \n";
            std::cout << " 2. [ECHO]     Open Archival Monologue Shredder  \n";
            std::cout << " 3. [MOMENTUM] Access Minimalist Survival Protocol\n";
            std::cout << " 4. [EXIT]     Terminate Instance                \n";
            std::cout << "-------------------------------------------------\n";
            std::cout << "Select current systemic vector: " << std::flush;
            g_menuNeedsRedraw = false;
        }

        if (ch != 0) {
            if (ch == '1') { g_currentState = AppState::GroundingMode; g_subStateStep = 0; }
            else if (ch == '2') { g_currentState = AppState::ShredderMode; g_subStateStep = 0; }
            else if (ch == '3') { g_currentState = AppState::SurvivalMode; g_menuNeedsRedraw = true; }
            else if (ch == '4') { g_currentState = AppState::Exit; }
        }
    } else if (g_currentState == AppState::GroundingMode) {
        runGroundingAnchorAsync();
    } else if (g_currentState == AppState::ShredderMode) {
        runThoughtShredderAsync(ch);
    } else if (g_currentState == AppState::SurvivalMode) {
        runSurvivalProtocolAsync(ch);
    } else if (g_currentState == AppState::Exit) {
        clearScreen();
        std::cout << "[ Instance Terminated Cleanly ]\n";
#ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
#endif
    }
}

int main() {
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(engineFrameTick, 30, 1);
#endif
    return 0;
}

