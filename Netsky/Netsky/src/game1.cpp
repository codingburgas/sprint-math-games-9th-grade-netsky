#include <cstdlib>
#include <game1.hpp>
#include <iostream>


struct MathProblem { // Create new data type
    int num1;
    int num2;
    char operation;
    int displayedResult;
    bool isCorrect;
};

MathProblem GenerateMathProblem() { 
    MathProblem problem;
    problem.num1 = rand() % 20 + 1;
    problem.num2 = rand() % 20 + 1;
    int opType = rand() % 4;

    switch (opType) {
    case 0:
        problem.operation = '+';
        problem.displayedResult = problem.num1 + problem.num2;
        break;
    case 1:
        problem.operation = '-';
        problem.displayedResult = problem.num1 - problem.num2;
        break;
    case 2:
        problem.operation = '*';
        problem.displayedResult = problem.num1 * problem.num2;
        break;
    case 3:
        problem.operation = '/';
        problem.displayedResult = problem.num2 != 0 ? problem.num1 / problem.num2 : 0;
        break;
    }

    // Randomly decide if displayed result is correct 
    problem.isCorrect = rand() % 2 == 0;
    if (!problem.isCorrect) {
        problem.displayedResult += (rand() % 5 + 1);
    }

    return problem;
}

GameState game1(int screenWidth, int screenHeight) {
    // Load textures
    Texture2D background = LoadTexture("graphics/backgroundgame1.png"); 
    
    Texture2D greenBoard; 
    {
        Image greenBoardImage = LoadImage("graphics/Green_board.png");
        ImageResize(&greenBoardImage, 1200, 600);
        greenBoard = LoadTextureFromImage(greenBoardImage);
    }

    Texture2D normalStance;
    {
        Image normalStanceImage = LoadImage("graphics/NormalStance.png");
        ImageResize(&normalStanceImage, 700, 700);
        normalStance = LoadTextureFromImage(normalStanceImage);
    }

    Texture2D thumbsUp;
    {
        Image thumbsUpImage = LoadImage("graphics/Thumbs_up.png");
        ImageResize(&thumbsUpImage, 700, 700);
        thumbsUp = LoadTextureFromImage(thumbsUpImage);
    }

    Texture2D thumbsDown;
    {
        Image thumbsDownImage = LoadImage("graphics/Thumbs_down.png");
        ImageResize(&thumbsDownImage, 700, 700);
        thumbsDown = LoadTextureFromImage(thumbsDownImage);
    }

    Texture2D currentTexture = normalStance;

    MathProblem currentProblem = GenerateMathProblem();

    int score = 0;
    float timer = 20.0f;
    bool gameOver = false;

    // Initialize buttons
    Button trueButton{"graphics/True_button.png", {190, 660}, 0.6f };
    Button falseButton{"graphics/False_button.png", {690, 660}, 0.6f };
    Button restartButton{"graphics/Restart_button.png", {140, 660}, 0.6f };
    Button homeButton{"graphics/Home_button.png", {460, 660}, 0.6f };
    Button quitButton{"graphics/Quit_button2.png", {780, 660}, 0.6f };

    // Load fonts
    Font fontBoard = LoadFontEx("fonts/chawp.ttf", 32, 0, 250);
    Font fontCartoon = LoadFontEx("fonts/CartoonCheck-Black.ttf", 64, 0, 500);

    // Load sound effects for interactions
    Sound write_sound = LoadSound("music/chalk.MP3");
    Sound no_sound = LoadSound("music/Voicy_No.MP3");
    Sound end_sound = LoadSound("music/end.MP3");



    while (!WindowShouldClose()) {
        BeginDrawing();

        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        if (!gameOver) {
            timer -= GetFrameTime(); // Decrease timer with elapsed time
            if (timer <= 0.0f) {
                gameOver = true;
            }


            if (trueButton.IsPressed(mousePosition, mousePressed)) {
                if (currentProblem.isCorrect) {
                    score += 10;
                    currentTexture = thumbsUp;
                    PlaySound(write_sound);
                }
                else {
                    score -= 10;
                    currentTexture = thumbsDown;
                    PlaySound(no_sound);
                }
                currentProblem = GenerateMathProblem();
            }
            if (falseButton.IsPressed(mousePosition, mousePressed)) {
                if (!currentProblem.isCorrect) {
                    score += 10;
                    currentTexture = thumbsUp;
                    PlaySound(write_sound);
                }
                else {
                    score -= 10;
                    currentTexture = thumbsDown;
                    PlaySound(no_sound);
                }
                currentProblem = GenerateMathProblem();
            }

        }

        // Render game elements
        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);
        DrawTexture(greenBoard, -40, 0, WHITE);
        DrawTexture(currentTexture, 870, 130, WHITE);

        if (!gameOver) {

            // Display score and timer
            DrawTextEx(fontCartoon, ("Score: " + std::to_string(score)).c_str(), Vector2({ 1200, 30 }), 30, 5, WHITE);
            DrawTextEx(fontCartoon, ("Time: " + std::to_string((int)timer)).c_str(), Vector2({ 1200, 70 }), 30 , 5, WHITE);

            // Display current math problem
            std::string problemText = std::to_string(currentProblem.num1) + " " + currentProblem.operation + " " + std::to_string(currentProblem.num2) + " = " + std::to_string(currentProblem.displayedResult);
            DrawTextEx(fontBoard, problemText.c_str(), (Vector2{ 375, 250 }), 60, 10, WHITE);
            trueButton.Draw();
            falseButton.Draw();

            PlaySound(end_sound);

        }

        else {

            // Display game over screen
            DrawTextEx(fontBoard, ("Game Over! Your score: " + std::to_string(score)).c_str(), Vector2({ 165, 200 }), 50, 5, WHITE);
            restartButton.Draw();
            homeButton.Draw();
            quitButton.Draw();
            if (score >= 50)
            {
                currentTexture = thumbsUp;
            }
            else {
                currentTexture = thumbsDown;
            }

            // Check button presses for restart, home and quit
            if (restartButton.IsPressed(mousePosition, mousePressed)) {

                PlaySound(end_sound);
                score = 0;
                timer = 20.0f;
                gameOver = false;
                currentProblem = GenerateMathProblem();
                currentTexture = normalStance;
            }
            else if (homeButton.IsPressed(mousePosition, mousePressed)) {

                // Unload assets
                UnloadFont(fontBoard);
                UnloadTexture(background);
                UnloadTexture(currentTexture);
                UnloadTexture(thumbsDown);
                UnloadTexture(thumbsUp);
                UnloadTexture(normalStance);
                UnloadTexture(greenBoard);
                UnloadSound(write_sound);
                UnloadSound(no_sound);
                UnloadSound(end_sound);
                return GAME_SELECT;
            }
            if (quitButton.IsPressed(mousePosition, mousePressed)) {
                // Unload assets
                UnloadFont(fontBoard);
                UnloadTexture(background);
                UnloadTexture(currentTexture);
                UnloadTexture(thumbsDown);
                UnloadTexture(thumbsUp);
                UnloadTexture(normalStance);
                UnloadTexture(greenBoard);
                UnloadSound(write_sound);
                UnloadSound(no_sound);
                UnloadSound(end_sound);
                CloseWindow();
                return NIL;
            }
        }
        EndDrawing();
    }
    // Unload assets
    UnloadSound(end_sound);
    UnloadSound(no_sound);
    UnloadSound(write_sound);
    UnloadFont(fontBoard);
    UnloadTexture(currentTexture);
    UnloadTexture(thumbsDown);
    UnloadTexture(thumbsUp);
    UnloadTexture(normalStance);
    UnloadTexture(greenBoard);
    UnloadTexture(background);

    return NIL;
}

