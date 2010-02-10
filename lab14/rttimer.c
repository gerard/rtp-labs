#include <stdio.h>
#include <time.h>
#include <signal.h>

void sig_handler(int signo, siginfo_t *siginf, void *context) {
	struct itimerspec *it;
	
	it = (struct itimerspec *)siginf->si_value.sival_ptr;
	printf("%d", it->it_interval.tv_sec);
}

int main() {
	struct sigaction sigact;
	struct sigevent s1, s2, s3;
	timer_t t1, t2, t3;
	struct itimerspec it1, it2, it3;

	setvbuf(stdout, NULL, _IONBF, 0);

	sigact.sa_sigaction = sig_handler;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = SA_SIGINFO;
	sigaction(SIGALRM, &sigact, NULL);
	
	it1.it_value.tv_nsec = it1.it_interval.tv_nsec = 0;
	it1.it_value.tv_sec = it1.it_interval.tv_sec = 1;
	it2.it_value.tv_nsec = it2.it_interval.tv_nsec = 0;
	it2.it_value.tv_sec = it2.it_interval.tv_sec = 3;
	it3.it_value.tv_nsec = it3.it_interval.tv_nsec = 0;
	it3.it_value.tv_sec = it3.it_interval.tv_sec = 7;
	
	s1.sigev_notify = s2.sigev_notify = s3.sigev_notify = SIGEV_SIGNAL;
	s1.sigev_signo = s2.sigev_signo = s3.sigev_signo = SIGALRM;
	s1.sigev_value.sival_ptr = (void *)&it1;
	s2.sigev_value.sival_ptr = (void *)&it2;
	s3.sigev_value.sival_ptr = (void *)&it3;
	
	timer_create(CLOCK_REALTIME, &s1, &t1);
	timer_settime(t1, 0, &it1, NULL);
	
	timer_create(CLOCK_REALTIME, &s2, &t2);
	timer_settime(t2, 0, &it2, NULL);
	
	timer_create(CLOCK_REALTIME, &s3, &t3);
	timer_settime(t3, 0, &it3, NULL);
	
	while(pause());
}
