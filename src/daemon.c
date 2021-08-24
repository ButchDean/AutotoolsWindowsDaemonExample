#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main() {

    FILE* fp = NULL;

    pid_t process_id = 0;
    pid_t sid = 0;

    int sentinel = 0;

#ifdef __CYGWIN__
    puts("Cygwin platform detected.");
#else
    puts("__CYGWIN__ not detected.");
#endif

#ifdef _WIN32
    puts("_WIN32 platform detected.");
#else
    puts("_WIN32 not detected.");
#endif

#ifdef WIN32
    puts("WIN32 platform detected.");
#else
    puts("WIN32 not detected.");
#endif

#ifdef KERNEL_WIN32
    puts("KERNEL_WIN32 platform detected.");
#else
    puts("KERNEL_WIN32 not detected.");
#endif

    // Create child process
    process_id = fork();

    // Check for successfully occurred
    if(process_id < 0) {
        printf("Fork failed with code: %d\n", process_id);
        exit(1);
    }

    // Kill parent process.
    if(process_id > 0) {
        printf("process_id of child process: %d\n", process_id);
        exit(0);    // We exit the terminal here
    }

    // Unmask file mode
    umask(0);

    // Set new session
    sid = setsid();

    if(sid < 0) {
        printf("setsid() failed with code: %d\n", sid);
        exit(1);
    }

    // Close STDIN, STDOUT, STDERR
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // open a log file in write mode
    fp = fopen("log.txt", "w+");

    while(sentinel < 10) {
        // Don't block context switches by allowing sleep
        sleep(1);
        fprintf(fp, "Daemon logging...\n");
        fflush(fp);

        sentinel++;
    }

    fclose(fp);

    return 0;
}
