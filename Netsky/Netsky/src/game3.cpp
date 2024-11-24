#include <iostream>
#include <cstdlib>
#include <ctime>
#include <game3.hpp>

using namespace std;


// Player and monster health
int playerHealth = 100;
int monsterHealth = 100;

// Random number generator
int num1, num2, correctAnswer;
void generateQuestion() {
    num1 = rand() % 20 + 1;
    num2 = rand() % 20 + 1;
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

    Color semiTransparentBlack = { 0, 0, 0, 230 };

    // Load textures and fonts
    Texture2D background = LoadTexture("graphics/arena.png");
    Texture2D monster = LoadTexture("graphics/Boss.png");
    Texture2D swordMark = LoadTexture("graphics/sword_mark.png");
    Texture2D clawmark = LoadTexture("graphics/claw_mark.png");
    Texture2D hero = LoadTexture("graphics/Hero.png");
    Button restartButton{"graphics/Restart_button.png", {380, 600}, 0.6f };
    Button homeButton{"graphics/Home_button.png", {635, 600}, 0.6f };
    Button quitButton{"graphics/Quit_button2.png", {880, 600}, 0.6f };
    Font fontBm = LoadFontEx("fonts/CartoonCheck-Black.ttf", 72, 0, 250);
    Sound hit_hero_sound = LoadSound("music/hit_human.MP3");
    Sound hit_monster = LoadSound("music/hit_monster.MP3");
    Music BOSS_music = LoadMusicStream("music/BOSS.mp3");
    Sound mute_sound = LoadSound("music/mute.MP3");
    Sound end_sound = LoadSound("music/end.MP3");

    SetTargetFPS(60);

    generateQuestion(); // Initial task

    char answer[10] = "\0";
    int answerIndex = 0;

    // Timer to track damage
    float damageTimer = 0.0f;
    bool monsterHit = false; // Track if the monster has been hit

    float damageTimer1 = 0.0f;
    bool heroHit = false;

    bool pause = false;
    bool gameOver = false;

    while (!WindowShouldClose()) {
        UpdateMusicStream(BOSS_music);

        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        // Update damage timer
        if (monsterHit) {
            PlaySound(hit_monster);
            damageTimer += GetFrameTime();
            if (damageTimer >= 0.5f) { // Show the effect for 0.5 seconds
                monsterHit = false;
                damageTimer = 0.0f;
            }
        }
        if (heroHit) {
            PlaySound(hit_hero_sound);
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
            generateQuestion();
        }

        if (IsKeyPressed(KEY_M))
        {
            StopMusicStream(BOSS_music);
            PlayMusicStream(BOSS_music);
        }

        if (IsKeyPressed(KEY_M))
        {
            PlaySound(mute_sound);
            pause = !pause;

            if (pause)
                PauseMusicStream(BOSS_music);
            else
                ResumeMusicStream(BOSS_music);

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
        DrawRectangleRounded({ 80, 5, 440, 40 }, 0.3f, 6, BLACK);
        DrawTextEx(fontBm, "PLAYER HEALTH", { 90, 10 }, (float)fontBm.baseSize - 40, 10, RAYWHITE);
        DrawRectangle(120, 50, int(playerHealth * 3.5), 35, GREEN);

        DrawRectangleRounded({ 890, 5, 470, 40 }, 0.3f, 6, BLACK);
        DrawTextEx(fontBm, "MONSTER HEALTH", { 900, 10 }, (float)fontBm.baseSize - 40, 10, RAYWHITE);
        DrawRectangle(940, 50, int(monsterHealth * 3.5), 35, RED);

        DrawRectangle(100, 500, 400, 130, semiTransparentBlack);
        DrawTextEx(fontBm, TextFormat("%d %c %d =", num1, operationSymbol, num2), { 220, 520 }, (float)fontBm.baseSize - 40, 10, WHITE);
        DrawTextEx(fontBm, "Your answer:", { 170, 550 }, (float)fontBm.baseSize - 40, 1, WHITE);
        DrawTextEx(fontBm, answer, { 265, 580 }, (float)fontBm.baseSize - 40, 10, WHITE);

        if (monsterHealth <= 0)
        {
            DrawRectangleRounded({ 270, 200, 900, 500 }, 0.3f, 6, BLACK);
            DrawTextEx(fontBm, "YOU WIN", { 530, 300 }, (float)fontBm.baseSize, 10, RAYWHITE);
            DrawTextEx(fontBm, "CONGRATULATIONS, CHAMPION!", { 360, 360 }, (float)fontBm.baseSize - 45, 10, RAYWHITE);
            restartButton.Draw();
            homeButton.Draw();
            quitButton.Draw();
            if (restartButton.IsPressed(mousePosition, mousePressed)) {

                PlaySound(end_sound);


                playerHealth = 100;
                monsterHealth = 100;
                answerIndex = 0;
                answer[0] = '\0';

                generateQuestion();

                gameOver = false;
            }
            else if (homeButton.IsPressed(mousePosition, mousePressed)) {
                UnloadFont(fontBm);
                UnloadTexture(background);
                UnloadTexture(monster);
                UnloadTexture(swordMark);
                UnloadTexture(clawmark);
                UnloadTexture(hero);
                UnloadSound(hit_hero_sound);
                UnloadSound(hit_monster);
                UnloadSound(end_sound);
                return MENU;

            }
            if (quitButton.IsPressed(mousePosition, mousePressed)) {
                UnloadFont(fontBm);
                UnloadTexture(background);
                UnloadTexture(monster);
                UnloadTexture(swordMark);
                UnloadTexture(clawmark);
                UnloadTexture(hero);
                UnloadSound(hit_hero_sound);
                UnloadSound(hit_monster);
                UnloadSound(end_sound);
                CloseWindow();
                return NIL;
            }
        }
        if (playerHealth <= 0)
        {
            DrawRectangleRounded({ 270, 200, 900, 500 }, 0.3f, 6, BLACK);
            DrawTextEx(fontBm, "GAME OVER", { 470, 300 }, (float)fontBm.baseSize, 10, RAYWHITE);
            DrawTextEx(fontBm, "BETTER LUCK NEXT", { 300, 360 }, (float)fontBm.baseSize - 10, 10, RAYWHITE);
            DrawTextEx(fontBm, "TIME", { 645, 420 }, (float)fontBm.baseSize - 10, 10, RAYWHITE);
            restartButton.Draw();
            homeButton.Draw();
            quitButton.Draw();
            if (restartButton.IsPressed(mousePosition, mousePressed)) {

                PlaySound(end_sound);

                
                playerHealth = 100;
                monsterHealth = 100;
                answerIndex = 0;
                answer[0] = '\0';

                generateQuestion(); 

                gameOver = false;  
            }
            else if (homeButton.IsPressed(mousePosition, mousePressed)) {
                UnloadFont(fontBm);
                UnloadTexture(background);
                UnloadTexture(monster);
                UnloadTexture(swordMark);
                UnloadTexture(clawmark);
                UnloadTexture(hero);
                UnloadSound(hit_hero_sound);
                UnloadSound(hit_monster);
                UnloadSound(end_sound);
                return GAME_SELECT;
            }
            if (quitButton.IsPressed(mousePosition, mousePressed)) {
                UnloadFont(fontBm);
                UnloadTexture(background);
                UnloadTexture(monster);
                UnloadTexture(swordMark);
                UnloadTexture(clawmark);
                UnloadTexture(hero);
                UnloadSound(hit_hero_sound);
                UnloadSound(hit_monster);
                UnloadSound(end_sound);
                CloseWindow();
                return NIL;
            }
        }

        EndDrawing();
    }

    // Unload textures
    UnloadMusicStream(BOSS_music);
    UnloadSound(hit_hero_sound);
    UnloadSound(hit_monster);
    UnloadTexture(background);
    UnloadTexture(monster);
    UnloadTexture(swordMark);
    UnloadTexture(hero);

    return NIL;
}