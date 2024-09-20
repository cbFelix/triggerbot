#include <iostream>
#include <windows.h>
#include <cmath>
#include <string>
#include <stdexcept>

// Глобальные настройки по умолчанию
int radius = 1;                   // Радиус проверки
int checkDelayMs = 6;             // Задержка перед кликом (в мс)
int idleDelayMs = 1000;           // Задержка при неактивности (в мс)
char activateKey = 'P';           // Клавиша для активации
double colorChangeThreshold = 15.0; // Порог изменения цвета
std::string gameWindowTitle = ""; // Название окна игры

std::string Warning = "\nThis code is provided for educational purposes only and is an example.\nThe author is not responsible for the use of this code in real applications, including violation of the rules or terms of use of third party software. \nUse this code at your own risk.\n\n";


void PerformMouseClick(HWND hwnd) {
    PostMessage(hwnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(0, 0));
    Sleep(10);
    PostMessage(hwnd, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(0, 0));
}

COLORREF GetPixelColor(int x, int y) {
    HDC hdc = GetDC(NULL);
    if (!hdc) throw std::runtime_error("Failed to get device context.");

    COLORREF color = GetPixel(hdc, x, y);
    ReleaseDC(NULL, hdc);

    return color;
}

double GetColorDifference(COLORREF color1, COLORREF color2) {
    int rDiff = abs(GetRValue(color1) - GetRValue(color2));
    int gDiff = abs(GetGValue(color1) - GetGValue(color2));
    int bDiff = abs(GetBValue(color1) - GetBValue(color2));

    return ((rDiff + gDiff + bDiff) / 3.0 / 255.0) * 100.0;
}

bool IsKeyPressed(char key) {
    return (GetAsyncKeyState(key) & 0x8000) != 0;
}

bool IsGameWindowActive(const std::string& windowTitle) {
    HWND hwnd = GetForegroundWindow();
    char title[256];
    GetWindowTextA(hwnd, title, sizeof(title));
    return hwnd && strstr(title, windowTitle.c_str()) != nullptr;
}

void UpdateSettings() {
    std::cout << "Enter new radius: ";
    std::cin >> radius;

    std::cout << "Enter new check delay (ms): ";
    std::cin >> checkDelayMs;

    std::cout << "Enter new idle delay (ms): ";
    std::cin >> idleDelayMs;

    std::cout << "Enter new color change threshold: ";
    std::cin >> colorChangeThreshold;

    std::cout << "Enter new activate key: ";
    std::cin >> activateKey;

    std::cout << "Enter new game window title: ";
    std::cin.ignore(); // Clean input buffer
    std::getline(std::cin, gameWindowTitle);

    std::cout << "Settings updated.\n";
}

int main() {
    try {
        bool triggerActive = false;
        bool isIdle = true;
        bool messageDisplayed = false;

        const int conRadius = 1;
        COLORREF savedColors[2 * conRadius + 1][2 * conRadius + 1];

        Sleep(1000);
        std::cout << "==== Triggerbot by keww:L ====" << std::endl;

        Sleep(1000);
        std::cout << "Github: https://github.com/cbFelix/triggerbot" << std::endl;

        for (char _ : Warning) {
            std::cout << _;
            Sleep(14);
        }

        Sleep(500);
        UpdateSettings();

        while (true) {
            if (IsGameWindowActive(gameWindowTitle)) {
                if (!messageDisplayed) {
                    std::cout << "Game window is active. Ready to trigger." << std::endl;
                    messageDisplayed = true;
                }

                HWND hwnd = GetForegroundWindow();

                if (IsKeyPressed(activateKey)) {
                    if (!triggerActive) {
                        triggerActive = true;

                        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
                        int screenHeight = GetSystemMetrics(SM_CYSCREEN);
                        int centerX = screenWidth / 2;
                        int centerY = screenHeight / 2;

                        for (int x = -radius; x <= radius; ++x) {
                            for (int y = -radius; y <= radius; ++y) {
                                savedColors[x + radius][y + radius] = GetPixelColor(centerX + x, centerY + y);
                            }
                        }
                    }

                    bool pixelChanged = false;
                    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
                    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
                    int centerX = screenWidth / 2;
                    int centerY = screenHeight / 2;

                    for (int x = -radius; x <= radius; ++x) {
                        for (int y = -radius; y <= radius; ++y) {
                            COLORREF currentColor = GetPixelColor(centerX + x, centerY + y);
                            double colorDifference = GetColorDifference(savedColors[x + radius][y + radius], currentColor);

                            if (colorDifference > colorChangeThreshold) {
                                pixelChanged = true;
                                break;
                            }
                        }
                        if (pixelChanged) break;
                    }

                    if (pixelChanged) {
                        Sleep(checkDelayMs);
                        PerformMouseClick(hwnd);
                        std::cout << "Action executed: Significant pixel change detected.\n";
                        triggerActive = false;
                        isIdle = false;
                    }
                    else if (!isIdle) {
                        std::cout << "Idle: No significant changes detected.\n";
                        isIdle = true;
                    }
                }
                else {
                    triggerActive = false;
                }
            }
            else {
                if (messageDisplayed) {
                    std::cout << "Idle: Game window not active." << std::endl;
                    messageDisplayed = false;
                }
                Sleep(idleDelayMs);
            }

            Sleep(10);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

}
