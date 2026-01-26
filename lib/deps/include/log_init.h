
#ifndef LOG_INIT_H
#define LOG_INIT_H

#include <cerrno>
#include <cstdio>
#include <mutex>

#ifdef _WIN32
#include <direct.h> // _mkdir
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

static std::mutex g_log_mutex;

static void log_lock_fn(bool lock, void *udata) {
    auto *m = static_cast<std::mutex *>(udata);
    if (lock)
        m->lock();
    else
        m->unlock();
}

// 跨平台确保 log 目录存在
static int ensure_log_dir() {
#ifdef _WIN32
    if (_mkdir("log") != 0) {
        if (errno == EEXIST)
            return 0; // 已存在
        return -1;    // 其他错误
    }
#else
    struct stat st;
    if (stat("log", &st) == 0) {
        if (!S_ISDIR(st.st_mode))
            return -1; // 存在但不是目录
        return 0;
    }
    if (mkdir("log", 0755) != 0) {
        if (errno == EEXIST)
            return 0; // 已存在
        return -1;
    }
#endif
    return 0;
}

inline int log_init(const char *log_name = nullptr) {

    if (ensure_log_dir() != 0)
        return -1;

    // ---- 注册锁（std::mutex）----
    log_set_lock(log_lock_fn, &g_log_mutex);

    // ---- 正常初始化 ----
    log_set_level(LOG_INFO);
    log_set_quiet(false);

    if (log_name != nullptr) {
        char path[256];
        snprintf(path, sizeof(path), "./log/%s", log_name);

        FILE *fp = fopen(path, "w");
        if (!fp) {
            perror("fopen");
            return -1;
        }
        log_add_fp(fp, LOG_INFO);
    }

    return 0;
}

#endif // LOG_INIT_H
