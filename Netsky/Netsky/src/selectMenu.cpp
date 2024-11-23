#include <selectMenu.hpp>


GameState selectMenu()
{
    Music music = LoadMusicStream("music/theme.mp3");


    bool pause = false;

    Texture2D background = LoadTexture("graphics/Background.png");
    Button game1Button{ "graphics/True_Solve.png", {250, 400}, 0.5f };
    Button game2Button{ "graphics/HangMan.png", {625, 400}, 0.5f};
    Button game3Button{ "graphics/MathBattle.png", {1000, 400}, 0.5f };
    Button muteButton{ "graphics/Sound_button.png", {1400, 690}, 0.15f };
    Button goBackButton{ "graphics/Go_back.png", {25, 25}, 0.10f };
    bool exit = false;
    Font fontBm = LoadFontEx("fonts/CartoonCheck-Black.ttf", 64, 0, 500);
  

    while (true)
    {
       
        UpdateMusicStream(music);

        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        if (game1Button.IsPressed(mousePosition, mousePressed))
        {
            UnloadFont(fontBm);
            UnloadMusicStream(music);
            UnloadTexture(background);
            return GAME1;
        }

        if (game2Button.IsPressed(mousePosition, mousePressed))
        {
            UnloadFont(fontBm);
            UnloadMusicStream(music);
            UnloadTexture(background);
            return GAME2;
        }

        if (game3Button.IsPressed(mousePosition, mousePressed))
        {
            UnloadFont(fontBm);
            UnloadMusicStream(music);
            UnloadTexture(background);
            return GAME3;
        }

        if (muteButton.IsPressed(mousePosition, mousePressed))
        {
            StopMusicStream(music);
            PlayMusicStream(music);
        }


        if (goBackButton.IsPressed(mousePosition, mousePressed))
        {
            UnloadFont(fontBm);
            UnloadMusicStream(music);
            UnloadTexture(background);

            return MENU;

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
        ClearBackground (BLUE);
        DrawTexture(background, 0, -1, WHITE);
        DrawTextEx(fontBm, "NETSKY", (Vector2{ 500, 100 }), (float)fontBm.baseSize + 30, 15, RAYWHITE);
        DrawTextEx(fontBm, "CHOOSE A GAME", { 250, 230 }, (float)fontBm.baseSize + 30, 15, RAYWHITE);

   
        game1Button.Draw();
        game2Button.Draw();
        game3Button.Draw();
        muteButton.Draw();
        goBackButton.Draw();
        EndDrawing();


    }
    UnloadFont(fontBm);
    UnloadMusicStream(music);
    UnloadTexture(background);
    return NIL;
}