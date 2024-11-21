#include <selectMenu.hpp>

GameState selectMenu()
{
    Music music = LoadMusicStream("music/theme.mp3");

    PlayMusicStream(music);

    bool pause = false;

    Texture2D background = LoadTexture("graphics/Background.png");
    Button game1Button{ "graphics/Game_icon.png", {333, 556}, 0.10f };
    Button game2Button{ "graphics/Game_icon.png", {433, 556}, 0.10f };
    Button game3Button{ "graphics/Game_icon.png", {533, 400}, 0.10f };
    Button muteButton{ "graphics/Sound_button.png", {1300, 690}, 0.15f };
    Button goBackButton{ "graphics/Go_back.png", {25, 25}, 0.10f };
    bool exit = false;
    Font fontBm = LoadFontEx("fonts/CartoonCheck-Black.ttf", 32, 0, 250);


    while (WindowShouldClose() == false && exit == false)
    {
        UpdateMusicStream(music);

        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        if (game1Button.IsPressed(mousePosition, mousePressed))
        {

        }

        if (game2Button.IsPressed(mousePosition, mousePressed))
        {
          
        }

        if (game3Button.IsPressed(mousePosition, mousePressed))
        {

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
        ClearBackground(BLACK);
        DrawTexture(background, 0, 10, WHITE);
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