#include <raylib.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <game3.hpp>

using namespace std;

constexpr int screenWidth = 1440;
constexpr int screenHeight = 800;

// player and moster health
int playerHealth = 100;
int monsterHealth = 100;

// random number generator
int num1, num2, correctAnswer;
void GenerateQuestion() {
    num1 = rand() % 10 + 1;
    num2 = rand() % 10 + 1;
    int operation = rand() % 3;  // randomly choose operation

    if (operation == 0) { // addition
        correctAnswer = num1 + num2;
    } else if (operation == 1) { // multiplication
        correctAnswer = num1 * num2;
    } else { // Division
        while (num1 % num2 != 0) { // ensure clean division
            num1 = rand() % 10 + 1;
            num2 = rand() % 10 + 1;
        }
        correctAnswer = num1 / num2;
    }
}

GameState game3() 
{
    InitWindow(screenWidth, screenHeight, "Math Battle");
    
    // load textures and fonts
    Texture2D background = LoadTexture("graphics/arena.jpg");
    Image healthBarImage = LoadImage("graphics/HealthBar.png");
    ImageResize(&healthBarImage, 350, 35);  // change in size of healtBar
    Texture2D healthBar = LoadTextureFromImage(healthBarImage);
    UnloadImage(healthBarImage);
    
    Font fontBm = LoadFontEx("fonts/CartoonCheck-Black.ttf", 32, 0, 250);
    
    SetTargetFPS(60);
    srand(time(0)); // initializing the random number generator
    
    GenerateQuestion(); // initial task
    
    char answer[10] = "\0";  // response input buffer
    int answerIndex = 0;
    
    while (!WindowShouldClose()) {
        // input verification
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
                monsterHealth -= 20;  // reduces monster health
            } else {
                playerHealth -= 40;  // reduces player health
            }
            answerIndex = 0;
            answer[0] = '\0';
            GenerateQuestion();  // generate a new question
        }
        char operationSymbol;
        if (correctAnswer == num1 + num2) {
        operationSymbol = '+';
        } else if (correctAnswer == num1 * num2) {
        operationSymbol = '*';
        } else {
        operationSymbol = '/';
        }
        
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(background, 0, 0, WHITE);
        
        // health bars
        DrawRectangleRounded({80, 5, 440, 40}, 0.3, 6, BLACK);
        DrawTextEx(fontBm, "PLAYER HEALTH", {90, 10}, (float)fontBm.baseSize, 10, RAYWHITE);
        DrawRectangle(120, 50, playerHealth * 3.5, 35, GREEN); 
        
        
        DrawRectangleRounded({890, 5, 470, 40}, 0.3, 6, BLACK);
        DrawTextEx(fontBm, "MONSTER HEALTH", {900, 10}, (float)fontBm.baseSize, 10, RAYWHITE);
        DrawRectangle(940, 50, monsterHealth * 3.5, 35, RED);
        
        DrawRectangle(540, 350, 400, 130, BLACK);
        DrawTextEx(fontBm, TextFormat("%d %c %d =", num1, operationSymbol, num2), {650, 370}, (float)fontBm.baseSize, 10, WHITE);
        DrawTextEx(fontBm, "Your answer:", {screenWidth / 2 - 100, 400}, (float)fontBm.baseSize, 1, WHITE);
        DrawTextEx(fontBm, answer, {710, 435}, (float)fontBm.baseSize, 10, WHITE);


        
        EndDrawing();
    }
    
    // unload textures
    UnloadTexture(background);
    UnloadTexture(healthBar);
    CloseWindow();
    
    return NIL;
}