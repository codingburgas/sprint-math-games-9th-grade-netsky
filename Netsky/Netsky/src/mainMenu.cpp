#include <mainMenu.hpp>


GameState mainMenu()
{
    Music music = LoadMusicStream("music/theme.mp3");

    bool pause = false;             

    Texture2D background = LoadTexture("graphics/Background.png");
    Button startButton{"graphics/Play_button.png", {600, 300}, 0.2f};
    Button exitButton{"graphics/Quit_button.png", {600, 400}, 0.2f};
    Button muteButton{"graphics/Sound_button.png", {1300, 690}, 0.15f};
    bool exit = false;
    Font fontBm = LoadFontEx("fonts/CartoonCheck-Black.ttf", 64, 0, 500);
 

    while (true)
    {
        UpdateMusicStream(music);

        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        if(startButton.IsPressed(mousePosition, mousePressed))
        {
            UnloadFont(fontBm);
            UnloadMusicStream(music);
            UnloadTexture(background);

            return GAME_SELECT;

        }

        if(exitButton.IsPressed(mousePosition, mousePressed))
        {
            UnloadFont(fontBm);
            UnloadMusicStream(music);
            UnloadTexture(background);
            return NIL;
        }

        if(muteButton.IsPressed(mousePosition, mousePressed))
        {
           StopMusicStream(music);
           PlayMusicStream(music);
        }

        if(muteButton.IsPressed(mousePosition, mousePressed))
        {
            pause = !pause;

            if (pause) 
                PauseMusicStream(music);
            else 
                ResumeMusicStream(music);

        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(background, 0, -1, WHITE);
        DrawTextEx(fontBm, "NETSKY", (Vector2{485, 110}), (float)fontBm.baseSize + 30, 15, RAYWHITE);
        DrawTextEx(fontBm, "minigames", {400, 230}, (float)fontBm.baseSize + 30, 15, RAYWHITE);
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