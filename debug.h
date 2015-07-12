#ifndef DEBUG_H
#define DEBUG_H

#define OK      1
#define ERROR   0

#define GENERAL_ERROR   1
#define MEM_ERROR      10

#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define error(M, ...) fprintf(stderr, "ERROR %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)


#endif /* DEBUG_H */