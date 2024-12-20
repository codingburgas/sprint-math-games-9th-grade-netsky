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


    //--------------------------------------------------------------------------------------
    std::string wordList[] = { "product",
       "ordinal", "divisor", "percent" , "algebra" }; // initialize the words we might get
    std::string chosenWord = wordList[rand() % 5]; // choosing a word from the wordlist 
    char underscores[MAX_ITEMSSSIZE];
    char name[MAX_ITEMSSSIZE] = { '\0' };

    for (int i = 0; i < chosenWord.length(); i++)// find how many underscores we have to draw
    {
        underscores[i] = '_';
    }
    underscores[chosenWord.length()] = '\0';  // Null-terminate the string

    
    int letterCount = 0;
    int maxInput = int(chosenWord.size());
    int lives = 5;
    bool found = false;
    int foundcount = 0;
   

    // initializing textures and fonts
    Texture2D hangman0 = LoadTexture("graphics/Hangman0.png");
    Texture2D hangman5 = LoadTexture("graphics/Hangman5.png");
    Texture2D hangman4 = LoadTexture("graphics/Hangman4.png");
    Texture2D hangman3 = LoadTexture("graphics/Hangman3.png");
    Texture2D hangman2 = LoadTexture("graphics/Hangman2.png");
    Texture2D hangman1 = LoadTexture("graphics/Hangman1.png");
    Texture2D background = LoadTexture("graphics/squaredpapersheet.png");
    Font fontBt = LoadFontEx("fonts/Kalam-Bold.ttf", 75, 0, 250);
    Button homeButton{ "graphics/Home_button.png", {300, 660}, 0.4f };
    Button quitButton{ "graphics/Quit_button2.png", {500, 660}, 0.4f };
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

                name[letterCount] = (char)letter; 
                    name[letterCount + 1] = '\0'; // Add null terminator at the end of the string

                letterCount++;

            }
            letter = GetCharPressed();  // Check next character in the queue
        }

        if (IsKeyPressed(KEY_BACKSPACE)) // delete the last entered letter 
        {
            letterCount--;
            if (letterCount < 0) //if there are no letters entered, return letterCount to zero
            {
                letterCount = 0;
                name[letterCount] = '\0';
            }

        }
        // check if the word has the letter the user entered
        if (IsKeyPressed(KEY_ENTER)) {
            char letterToCheck = name[letterCount - 1];
            bool foundLetter = false;

            for (int i = 0; i < chosenWord.size(); i++) {
                if (chosenWord[i] == letterToCheck) {
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


        DrawTextEx(fontBt, "GUESS THE WORD:", { 70, 56 }, (float)fontBt.baseSize, 30, BLACK);
        DrawTextEx(fontBt, "(try guessing math terms)", { 30, 120 }, (float)fontBt.baseSize - 36, 1, DARKBLUE);
        DrawTextEx(fontBt, TextFormat( "Letters left: %i/%i", foundcount, maxInput), { 1170, 700 }, (float)fontBt.baseSize - 24, 1, DARKBLUE);
        DrawTextEx(fontBt, "Guess a letter ", { 70, 260 }, (float)fontBt.baseSize, 30, BLACK);
        DrawTextEx(fontBt, "and press ENTER : ", { 70, 340 }, (float)fontBt.baseSize, 15, BLACK);

        // draw the underscores
        DrawTextEx(fontBt, underscores, { 180, 70 + 105 }, (float)fontBt.baseSize, 60, BLACK);

        // draw user's input
        DrawTextEx(fontBt, name, {100, 400}, (float)fontBt.baseSize + 30, 40, DARKBLUE);

        // draw the hangman when you have 5 lives
        if (lives == 5)
        {
            DrawTextEx(fontBt, "Lives left: 5/5", { 1200, 80 }, (float)fontBt.baseSize - 24, 1,RED);
            DrawTexture(hangman5, screenWidth / 2 - hangman5.width / 2, screenHeight / 2 - hangman5.height / 2, WHITE);
            if ((lives != 0) && (letterCount == maxInput))
            {
                DrawTextEx(fontBt, "GAME WON", { 70, 500 }, (float)fontBt.baseSize, 17, DARKGREEN);  // draw Game Won if the user has guessed
            }
        }
        // draw the hangman when you have 4 lives
        if (lives == 4)
        {
            DrawTextEx(fontBt, "Lives left: 4/5", { 1200, 80 }, (float)fontBt.baseSize - 24, 1, RED);
            DrawTexture(hangman4, screenWidth / 2 - hangman4.width / 2, screenHeight / 2 - hangman4.height / 2, WHITE);
            if ((lives != 0) && (foundcount == maxInput))
            {
                DrawTextEx(fontBt, "GAME WON", { 70, 500 }, (float)fontBt.baseSize, 60, DARKGREEN); // draw Game Won if the user has guessed
            }
        }
        // draw the hangman when you have 3 lives
        if (lives == 3)
        {
            DrawTextEx(fontBt, "Lives left: 3/5", { 1200, 80 }, (float)fontBt.baseSize - 24, 1, RED);
            DrawTexture(hangman3, screenWidth / 2 - hangman3.width / 2, screenHeight / 2 - hangman3.height / 2, WHITE);
            if ((lives != 0) && (foundcount == maxInput))
            {
                DrawTextEx(fontBt, "GAME WON", { 70, 500 }, (float)fontBt.baseSize, 60, DARKGREEN);  // draw Game Won if the user has guessed
                
            }
        }
        // draw the hangman when you have 2 lives
        if (lives == 2)
        {
            DrawTextEx(fontBt, "Lives left: 2/5", { 1200, 80 }, (float)fontBt.baseSize - 24, 1, RED);
            DrawTexture(hangman2, screenWidth / 2 - hangman2.width / 2, screenHeight / 2 - hangman2.height / 2, WHITE);
            if ((lives != 0) && (foundcount == maxInput))
            {
                DrawTextEx(fontBt, "GAME WON", { 70, 500 }, (float)fontBt.baseSize, 60, DARKGREEN); // draw Game Won if the user has guessed
            }
        }
        // draw the hangman when you have 1 live
        if (lives == 1)
        {
            DrawTextEx(fontBt, "Lives left: 1/5", { 1200, 80 }, (float)fontBt.baseSize - 24, 1, RED);
            DrawTexture(hangman1, screenWidth / 2 - hangman1.width / 2, screenHeight / 2 - hangman1.height / 2, WHITE);
            if ((lives != 0) && (foundcount == maxInput)) // draw Game Won if the user has guessed
            {
                DrawTextEx(fontBt, "GAME WON", { 70, 500 }, (float)fontBt.baseSize, 60, DARKGREEN);
            }

            // draw the hangman when you have 0 lives
        }if (lives == 0)
        {
            DrawTextEx(fontBt, "Lives left: 0/5", { 1200, 80 }, (float)fontBt.baseSize - 24, 1, RED);
            DrawTextEx(fontBt, "GAME OVER", { 70, 500 }, (float)fontBt.baseSize, 60, RED);
            DrawTexture(hangman0, screenWidth / 2 - hangman0.width / 2, screenHeight / 2 - hangman0.height / 2, WHITE);
            PlaySound(end_sound);


        }
        //draw restert, home and quit buttons
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
    





    return NIL;

  }
 


