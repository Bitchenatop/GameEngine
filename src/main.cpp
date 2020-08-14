#include "render_engine/GLFW.h"
#include "render_engine/Window.h"

int main()
{
	try
	{
		GLFW glfw;
		Window window(1366, 720, "GameEngine");
		window.loop();
	}
	catch (runtime_error e)
	{
		cout << "EXCEPTION: " << e.what() << endl;
	}

	return 0;
}