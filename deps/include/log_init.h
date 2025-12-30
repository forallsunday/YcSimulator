// 初始化log
#ifndef LOG_INIT_HPP
#define LOG_INIT_HPP

#include <cerrno>
#include <cstdio>
#include <mutex>
#include <sys/stat.h>
#include <sys/types.h>

#include <log.h>

static std::mutex g_log_mutex;

static void log_lock_fn(bool lock, void *udata) {
    auto *m = static_cast<std::mutex *>(udata);

    if (lock)
        m->lock();
    else
        m->unlock();
}

static int ensure_log_dir(void) {
    struct stat st;
    if (stat("./log", &st) == 0)
        return S_ISDIR(st.st_mode) ? 0 : -1;

    if (mkdir("./log", 0755) == 0)
        return 0;

    if (errno == EEXIST)
        return 0;

    return -1;
}

inline int log_init(const char *log_name) {
    if (!log_name)
        return -1;

    ensure_log_dir();

    char path[256];
    snprintf(path, sizeof(path), "./log/%s", log_name);

    FILE *fp = fopen(path, "w");
    if (!fp) {
        perror("fopen");
        return -1;
    }

    // ---- 注册锁（std::mutex）----
    log_set_lock(log_lock_fn, &g_log_mutex);

    // ---- 正常初始化 ----
    log_set_level(LOG_INFO);
    log_set_quiet(false);
    log_add_fp(fp, LOG_INFO);

    return 0;
}

#endif
