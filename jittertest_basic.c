// Program to test Linux timing jitter by driving GPIO output via sysfs interface.

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define GPIO_TO_PIN(bank, gpio) (32 * (bank) + (gpio))

int main() {
    char buf[128];

    const int pin = GPIO_TO_PIN(1, 24);

    int fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd == -1) {
        fprintf(stderr, "Failed to open export for writing!\n");
        return(-1);
    }

    int bytes_written = snprintf(buf, sizeof buf, "%d", pin);
    write(fd, buf, bytes_written);
    close(fd);

    snprintf(buf, sizeof buf, "/sys/class/gpio/gpio%d/direction", pin);
    fd = open(buf, O_WRONLY);
    if (fd == -1) {
        fprintf(stderr, "Failed to open gpio direction for writing!\n");
        return(-1);
    }

    if (write(fd, "out", 3) == -1) {
        fprintf(stderr, "Failed to set direction!\n");
        return(-1);
    }

    snprintf(buf, sizeof buf, "/sys/class/gpio/gpio%d/value", pin);
    fd = open(buf, O_WRONLY);
    if (fd == -1) {
	    fprintf(stderr, "Failed to open gpio value for writing!\n");
	    return(-1);
    }

    while (1) {
	    if (write(fd, "1", 1) != 1) {
		    fprintf(stderr, "Failed to write value!\n");
		    return(-1);
	    }
	    usleep(500);

	    if (write(fd, "0", 1) != 1) {
		    fprintf(stderr, "Failed to write value!\n");
		    return(-1);
	    }
	    usleep(500);
    }

    close(fd);

    return 0;
}
