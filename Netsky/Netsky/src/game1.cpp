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
        problem.displayedResult += (rand() % 2 + 1);
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
        ImageResize(&normalStanceImage, 500, 700);
        normalStance = LoadTextureFromImage(normalStanceImage);
    }



    MathProblem currentProblem = GenerateMathProblem();
    int score = 0;
    float timer = 500.0f;
    bool gameOver = false;
    Button trueButton{ "graphics/True_button.png", {300, 620}, 0.25f };
    Button falseButton{ "graphics/False_button.png", {800, 620}, 0.25f };
    Button restartButton{ "graphics/Play_button.png", {400, 500}, 0.1f };
    Button exitButton{ "graphics/Quit_button.png", {900, 500}, 0.1f };

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
                }
                currentProblem = GenerateMathProblem();
            }
            if (falseButton.IsPressed(mousePosition, mousePressed)) {
                if (!currentProblem.isCorrect) {
                    score += 10;
                }
                currentProblem = GenerateMathProblem();
            }

        }

        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, -15, WHITE);
        DrawTexture(normalStance, 950, -10, WHITE);

        if (!gameOver) {
            DrawText(("Score: " + std::to_string(score)).c_str(), 1290, 10, 30, BLACK);
            DrawText(("Time: " + std::to_string(timer)).c_str(), 1290, 50, 30, BLACK);

            std::string problemText = std::to_string(currentProblem.num1) + " " +
                currentProblem.operation + " " +
                std::to_string(currentProblem.num2) + " = " +
                std::to_string(currentProblem.displayedResult);
            DrawText(problemText.c_str(), screenWidth / 2 - MeasureText(problemText.c_str(), 40) / 2, 300, 40, BLACK);
            trueButton.Draw();
            falseButton.Draw();

        }

        else {
            DrawText(("Game Over! Your score: " + std::to_string(score)).c_str(), screenWidth / 2 - 250, 300, 40, BLACK);
            restartButton.Draw();
            exitButton.Draw();

            if (restartButton.IsPressed(mousePosition, mousePressed)) {
                score = 0;
                timer = 30.0f;
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
    UnloadTexture(normalStance);
    UnloadTexture(background);
    return NIL;
}

