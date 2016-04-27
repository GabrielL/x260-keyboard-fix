#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>

#define INSERT_SCANCODE 0xd2
#define END_SCANCODE 0xcf

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;

	int fd = open(argv[1], O_RDWR);

	struct input_keymap_entry keymap_entry[] = {
		{
			.len = 4,
			.keycode = KEY_END,
			.scancode = { INSERT_SCANCODE, 0 },
		},
		{
			.len = 4,
			.keycode = KEY_INSERT,
			.scancode = { END_SCANCODE, 0 },
		}
	};

	for (size_t i = 0; i < sizeof(keymap_entry) / sizeof(*keymap_entry); ++i) {
		int rc = ioctl(fd, EVIOCSKEYCODE_V2, &keymap_entry[i]);
	}

	close(fd);

	return 0;
}
