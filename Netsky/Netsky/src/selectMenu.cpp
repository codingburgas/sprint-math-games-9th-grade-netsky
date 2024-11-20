#include <selectMenu.hpp>

GameState selectMenu()
{
    Music music = LoadMusicStream("music/theme.mp3");

    PlayMusicStream(music);

    bool pause = false;

    Texture2D background = LoadTexture("graphics/Background.png");
    Button startButton{ "graphics/Play_button.png", {260, 300}, 0.2f };
    Button exitButton{ "graphics/Quit_button.png", {260, 400}, 0.2f };
    Button muteButton{ "graphics/Sound_button.png", {590, 690}, 0.15f };
    bool exit = false;
    Font fontBm = LoadFontEx("fonts/CartoonCheck-Black.ttf", 32, 0, 250);


    while (WindowShouldClose() == false && exit == false)
    {
        UpdateMusicStream(music);

        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        if (startButton.IsPressed(mousePosition, mousePressed))
        {

        }

        if (exitButton.IsPressed(mousePosition, mousePressed))
        {
            exit = true;
        }

        if (muteButton.IsPressed(mousePosition, mousePressed))
        {
            StopMusicStream(music);
            PlayMusicStream(music);
        }

        if (muteButton.IsPressed(mousePosition, mousePressed))
        {
            pause = !pause;

            if (pause)
                PauseMusicStream(music);
            else
                ResumeMusicStream(music);

        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(background, 0, 10, WHITE);
        DrawTextEx(fontBm, "HELLO NIGGA", (Vector2{ 260, 150 }), (float)fontBm.baseSize, 32, RAYWHITE);
        DrawTextEx(fontBm, "minigames", { 190, 230 }, (float)fontBm.baseSize, 32, RAYWHITE);
        startButton.Draw();
        exitButton.Draw();
        muteButton.Draw();
        EndDrawing();

    }
    UnloadFont(fontBm);
    UnloadMusicStream(music);
    UnloadTexture(background);
    return NIL;
}