
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <log.h>

static int ensure_log_dir(void) {
    struct stat st;
    if (stat("./log", &st) == 0) {
        return S_ISDIR(st.st_mode) ? 0 : -1;
    }

    if (mkdir("./log", 0755) == 0)
        return 0;

    if (errno == EEXIST)
        return 0;

    return -1;
}

inline int log_init(const char *log_name) {
    if (!log_name)
        return -1;

    if (ensure_log_dir() != 0) {
        fprintf(stderr, "failed to create ./log directory\n");
        return -1;
    }

    char path[256];
    snprintf(path, sizeof(path), "./log/%s", log_name);

    log_set_level(LOG_INFO);
    log_set_quiet(false);

    FILE *fp = fopen(path, "w");
    if (!fp) {
        perror("fopen log file");
        return -1;
    }

    log_add_fp(fp, LOG_INFO);
    return 0;
}
