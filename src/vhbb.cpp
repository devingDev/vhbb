#include <global_include.h>

// Davee: Fix c++ exceptions
//#### TODO: move to SDK
extern "C"
{
    unsigned int sleep(unsigned int seconds)
    {
        sceKernelDelayThread(seconds*1000*1000);
        return 0;
    }

    /*int usleep(unsigned int usec)
    {
        sceKernelDelayThread(usec);
        return 0;
    }*/

    void __sinit(struct _reent *);
}

__attribute__((constructor(101)))
void pthread_setup(void) 
{
    pthread_init();
    __sinit(_REENT);
}
//#### end TODO

int main()
{
	dbg_init();

	#ifdef PSP2SHELL
	// Do it before any file is opened otherwise psp2shell fails to reload the app
	sceAppMgrUmount("app0:");
	psp2shell_init(3333, 0);
	dbg_printf(DBG_INFO, "PSPSHELL started on port 3333");
	#endif

	vita2d_init();
	vita2d_set_clear_color(COLOR_BLACK);

	Input input;
	
	Background background;
	CategoryView categoryView;
	StatusBar statusBar;
	// Init queue view too

	GUIViews curView = LIST_VIEW;
	while (1) {
		//sceKernelPowerTick(0);
		vita2d_start_drawing();
		vita2d_clear_screen();

		input.Get();
		//input.Propagate(curView); // TODO: Rework function
		categoryView.HandleInput(1, input);	

		background.Display();
		categoryView.Display();
		statusBar.Display();

		vita2d_end_drawing();
		vita2d_swap_buffers();
		sceDisplayWaitVblankStart();	
	}

	#ifdef PSP2SHELL
	psp2shell_exit();
	#endif

	return 0;
}
