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

// Needles
#define ND_BODY 64
#define ND_HEAD 9 

void Needles(int x, int y, float rot) {
	DrawCircle(x, y, ND_HEAD, BLACK);
	Rectangle rec = {x, y, 3, ND_BODY};
	// origin 遵循左加右减
	Vector2 o ={1, 0};  // Origin是一个偏移量，在(x,y)的基础上进行偏移
	DrawRectanglePro(rec, o, rot, BLACK);  // rot角度制
}

int main(){
	SetTargetFPS(FPS);
	InitWindow(D_SC_W, D_SC_H, "Needles");
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(Cyan);

		double cx = D_SC_W / 2;
		double cy = D_SC_H / 2;

		DrawCircle(cx, cy, PLT_R, BLUE);
		DrawCircle(cx, cy, PT_R, GOLD);

		Needles(cx, cy, 0);

		EndDrawing();
	}
}
