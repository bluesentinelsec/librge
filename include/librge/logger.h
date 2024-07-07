#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

    typedef enum
    {
        RGE_LOG_LEVEL_DEBUG,
        RGE_LOG_LEVEL_INFO,
        RGE_LOG_LEVEL_WARN,
        RGE_LOG_LEVEL_ERROR,
        RGE_LOG_LEVEL_FATAL
    } RGE_LogLevel;

    // Helper function to extract just the filename from the path
    static const char *get_filename(const char *path)
    {
        const char *filename = strrchr(path, '/');
#ifdef _WIN32
        const char *filename_win = strrchr(path, '\\');
        if (!filename || (filename_win && filename_win > filename))
        {
            filename = filename_win;
        }
#endif
        return filename ? filename + 1 : path; // +1 to skip the slash
    }

    static void rgeLog(RGE_LogLevel level, const char *file, int line, const char *fmt, ...)
    {
        va_list args;
        FILE *output_stream = (level >= RGE_LOG_LEVEL_WARN) ? stderr : stdout;

        switch (level)
        {
        case RGE_LOG_LEVEL_DEBUG:
            fprintf(output_stream, "DEBUG: ");
            break;
        case RGE_LOG_LEVEL_INFO:
            fprintf(output_stream, "INFO: ");
            break;
        case RGE_LOG_LEVEL_WARN:
            fprintf(output_stream, "WARN: ");
            break;
        case RGE_LOG_LEVEL_ERROR:
            fprintf(output_stream, "ERROR: ");
            break;
        case RGE_LOG_LEVEL_FATAL:
            fprintf(output_stream, "FATAL: ");
            break;
        }

        // Use the get_filename function to only print the filename
        fprintf(output_stream, "(%s:%d) ", get_filename(file), line);

        va_start(args, fmt);
        vfprintf(output_stream, fmt, args);
        va_end(args);

        fprintf(output_stream, "\n");
    }

#ifdef NDEBUG
#define rgeLogDebug(fmt, ...) ((void)0)
#else
#define rgeLogDebug(fmt, ...) rgeLog(RGE_LOG_LEVEL_DEBUG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#endif
#define rgeLogInfo(fmt, ...) rgeLog(RGE_LOG_LEVEL_INFO, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define rgeLogWarn(fmt, ...) rgeLog(RGE_LOG_LEVEL_WARN, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define rgeLogError(fmt, ...) rgeLog(RGE_LOG_LEVEL_ERROR, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define rgeLogFatal(fmt, ...) rgeLog(RGE_LOG_LEVEL_FATAL, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif
