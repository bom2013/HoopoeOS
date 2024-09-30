// Logging utils
#ifndef KERNEL_LOGGING_H_
#define KERNEL_LOGGING_H_

#define LOG(msg, ...)                 \
    do                                \
    {                                 \
        log_info(msg, ##__VA_ARGS__); \
    } while (0)
#define ERROR(msg, ...)                                                  \
    do                                                                   \
    {                                                                    \
        log_error(msg, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
    } while (0)

void log_info(const char *msg, ...);
void log_error(const char *msg, const char *src_file, const char *function, int line_number, ...);

#endif // KERNEL_LOGGING_H_