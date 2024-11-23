#include <game1.hpp>
#include <cstdlib>
#include <iostream>


struct MathProblem {
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

    problem.isCorrect = rand() % 2 == 0;
    if (!problem.isCorrect) {
        problem.displayedResult += (rand() % 5 + 1);
    }

    return problem;
}

GameState game1(int screenWidth, int screenHeight) {

    Texture2D background;
    {
        Image backgroundImage = LoadImage("graphics/Green_board.png");
        ImageResize(&backgroundImage, 1100, 600);
        background = LoadTextureFromImage(backgroundImage);
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
    float timer = 1.0f;
    bool gameOver = false;
    Button trueButton{ "graphics/True_button.png", {300, 660}, 0.6f };
    Button falseButton{ "graphics/False_button.png", {800, 660}, 0.6f };
    Button restartButton{ "graphics/Play_button.png", {400, 500}, 0.1f };
    Button exitButton{ "graphics/Quit_button.png", {900, 500}, 0.1f };
    Font fontBoard = LoadFontEx("fonts/chawp.ttf", 32, 0, 250);

    while (!WindowShouldClose()) {
        BeginDrawing();

        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        if (!gameOver) {
            timer -= GetFrameTime();
            if (timer <= 0.0f) {
                gameOver = true;
            }


            if (trueButton.IsPressed(mousePosition, mousePressed)) {
                if (currentProblem.isCorrect) {
                    score += 10;
                    currentTexture = thumbsUp;
                }
                else {
                    currentTexture = thumbsDown;
                }
                currentProblem = GenerateMathProblem();
            }
            if (falseButton.IsPressed(mousePosition, mousePressed)) {
                if (!currentProblem.isCorrect) {
                    score += 10;
                    currentTexture = thumbsUp;
                }
                else {
                    currentTexture = thumbsDown;
                }
                currentProblem = GenerateMathProblem();
            }

        }

        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, -15, WHITE);
        DrawTexture(currentTexture, 850, 50, WHITE);

        if (!gameOver) {

            DrawText(("Score: " + std::to_string(score)).c_str(), 1200, 10, 30, BLACK);
            DrawText(("Time: " + std::to_string((int)timer)).c_str(), 1200, 50, 30, BLACK);

            std::string problemText = std::to_string(currentProblem.num1) + " " + currentProblem.operation + " " + std::to_string(currentProblem.num2) + " = " + std::to_string(currentProblem.displayedResult);
            DrawTextEx(fontBoard, problemText.c_str(), (Vector2{ 375, 250 }), 60, 10, WHITE);
            trueButton.Draw();
            falseButton.Draw();

        }

        else {
            DrawTextEx(fontBoard, ("Game Over! Your score: " + std::to_string(score)).c_str(), Vector2({ 225, 250 }), 50, 0, WHITE);
            restartButton.Draw();
            exitButton.Draw();
            if (restartButton.IsPressed(mousePosition, mousePressed)) {
                score = 0;
                timer = 50.0f;
                gameOver = false;
                currentProblem = GenerateMathProblem();

            }

            if (exitButton.IsPressed(mousePosition, mousePressed)) {
                CloseWindow();
                return NIL;
            }
        }
        EndDrawing();
    }
    UnloadTexture(thumbsDown);
    UnloadTexture(thumbsUp);
    UnloadTexture(normalStance);
    UnloadTexture(background);
    return NIL;
}

