#include "raylib.h"

int main() {
    InitWindow(800, 600, "qwq");
    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Hello from Neovim!", 300, 280, 20, GREEN);
        DrawCircle(400, 300, 50, RED);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
