#include <ftxui/dom/elements.hpp>
#include <stdlib.h>                // for EXIT_SUCCESS
#include <ftxui/screen/screen.hpp>  // for Full, Screen
#include <memory>                   // for allocator
 
#include "ftxui/dom/node.hpp"      // for Render
#include "ftxui/screen/color.hpp"  // for ftxui
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"

#include <iostream>

using namespace ftxui;
using namespace std;

int main(void){
	auto document = hbox(
		text("qwq") | color(Color::Pink1) | flex | border ,
		text("qwq") | color(Color::Red) | flex | border
	);

	/* 静态屏幕
	auto screen = Screen::Create(
		Dimension::Full(),  // width
		Dimension::Full()   // height
	);
	
	Render(screen, document);
	screen.Print();
	*/

	/* 可交互式屏幕 */
	auto screen = ScreenInteractive::Fullscreen();  // 全屏
	Component comp = Renderer([&]{
		return document;
	});
	
	screen.Loop(comp);
	
	return 0;
}
