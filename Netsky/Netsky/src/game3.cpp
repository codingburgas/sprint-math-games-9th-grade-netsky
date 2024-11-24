#include <raylib.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <game3.hpp>

using namespace std;

constexpr int screenWidth = 1440;
constexpr int screenHeight = 800;

// Player and monster health
int playerHealth = 100;
int monsterHealth = 100;

// Random number generator
int num1, num2, correctAnswer;
void GenerateQuestion() {
    num1 = rand() % 10 + 1;
    num2 = rand() % 10 + 1;
    int operation = rand() % 3;

    if (operation == 0) {
        correctAnswer = num1 + num2;
    }
    else if (operation == 1) {
        correctAnswer = num1 * num2;
    }
    else {
        while (num1 % num2 != 0) {
            num1 = rand() % 10 + 1;
            num2 = rand() % 10 + 1;
        }
        correctAnswer = num1 / num2;
    }
}

GameState game3() {
    InitWindow(screenWidth, screenHeight, "Math Battle");

    // Load textures and fonts
    Texture2D background = LoadTexture("graphics/arena.png");
    Texture2D monster = LoadTexture("graphics/Boss.png");
    Texture2D swordMark = LoadTexture("graphics/sword_mark.png");
    Texture2D clawmark = LoadTexture("graphics/claw_mark.png");
    Texture2D hero = LoadTexture("graphics/Hero.png");
    Font fontBm = LoadFontEx("fonts/CartoonCheck-Black.ttf", 32, 0, 250);

    SetTargetFPS(60);
    srand(time(0));

    GenerateQuestion(); // Initial task

    char answer[10] = "\0";
    int answerIndex = 0;

    // Timer to track damage
    float damageTimer = 0.0f;
    bool monsterHit = false; // Track if the monster has been hit

    float damageTimer1 = 0.0f;
    bool heroHit = false;

    while (!WindowShouldClose()) {
        // Update damage timer
        if (monsterHit) {
            damageTimer += GetFrameTime();
            if (damageTimer >= 0.5f) { // Show the effect for 0.5 seconds
                monsterHit = false;
                damageTimer = 0.0f;
            }
        }
        if (heroHit) {
            damageTimer1 += GetFrameTime();
            if (damageTimer1 >= 0.5f) { // Show the effect for 0.5 seconds
                heroHit = false;
                damageTimer1 = 0.0f;
            }
        }

        // Input handling
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= '0' && key <= '9') && (answerIndex < 9)) {
                answer[answerIndex++] = (char)key;
                answer[answerIndex] = '\0';
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && answerIndex > 0) {
            answer[--answerIndex] = '\0';
        }

        if (IsKeyPressed(KEY_ENTER)) {
            if (atoi(answer) == correctAnswer) {
                monsterHealth -= 20;
                monsterHit = true;  // Trigger the hit effect
            }
            else {
                playerHealth -= 40;
                heroHit = true;
            }
            answerIndex = 0;
            answer[0] = '\0';
            GenerateQuestion();
        }

        char operationSymbol;
        if (correctAnswer == num1 + num2) {
            operationSymbol = '+';
        }
        else if (correctAnswer == num1 * num2) {
            operationSymbol = '*';
        }
        else {
            operationSymbol = '/';
        }

        // Draw game elements
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(background, 0, 0, WHITE);

        // Display the appropriate monster texture
        if (monsterHit) {
            DrawTextureEx(swordMark, { 650, 420 }, 0.0f, 0.53f, WHITE); 
        }
        else {
            DrawTextureEx(monster, { 650, 420 }, 0.0f, 0.53f, WHITE); 
        }

        if (heroHit) {
            DrawTextureEx(clawmark, { 600, 600 }, 0.0f, 0.38f, WHITE); 
        }
        else {
            DrawTextureEx(hero, { 600, 600 }, 0.0f, 0.38f, WHITE); 
        }

        // Health bars
        DrawRectangleRounded({ 80, 5, 440, 40 }, 0.3, 6, BLACK);
        DrawTextEx(fontBm, "PLAYER HEALTH", { 90, 10 }, (float)fontBm.baseSize, 10, RAYWHITE);
        DrawRectangle(120, 50, playerHealth * 3.5, 35, GREEN);

        DrawRectangleRounded({ 890, 5, 470, 40 }, 0.3, 6, BLACK);
        DrawTextEx(fontBm, "MONSTER HEALTH", { 900, 10 }, (float)fontBm.baseSize, 10, RAYWHITE);
        DrawRectangle(940, 50, monsterHealth * 3.5, 35, RED);

        DrawRectangle(100, 500, 400, 130, BLACK);
        DrawTextEx(fontBm, TextFormat("%d %c %d =", num1, operationSymbol, num2), { 220, 520 }, (float)fontBm.baseSize, 10, WHITE);
        DrawTextEx(fontBm, "Your answer:", { 170, 550 }, (float)fontBm.baseSize, 1, WHITE);
        DrawTextEx(fontBm, answer, { 265, 580 }, (float)fontBm.baseSize, 10, WHITE);

        EndDrawing();
    }

    // unload textures
    UnloadTexture(background);
    UnloadTexture(monster);
    UnloadTexture(swordMark); // unload sword mark texture
    UnloadTexture(hero);
    CloseWindow();

    return NIL;
}