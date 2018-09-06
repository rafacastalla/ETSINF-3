#include <linux/unistd.h>
int sacarpid(int PID) {
	return syscall(337 , PID);
}
