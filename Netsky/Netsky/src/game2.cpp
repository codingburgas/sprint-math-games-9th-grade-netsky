#include <raylib.h>

#include <iostream>
#include <cstdlib>
#include <string>
#include <game2.hpp>
using namespace std;

#define MAX_ITEMSSSIZE  35
void ReplaceSpecificUnderscore(char* text, int targetIndex, char replacement) {
    int underscoreCount = 0;

    // Iterate over the string to find underscores and replace the target index
    for (int i = 0; i < strlen(text); i++) {
        (text[i] == '_'); {
            underscoreCount++;
            // When the target underscore is reached, replace it
            if (underscoreCount == targetIndex) {
                text[i] = replacement;
                return;  // Stop after replacing the target underscore
            }
        }
    }
}

GameState game2()
{


    const int screenWidth = 1440;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib [text] example - input box");

    //--------------------------------------------------------------------------------------
    std::string wordList[] = { "product",
       "ordinal", "divisor", "percent" , "algebra" }; // the words we might get
    std::string ChosenWord = wordList[rand() % 5]; // choosing a word from the wordlist 

    char underscores[MAX_ITEMSSSIZE];
    char name[MAX_ITEMSSSIZE] = { '\0' };
    // find how many underscores we have to draw
    for (int i = 0; i < ChosenWord.length(); i++)
    {
        underscores[i] = '_';
    }
    underscores[ChosenWord.length()] = '\0';  // Null-terminate the string

    Rectangle textBox = { screenWidth / 2.0f - 140 , 70, 250, 70 };
    int LetterCount = 0;
    int MaxInput = ChosenWord.size();
    int lives = 5;
    bool found = false;
    int foundcount = 0;
    Rectangle textBox2 = { screenWidth / 2.0f + 200, 150, 280, 60 };
    int underscoreX = textBox.x + 3;
    int underscoreY = textBox.y + 20;
 
    Texture2D hangman0 = LoadTexture("graphics/Hangman0.png");
    Texture2D hangman5 = LoadTexture("graphics/Hangman5.png");
    Texture2D hangman4 = LoadTexture("graphics/Hangman4.png");
    Texture2D hangman3 = LoadTexture("graphics/Hangman3.png");
    Texture2D hangman2 = LoadTexture("graphics/Hangman2.png");
    Texture2D hangman1 = LoadTexture("graphics/Hangman1.png");
    Texture2D background = LoadTexture("graphics/squaredpapersheet.png");
    Font fontBt = LoadFontEx("fonts/Kalam-Bold.ttf", 75, 0, 250);
    Button restartButton{ "graphics/Restart_button.png", {140, 660}, 0.6f };
    Button homeButton{ "graphics/Home_button.png", {460, 660}, 0.6f };
    Button quitButton{ "graphics/Quit_button2.png", {780, 660}, 0.6f };
    Sound correct_sound = LoadSound("music/start.MP3");
    Sound incorrect_sound = LoadSound("music/go_back.MP3");
    Sound end_sound = LoadSound("music/end.MP3");
   


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
  

    // Main game loop
    while (!WindowShouldClose())    
    {
        

        int letter = GetCharPressed();
        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        while (letter > 0)
        {
            //Only allow keys in range [32..125]
            if ((letter >= 32) && (letter <= 125))

            {

                name[LetterCount] = (char)letter; 
                    name[LetterCount + 1] = '\0'; // Add null terminator at the end of the string

                LetterCount++;

            }
            letter = GetCharPressed();  // Check next character in the queue
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            LetterCount--;
            if (LetterCount < 0)
            {
                LetterCount = 0;
                name[LetterCount] = '\0';
            }

        }
        // check if the word has the letter the user entered
        if (IsKeyPressed(KEY_ENTER)) {
            char letterToCheck = name[LetterCount - 1];
            bool foundLetter = false;

            for (int i = 0; i < ChosenWord.size(); i++) {
                if (ChosenWord[i] == letterToCheck) {
                    foundLetter = true;
                    ReplaceSpecificUnderscore(underscores, i + 1, letterToCheck);  // +1 because underscores are 1-indexed in logic
                    //the letter has been found and replaced
                    foundcount++;
                    found = true;
                    PlaySound(correct_sound);
                }


            }
            if (!foundLetter) {
                lives--;  // Decrease lives if the letter isnt in the word
                PlaySound(incorrect_sound);
            }

        }


        BeginDrawing();

        ClearBackground(WHITE);
        DrawTexture(background, 0, 0, WHITE);


        DrawTextEx(fontBt, "GUESS THE WORD:", { 70, 70 }, (float)fontBt.baseSize, 30, BLACK);

        // draw the underscores
        DrawTextEx(fontBt, underscores, { textBox.x- 400, textBox.y + 105 }, (float)fontBt.baseSize, 60, BLACK);
        DrawRectangleLines(300, 300, (int)textBox2.width, (int)textBox2.height, DARKBLUE);



        DrawTextEx(fontBt, TextFormat( "Letters left: %i/%i", foundcount, MaxInput), { 500, 550 }, (float)fontBt.baseSize, 1, DARKBLUE);


        DrawTextEx(fontBt, "Guess a letter ", { 70, 260 }, (float)fontBt.baseSize, 30, BLACK);
        DrawTextEx(fontBt, "and press ENTER : ", { 70, 340 }, (float)fontBt.baseSize, 15, BLACK);
        DrawTextEx(fontBt, name, { 200, 400 }, (float)fontBt.baseSize, 60, BLACK);

        if (lives == 5)
        {
            DrawTextEx(fontBt, "Lives left: 5/5", { 500, 500 }, (float)fontBt.baseSize, 1, DARKBLUE);
            DrawTexture(hangman5, screenWidth / 2 - hangman5.width / 2, screenHeight / 2 - hangman5.height / 2, WHITE);
            if ((lives != 0) && (LetterCount == MaxInput))
            {
                DrawTextEx(fontBt, "GAME WON", { 350, 400 }, (float)fontBt.baseSize, 60, DARKGREEN);
            }
        }

        if (lives == 4)
        {
            DrawTextEx(fontBt, "Lives left: 4/5", { 500, 550 }, (float)fontBt.baseSize, 50, DARKBLUE);
            DrawTexture(hangman4, screenWidth / 2 - hangman4.width / 2, screenHeight / 2 - hangman4.height / 2, WHITE);
            if ((lives != 0) && (foundcount == MaxInput))
            {
                DrawTextEx(fontBt, "GAME WON", { 350, 400 }, (float)fontBt.baseSize, 60, DARKGREEN);
            }
        }

        if (lives == 3)
        {
            DrawTextEx(fontBt, "Lives left: 3/5", { 500, 550 }, (float)fontBt.baseSize, 50, DARKBLUE);
            DrawTexture(hangman3, screenWidth / 2 - hangman3.width / 2, screenHeight / 2 - hangman3.height / 2, WHITE);
            if ((lives != 0) && (foundcount == MaxInput))
            {
                DrawTextEx(fontBt, "GAME WON", { 350, 400 }, (float)fontBt.baseSize, 60, DARKGREEN);
            }
        }
        if (lives == 2)
        {
            DrawTextEx(fontBt, "Lives left: 2/5", { 500, 550 }, (float)fontBt.baseSize, 50, DARKBLUE);
            DrawTexture(hangman2, screenWidth / 2 - hangman2.width / 2, screenHeight / 2 - hangman2.height / 2, WHITE);
            if ((lives != 0) && (foundcount == MaxInput))
            {
                DrawTextEx(fontBt, "GAME WON", { 350, 400 }, (float)fontBt.baseSize, 60, DARKGREEN);
            }
        }
        if (lives == 1)
        {
            DrawTextEx(fontBt, "Lives left: 1/5", { 500, 550 }, (float)fontBt.baseSize, 50, DARKBLUE);
            DrawTexture(hangman1, screenWidth / 2 - hangman1.width / 2, screenHeight / 2 - hangman1.height / 2, WHITE);
            if ((lives != 0) && (foundcount == MaxInput))
            {
                DrawTextEx(fontBt, "GAME WON", { 350, 400 }, (float)fontBt.baseSize, 60, DARKGREEN);
            }

        }if (lives == 0)
        {
            DrawTextEx(fontBt, "Lives left: 0/5", { 500, 400 }, (float)fontBt.baseSize, 50, RED);
            DrawTextEx(fontBt, "GAME OVER", { 350, 400 }, (float)fontBt.baseSize, 60, RED);
            DrawTexture(hangman0, screenWidth / 2 - hangman0.width / 2, screenHeight / 2 - hangman0.height / 2, WHITE);
            PlaySound(end_sound);


        }
        restartButton.Draw();
        homeButton.Draw();
        quitButton.Draw();
        if (homeButton.IsPressed(mousePosition, mousePressed)) {
            UnloadSound(correct_sound);
            UnloadSound(end_sound);
            UnloadSound(incorrect_sound);
            UnloadTexture(hangman0);
            UnloadTexture(hangman5) ;
            UnloadTexture(hangman4) ;
            UnloadTexture(hangman3) ;
            UnloadTexture(hangman2);
            UnloadTexture(hangman1) ;
            UnloadTexture(background);
            UnloadFont(fontBt);
            return GAME_SELECT;
        }
        if (quitButton.IsPressed(mousePosition, mousePressed)) {
            UnloadSound(correct_sound);
            UnloadSound(end_sound);
            UnloadSound(incorrect_sound);
            UnloadTexture(hangman0);
            UnloadTexture(hangman5);
            UnloadTexture(hangman4);
            UnloadTexture(hangman3);
            UnloadTexture(hangman2);
            UnloadTexture(hangman1);
            UnloadTexture(background);
            UnloadFont(fontBt);
            return NIL;
        }
        if (restartButton.IsPressed(mousePosition, mousePressed)) {
            UnloadSound(correct_sound);
            UnloadSound(end_sound);
            UnloadSound(incorrect_sound);
            UnloadTexture(hangman0);
            UnloadTexture(hangman5);
            UnloadTexture(hangman4);
            UnloadTexture(hangman3);
            UnloadTexture(hangman2);
            UnloadTexture(hangman1);
            UnloadTexture(background);
            UnloadFont(fontBt);
            return GAME2;
        }






        EndDrawing();
       

    }
    // unload textures and fonts
    UnloadSound(correct_sound);
    UnloadSound(end_sound);
    UnloadSound(incorrect_sound);
    UnloadTexture(background);
    UnloadTexture(hangman0);
    UnloadTexture(hangman5);
    UnloadTexture(hangman4);
    UnloadTexture(hangman3);
    UnloadTexture(hangman2);
    UnloadTexture(hangman1);
    UnloadTexture(background);
    UnloadFont(fontBt);
    


    CloseWindow();



    return NIL;

  }
 




