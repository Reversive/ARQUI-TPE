/* sampleCodeModule.c */
#include "include/stdio.h"
#include "include/time.h"
#include "include/colors.h"
#include "include/console.h"

char console_buffer[MAX] = {0};


int main() {
	sys_set_text_color(WHITE);
	printf("\nBienvenidos a TaurOS, espero que lo disfruten!\n\n");
	help();
	putchar('\n');
	sys_set_cursor_status(_ENABLED);
	
	while(1) {
		char c;
		sys_set_text_color(WHITE);
		puts("TaurOS> ");
		sys_set_text_color(LIME);
		while(c = getchar(), c != '\n') {
			if(c != EOF) {
				console_key_handler(c,console_buffer);
			}
		}
		if (is_newline_char(c)){
			console_finish_handler(console_buffer);
		}
		putchar('\n');
	}
	sys_set_cursor_status(_DISABLED);

	return 0x1;
}
