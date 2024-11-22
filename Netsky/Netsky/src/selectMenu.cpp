#include <selectMenu.hpp>


GameState selectMenu()
{
    Music music = LoadMusicStream("music/theme.mp3");


    bool pause = false;

    Texture2D background = LoadTexture("graphics/Background.png");
    Button game1Button{ "graphics/True_Solve.png", {300, 400}, 0.5f };
    Button game2Button{ "graphics/HangMan.png", {600, 400}, 0.5f};
    Button game3Button{ "graphics/MathBattle.png", {900, 400}, 0.5f };
    Button muteButton{ "graphics/Sound_button.png", {1400, 690}, 0.15f };
    Button goBackButton{ "graphics/Go_back.png", {25, 25}, 0.10f };
    bool exit = false;
    Font fontBm = LoadFontEx("fonts/CartoonCheck-Black.ttf", 32, 0, 250);
  

    while (true)
    {
       
        UpdateMusicStream(music);

        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        if (game1Button.IsPressed(mousePosition, mousePressed))
        {
            return GAME1;
        }

        if (game2Button.IsPressed(mousePosition, mousePressed))
        {
            return GAME2;
        }

        if (game3Button.IsPressed(mousePosition, mousePressed))
        {
            return GAME3;
        }

        if (muteButton.IsPressed(mousePosition, mousePressed))
        {
            StopMusicStream(music);
            PlayMusicStream(music);
        }


        if (goBackButton.IsPressed(mousePosition, mousePressed))
        {
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
        DrawTextEx(fontBm, "NETSKY", (Vector2{ 570, 150 }), (float)fontBm.baseSize, 32, RAYWHITE);
        DrawTextEx(fontBm, "CHOOSE A GAME", { 390, 230 }, (float)fontBm.baseSize, 32, RAYWHITE);

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