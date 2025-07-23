#include "../include/ui.h"
#include "../include/io.h"
#include "../include/ins.h"

signed main()
{
	load_data();
	ui_init();
	ui_main_loop();
	ui_cleanup();
	save_data();
}
