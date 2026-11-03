#include <raylib.h>

#define FPS 60
#define D_SC_H 900
#define D_SC_W 600

Color Blue = {59, 130, 246, 1};
Color Cyan = {4, 202, 225};
Color Gold = {59, 130, 246, 1};
Color Red = {59, 130, 246, 1};

// Plate and Point 
#define PLT_R 111
#define PT_R 16

int main(){
	SetTargetFPS(FPS);
	InitWindow(D_SC_W, D_SC_H, "Needles");
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(Cyan);
		DrawCircle(D_SC_W / 2, D_SC_H / 2, PLT_R, BLUE);
		DrawCircle(D_SC_W / 2, D_SC_H / 2, PT_R, GOLD);

		EndDrawing();
	}
}
