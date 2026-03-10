#include <signal.h>
#include <stdio.h>

void handleSignal(int sig) {
	(void)sig;
	printf("signal : %d\n", sig);
}

int main() {
	struct sigaction sa;
	sa.sa_handler = handleSignal;
	sigaction(SIGINT, &sa, NULL);
	unsigned long long i = 0;
	while (1)
		i++;
	return (0);
}