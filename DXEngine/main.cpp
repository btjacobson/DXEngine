#include "AppWindow.h"

int main()
{
	AppWindow app;
	if (app.Init())
	{
		while (app.IsRunning())
		{
			app.Broadcast();
		}
	}

	return 0;
}